# ZE40B-TVOC Feature Research & Roadmap

## 1. Missing Feature: Q&A Polling Mode
**Status:** Not Implemented
**Description:** The Winsen ZE40B-TVOC sensor is currently hardcoded in this library to only read data passively in "Initiative Upload" mode (where the sensor uncontrollably spams data every 1 second). This clogs the UART buffer and wastes microcontroller cycles. The sensor hardware natively supports a "Question & Answer" (Q&A) mode where it stays completely silent until explicitly requested to read by the microcontroller.
**Proposed Addition:** 
1. Implement `setMode(Mode)` allowing users to toggle between `Initiative` (0x40) and `QuestionAnswer` (0x41) modes using Winsen's standard `0xFF 0x01 0x78` command protocol.
2. Implement `requestRead()` allowing the Arduino to actively poll the sensor using the `0xFF 0x01 0x86` command. This will make the library significantly more robust for low-power and multi-sensor systems.
