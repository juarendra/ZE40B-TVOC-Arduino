# ZE40B-TVOC Arduino Library

Enterprise IoT Arduino library for the Winsen ZE40B-TVOC Gas Sensor.

## 🚀 Key Features & Upgrades
- **Q&A Polling Mode**: Take control of your UART bus! Switch the sensor to `QuestionAnswer` mode and only poll data when needed using `requestRead()`, saving cycles and battery.
- Supports standard `Initiative` (active upload) mode.
- Calculates PPB, full scale, and exact concentration.

## 📖 Usage Manual

```cpp
#include <ZE40BTVOC.h>

ZE40BTVOC tvoc(Serial1);
ZE40BTVOC::Reading reading;

void setup() {
  Serial.begin(115200);
  Serial1.begin(9600);
  
  tvoc.begin();
  tvoc.setMode(ZE40BTVOC::Mode::QuestionAnswer); // Silence the sensor!
}

void loop() {
  // Only read when YOU want to
  if (tvoc.requestRead(reading)) {
    Serial.print("TVOC (ppb): ");
    Serial.println(reading.tvocPpb);
  }
  delay(10000); // Sleep for 10 seconds
}
```

## 🛠 Installation
1. Download this repository as a `.zip` file.
2. In the Arduino IDE, go to **Sketch > Include Library > Add .ZIP Library...**
3. Select the downloaded `.zip` file.

## 📄 License
MIT License.
