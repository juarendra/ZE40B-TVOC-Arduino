#pragma once

#include <Arduino.h>

/** Driver for the Winsen ZE40B-TVOC initiative-upload UART protocol. */
class ZE40BTVOC {
public:
  static constexpr uint32_t BAUD_RATE = 9600;
  static constexpr uint8_t FRAME_LENGTH = 9;
  static constexpr uint8_t START_BYTE = 0xFF;
  static constexpr uint8_t GAS_TVOC = 0x34;

  struct Reading {
    uint16_t tvocPpb;
    uint8_t unit;
    uint8_t decimals;
    uint16_t fullScale;
  };

  explicit ZE40BTVOC(Stream &serial);

  /** Clear incomplete data. Configure the supplied serial port for 9600 8N1 first. */
  void begin();

  /** Consume available UART bytes and return the newest validated TVOC frame. */
  bool read(Reading &reading);

  /** Consume available UART bytes and return only the concentration in ppb. */
  bool readTVOC(uint16_t &tvocPpb);

  /** Parse the last valid ZE40B-TVOC frame in a byte buffer. */
  static bool parse(const uint8_t *buffer, size_t length, Reading &reading);

  /** Winsen checksum: two's complement of bytes 1 through 7. */
  static uint8_t checksum(const uint8_t *frame);

private:
  bool consume(uint8_t value, Reading &reading);
  static bool decodeFrame(const uint8_t *frame, Reading &reading);

  Stream &_serial;
  uint8_t _frame[FRAME_LENGTH];
  uint8_t _index;
};
