import 'package:flutter/material.dart';

import '../../theme/app_colors.dart';

class PrivacyMenuPanel extends StatelessWidget {
  const PrivacyMenuPanel({super.key});

  @override
  Widget build(BuildContext context) {
    return const Column(
      crossAxisAlignment: CrossAxisAlignment.start,
      children: [
        _PrivacyItem(
          title: '本地演示',
          body: '当前版本主要在本机展示界面和交互状态，不会主动上传机器人控制数据。',
        ),
        _PrivacyItem(
          title: '蓝牙连接',
          body: '后续接入真实蓝牙时，会仅用于发现设备、建立连接和发送控制指令。',
        ),
        _PrivacyItem(
          title: '头像图片',
          body: '相册图片只用于个人主页头像显示，后续如果加入云同步，会在这里补充更完整的说明。',
        ),
      ],
    );
  }
}

class _PrivacyItem extends StatelessWidget {
  const _PrivacyItem({
    required this.title,
    required this.body,
  });

  final String title;
  final String body;

  @override
  Widget build(BuildContext context) {
    return Padding(
      padding: const EdgeInsets.only(bottom: 14),
      child: Container(
        width: double.infinity,
        padding: const EdgeInsets.all(16),
        decoration: BoxDecoration(
          color: const Color(0xFFF5F5F2),
          borderRadius: BorderRadius.circular(22),
        ),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            Text(
              title,
              style: const TextStyle(
                color: AppColors.ink,
                fontSize: 15,
                fontWeight: FontWeight.w800,
              ),
            ),
            const SizedBox(height: 6),
            Text(
              body,
              style: const TextStyle(
                color: AppColors.muted,
                fontSize: 13,
                height: 1.45,
              ),
            ),
          ],
        ),
      ),
    );
  }
}
