# Milo-AI Flutter 文件结构说明

## 入口层

- `lib/main.dart`
  - Flutter 启动入口，只负责启动 `MiloAiApp`。
- `lib/app/app.dart`
  - 应用根组件，集中管理当前页面、机器人表情、蓝牙状态、菜单开关、全屏机器人开关。
- `lib/app/router/app_router.dart`
  - 底部导航 Tab 定义，包括图标和文案。

## 主题与通用组件

- `lib/app/shared/theme/app_colors.dart`
  - 全局颜色，页面、按钮、机器人屏幕颜色都从这里取。
- `lib/app/shared/theme/app_theme.dart`
  - Flutter 全局主题。
- `lib/app/shared/widgets/floating_bottom_bar.dart`
  - 底部悬浮导航栏和点击震动反馈。
- `lib/app/shared/widgets/page_title.dart`
  - 页面标题组件。
- `lib/app/shared/widgets/soft_cards.dart`
  - 首页/设置/活动卡片等柔和卡片组件。

## 菜单模块

- `lib/app/shared/widgets/app_menu_overlay.dart`
  - 菜单模块导出入口，兼容旧 import。
- `lib/app/shared/widgets/menu/app_menu_button.dart`
  - 右上角三条杠菜单按钮。
- `lib/app/shared/widgets/menu/app_menu_overlay.dart`
  - 菜单弹层、遮罩和过渡动画。
- `lib/app/shared/widgets/menu/app_menu_models.dart`
  - 菜单分段状态、个人主页头像/昵称状态模型。
- `lib/app/shared/widgets/menu/profile_menu_panel.dart`
  - 个人主页面板，负责昵称、头像预览、表情头像、相册头像选择。
- `lib/app/shared/widgets/menu/privacy_menu_panel.dart`
  - 隐私政策面板。

## 首页与机器人屏幕

- `lib/app/features/robot_face/pages/robot_home_page.dart`
  - 首页页面编排，只组合顶部、机器人卡片、AI/蓝牙操作、表情网格、最近活动。
- `lib/app/features/robot_face/widgets/home_header.dart`
  - 首页顶部问候语和菜单按钮。
- `lib/app/features/robot_face/widgets/robot_hero_card.dart`
  - 首页黑色机器人屏幕卡片。
- `lib/app/features/robot_face/widgets/mood_grid.dart`
  - 表情按钮网格。
- `lib/app/features/robot_face/widgets/robot_face_canvas.dart`
  - 机器人脸部、首页机器人预览、横屏沉浸机器人屏幕的绘制逻辑。
- `lib/app/features/robot_face/pages/immersive_robot_page.dart`
  - 横屏全屏机器人页面。
- `lib/app/features/robot_face/models/companion_bot_mood.dart`
  - 机器人表情枚举、表情颜色、标题文案。

## 蓝牙模块

- `lib/app/core/bluetooth/bluetooth_device_info.dart`
  - 蓝牙设备基础数据模型。
- `lib/app/core/bluetooth/bluetooth_discovery_service.dart`
  - 蓝牙发现服务，目前仍是模拟数据入口，后续真实蓝牙扫描优先改这里。
- `lib/app/features/bluetooth/models/companion_connect_state.dart`
  - 蓝牙连接状态。
- `lib/app/features/bluetooth/pages/robot_bluetooth_page.dart`
  - 蓝牙扫描、设备列表、连接弹窗页面。

## 控制与设置

- `lib/app/features/bot_control/models/companion_move_command.dart`
  - 移动指令模型。
- `lib/app/features/bot_control/pages/robot_control_page.dart`
  - Move 控制页面。
- `lib/app/features/settings/pages/robot_settings_page.dart`
  - Settings 页面。
- `lib/app/features/guide/pages/robot_beginner_guide_page.dart`
  - Guide 新手文档页面。

## 平台目录

- `android/`
  - Android 平台工程壳，模拟器和真机运行用。
- `ios/`
  - iOS 平台工程壳，后续需要 macOS + Xcode 才能真机构建。
- `test/widget_test.dart`
  - Flutter 基础启动测试。
