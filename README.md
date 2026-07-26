# ZE40B-TVOC Arduino Library

Arduino driver for the Winsen ZE40B-TVOC electrochemical TVOC sensor. The
sensor transmits an initiative-upload frame every second over UART at 9600 baud
(8 data bits, no parity, 1 stop bit). This library validates the checksum and
returns the most recent valid frame.

## Wiring

Connect sensor TX to the microcontroller RX and sensor RX to the
microcontroller TX. Configure the serial port at 9600 baud, 8N1. On the VIA
board the UART is isolated with an ADuM1201; the isolation does not change the
serial protocol.

## Example

```cpp
#include <ZE40BTVOC.h>

ZE40BTVOC sensor(Serial2);

void setup() {
  Serial2.begin(ZE40BTVOC::BAUD_RATE, SERIAL_8N1, 12, 14);
  sensor.begin();
}

void loop() {
  ZE40BTVOC::Reading reading;
  if (sensor.read(reading)) {
    // reading.tvocPpb contains the concentration in ppb.
  }
}
```

`read()` consumes all currently available bytes and returns the newest valid
frame. It is safe to call frequently; partial frames are retained until their
remaining bytes arrive.

## License

MIT. See [LICENSE](LICENSE).
