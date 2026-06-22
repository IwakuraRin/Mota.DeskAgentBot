# Mota ESP32-S3 固件

[English](README.md)

本仓库是一个标准 ESP-IDF CMake 项目，同时提供 PlatformIO 入口。
它面向两类 VS Code 用户：习惯使用 PlatformIO 插件的用户，以及习惯使用
ESP-IDF 插件的用户。

## 目标硬件

- 开发板配置：`esp32-s3-devkitc-1`
- ESP-IDF 目标：`esp32s3`
- 模组类型：ESP32-S3N16R8，16 MB Flash 和 8 MB OPI PSRAM
- 串口监视器波特率：`115200`
- 上传波特率：`460800`

共享硬件默认配置位于 `sdkconfig.defaults`。`sdkconfig`、`.pio/` 和 `build/`
等生成文件会被有意忽略。

## VS Code + PlatformIO

安装 PlatformIO IDE 插件，然后在 VS Code 中打开本文件夹。

PlatformIO 工作流使用 `platformio.ini`：

```powershell
pio run
pio run -t upload
pio device monitor
```

在 VS Code 中，也可以通过 PlatformIO 工具栏执行相同操作。

## VS Code + ESP-IDF 插件

安装 Espressif ESP-IDF 插件，然后在 VS Code 中打开本文件夹。

ESP-IDF 工作流使用标准项目文件：

- `CMakeLists.txt`
- `src/CMakeLists.txt`
- `sdkconfig.defaults`

首次使用时，在 VS Code 中运行 `ESP-IDF: Select Current ESP-IDF Version`，
并选择你本机的 ESP-IDF 安装。该选择和具体机器相关，因此不会写入本仓库的
工作区设置。

VS Code 命令面板中的常用命令：

```text
ESP-IDF: Set Espressif Device Target
ESP-IDF: SDK Configuration Editor
ESP-IDF: Build your Project
ESP-IDF: Flash your Project
ESP-IDF: Monitor your Device
```

如果插件要求选择目标芯片，请选择 `esp32s3`。
