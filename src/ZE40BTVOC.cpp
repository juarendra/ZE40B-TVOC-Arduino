#include "ZE40BTVOC.h"

#include <string.h>

ZE40BTVOC::ZE40BTVOC(Stream &serial) : _serial(serial), _index(0), _baselineOffset(0.0f) {
  memset(_frame, 0, sizeof(_frame));
}

void ZE40BTVOC::setBaselineOffset(float offsetPpb) {
  _baselineOffset = offsetPpb;
}

float ZE40BTVOC::getBaselineOffset() const {
  return _baselineOffset;
}

void ZE40BTVOC::begin() {
  _index = 0;
  memset(_frame, 0, sizeof(_frame));
}

void ZE40BTVOC::setMode(Mode mode) {
  uint8_t command[FRAME_LENGTH] = {START_BYTE, 0x01, 0x78, static_cast<uint8_t>(mode), 0x00, 0x00, 0x00, 0x00, 0x00};
  command[FRAME_LENGTH - 1] = checksum(command);
  _serial.write(command, sizeof(command));
}

bool ZE40BTVOC::requestRead(Reading &reading) {
  const uint8_t command[FRAME_LENGTH] = {START_BYTE, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79};
  _serial.write(command, sizeof(command));

  const uint32_t startMs = millis();
  while (millis() - startMs < 100) {
    if (read(reading)) {
      return true;
    }
    yield();
  }
  return false;
}

bool ZE40BTVOC::read(Reading &reading) {
  bool found = false;
  while (_serial.available() > 0) {
    const int value = _serial.read();
    if (value >= 0 && consume(static_cast<uint8_t>(value), reading)) {
      found = true;
    }
  }
  return found;
}

bool ZE40BTVOC::readTVOC(uint16_t &tvocPpb) {
  Reading reading{};
  if (!read(reading)) {
    return false;
  }
  tvocPpb = reading.tvocPpb;
  return true;
}

bool ZE40BTVOC::parse(const uint8_t *buffer, size_t length, Reading &reading) {
  if (buffer == nullptr || length < FRAME_LENGTH) {
    return false;
  }

  bool found = false;
  for (size_t offset = 0; offset + FRAME_LENGTH <= length; ++offset) {
    if (decodeFrame(buffer + offset, reading)) {
      found = true;
      offset += FRAME_LENGTH - 1;
    }
  }
  return found;
}

uint8_t ZE40BTVOC::checksum(const uint8_t *frame) {
  uint8_t sum = 0;
  for (uint8_t index = 1; index < FRAME_LENGTH - 1; ++index) {
    sum = static_cast<uint8_t>(sum + frame[index]);
  }
  return static_cast<uint8_t>(~sum + 1);
}

bool ZE40BTVOC::consume(uint8_t value, Reading &reading) {
  if (_index == 0) {
    if (value == START_BYTE) {
      _frame[_index++] = value;
    }
    return false;
  }

  _frame[_index++] = value;
  if (_index < FRAME_LENGTH) {
    return false;
  }

  const bool valid = decodeFrame(_frame, reading);
  if (valid) {
    float compensated = static_cast<float>(reading.tvocPpb) - _baselineOffset;
    reading.tvocPpb = compensated > 0.0f ? static_cast<uint16_t>(compensated) : 0;
  }
  
  _index = (value == START_BYTE) ? 1 : 0;
  if (_index == 1) {
    _frame[0] = START_BYTE;
  }
  return valid;
}

bool ZE40BTVOC::decodeFrame(const uint8_t *frame, Reading &reading) {
  if (frame[0] != START_BYTE || frame[1] != GAS_TVOC ||
      checksum(frame) != frame[FRAME_LENGTH - 1]) {
    return false;
  }

  reading.unit = frame[2];
  reading.decimals = frame[3];
  reading.tvocPpb = (static_cast<uint16_t>(frame[4]) << 8) | frame[5];
  reading.fullScale = (static_cast<uint16_t>(frame[6]) << 8) | frame[7];
  return true;
}
