# Milo-AI

文件作用：说明这个 Flutter/Dart 项目的来源、当前迁移范围和后续运行方式。

这是从 `/Users/jhb/Downloads/MyApplication_2026-06-03_19-42-46_extracted/MyApplication` 的 Android Kotlin + Jetpack Compose 项目裁剪迁移出来的 Flutter/Dart 版本。

当前已迁移的核心内容：

- 机器人主界面
- 表情状态和眼睛动画
- 移动控制页面
- 蓝牙设备页面结构
- 新手引导页面
- 全屏机器人表情展示

没有迁移的内容：

- 原 Android 项目的 release keystore
- 原 Android 项目的 `local.properties`
- 平台原生蓝牙实现

后续如果本机安装了 Flutter，可以在这个目录执行：

```bash
flutter create .
flutter pub get
flutter run
```

如果要恢复真实蓝牙扫描和连接，建议后续接入 Flutter 蓝牙插件，并把蓝牙逻辑封装到独立 service 文件中。
