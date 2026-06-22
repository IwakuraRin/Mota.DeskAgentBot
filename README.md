# Mota ESP32-S3 Firmware

[中文](README.zh-CN.md)

This repository is a standard ESP-IDF CMake project with a PlatformIO entry point.
It is intended to work for both VS Code PlatformIO users and VS Code ESP-IDF
extension users.

## Target

- Board profile: `esp32-s3-devkitc-1`
- ESP-IDF target: `esp32s3`
- Module class: ESP32-S3N16R8, 16 MB flash and 8 MB OPI PSRAM
- Serial monitor: `115200`
- Upload speed: `460800`

Shared hardware defaults live in `sdkconfig.defaults`. Generated files such as
`sdkconfig`, `.pio/`, and `build/` are intentionally ignored.

## VS Code + PlatformIO

Install the PlatformIO IDE extension and open this folder in VS Code.

The PlatformIO workflow uses `platformio.ini`:

```powershell
pio run
pio run -t upload
pio device monitor
```

In VS Code, the same actions are available from the PlatformIO toolbar.

## VS Code + ESP-IDF Extension

Install the Espressif ESP-IDF extension and open this folder in VS Code.

The ESP-IDF workflow uses the standard project files:

- `CMakeLists.txt`
- `src/CMakeLists.txt`
- `sdkconfig.defaults`

On first use, run `ESP-IDF: Select Current ESP-IDF Version` in VS Code and select
your local ESP-IDF installation. The selected setup is machine-specific, so it is
not stored in this repository's workspace settings.

Useful commands from the VS Code command palette:

```text
ESP-IDF: Set Espressif Device Target
ESP-IDF: SDK Configuration Editor
ESP-IDF: Build your Project
ESP-IDF: Flash your Project
ESP-IDF: Monitor your Device
```

Choose `esp32s3` as the target if the extension asks.
