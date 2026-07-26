#include <ZE40BTVOC.h>

constexpr int ZE40B_RX_PIN = 12;  // Sensor TX -> ESP32 RX
constexpr int ZE40B_TX_PIN = 14;  // Sensor RX -> ESP32 TX

ZE40BTVOC sensor(Serial2);

void setup() {
  Serial.begin(115200);
  Serial2.begin(ZE40BTVOC::BAUD_RATE, SERIAL_8N1, ZE40B_RX_PIN, ZE40B_TX_PIN);
  sensor.begin();
}

void loop() {
  ZE40BTVOC::Reading reading{};
  if (sensor.read(reading)) {
    Serial.print("TVOC: ");
    Serial.print(reading.tvocPpb);
    Serial.print(" ppb, range: ");
    Serial.println(reading.fullScale);
  }
  delay(50);
}
