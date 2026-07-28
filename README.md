# ZE40B-TVOC - Enterprise Gas Sensing Library

****Take absolute control of your air quality sensors with Q&A Polling.****

Read **TVOC ppb** cleanly • **Silence UART Spam with Q&A Mode** • **Low-Power Ready** • [**Built for IoT**](https://github.com/juarendra/ZE40B-TVOC-Arduino)

[![Build Status](https://github.com/juarendra/ZE40B-TVOC-Arduino/actions/workflows/build.yml/badge.svg)](https://github.com/juarendra/ZE40B-TVOC-Arduino/actions/workflows/build.yml) [![License](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE) [![Community](https://img.shields.io/badge/github-juarendra-orange.svg?logo=github)](https://github.com/juarendra)

## ⚡ Get Sensing in 30 Seconds

```cpp
#include <ZE40BTVOC.h>

ZE40BTVOC tvoc(Serial1);
ZE40BTVOC::Reading reading;

void setup() { 
  Serial.begin(115200);
  Serial1.begin(9600);
  tvoc.begin();
  tvoc.setMode(ZE40BTVOC::Mode::QuestionAnswer); // Silence!
}

void loop() {
  if (tvoc.requestRead(reading)) { // Active polling
    Serial.println(reading.tvocPpb);
  }
  delay(5000);
}
```

**✅ Works on ESP32, RP2040, Teensy, Arduino, and 50+ other platforms**

## Table of Contents
- [⚡ Quick Start](#-get-sensing-in-30-seconds)
- [🚀 Why This Library?](#-why-this-library)
- [📦 Installation](#-installation)
- [📄 License](#-license)

## 🚀 Why This Library?

| **Q&A Polling** | **Initiative Upload** | **Checksum Check** | **Universal** |
|---|---|---|---|
| Command 0x86 polling mode | Standard 1s upload mode | 100% data validation | Works on 50+ platforms |

**🎯 Performance**: Eliminates UART buffer overflow • Ultra-low CPU usage in Q&A mode.
**🔧 Developer Experience**: Mode selection enum • Built-in timeout handlers.

## 📦 Installation
1. Download this repository as a `.zip` file.
2. In the Arduino IDE, go to **Sketch > Include Library > Add .ZIP Library...**
3. Select the downloaded `.zip` file.
4. (Optional) Check the `examples/` directory for full usage.

## 📄 License
This project is licensed under the MIT License - see the LICENSE file for details.
