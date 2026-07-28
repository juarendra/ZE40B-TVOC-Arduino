# Changelog
All notable changes to this project will be documented in this file.

## [Unreleased]
### Added
- Implemented **Q&A Mode** support. Added `setMode(Mode)` allowing the sensor to switch between `Initiative` (active upload every 1s) and `QuestionAnswer` (polling mode).
- Added `requestRead(Reading &reading)` function to actively poll the sensor for data synchronously. This greatly saves UART processing time and makes the library suitable for low-power, multi-sensor IoT setups.
