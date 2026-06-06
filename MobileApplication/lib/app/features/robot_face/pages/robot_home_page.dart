import 'package:flutter/material.dart';

import '../../../features/bluetooth/models/companion_connect_state.dart';
import '../../../shared/widgets/page_title.dart';
import '../../../shared/widgets/soft_cards.dart';
import '../models/companion_bot_mood.dart';
import '../widgets/home_header.dart';
import '../widgets/mood_grid.dart';
import '../widgets/robot_hero_card.dart';

class RobotHomePage extends StatelessWidget {
  const RobotHomePage({
    required this.mood,
    required this.connectState,
    required this.lastCommand,
    required this.aiMessage,
    required this.onMoodChange,
    required this.onFullScreenTap,
    required this.onAiCallTap,
    required this.onScanTap,
    required this.onConnectTap,
    required this.onMenuTap,
    super.key,
  });

  final CompanionBotMood mood;
  final CompanionConnectState connectState;
  final String lastCommand;
  final String aiMessage;
  final ValueChanged<CompanionBotMood> onMoodChange;
  final VoidCallback onFullScreenTap;
  final VoidCallback onAiCallTap;
  final VoidCallback onScanTap;
  final VoidCallback onConnectTap;
  final VoidCallback onMenuTap;

  @override
  Widget build(BuildContext context) {
    return SingleChildScrollView(
      padding: const EdgeInsets.fromLTRB(22, 18, 22, 126),
      child: Column(
        crossAxisAlignment: CrossAxisAlignment.start,
        children: [
          HomeHeader(onMenuTap: onMenuTap),
          const SizedBox(height: 16),
          RobotHeroCard(
            mood: mood,
            connectState: connectState,
            onTap: onFullScreenTap,
          ),
          const SizedBox(height: 14),
          Row(
            children: [
              Expanded(
                child: SoftActionCard(
                  title: 'AI 呼唤',
                  subtitle: '到我旁边',
                  emoji: '✨',
                  onTap: onAiCallTap,
                ),
              ),
              const SizedBox(width: 12),
              Expanded(
                child: SoftActionCard(
                  title: '蓝牙扫描',
                  subtitle: '打开扫描窗口',
                  emoji: '📡',
                  highlighted: true,
                  onTap: onScanTap,
                ),
              ),
            ],
          ),
          const SizedBox(height: 12),
          SoftActionCard(
            title: '快速连接',
            subtitle: '模拟连接 LinBot-01',
            emoji: '🤖',
            onTap: onConnectTap,
          ),
          const SizedBox(height: 18),
          const SectionTitle('Mood Expressions'),
          const SizedBox(height: 12),
          MoodGrid(currentMood: mood, onMoodChange: onMoodChange),
          const SizedBox(height: 16),
          const SectionTitle('Recent Activity'),
          const SizedBox(height: 12),
          ActivityItem(
            emoji: '💬',
            title: 'AI Feedback',
            subtitle: aiMessage,
            value: mood.title,
          ),
          ActivityItem(
            emoji: '🎮',
            title: 'Last Command',
            subtitle: lastCommand,
            value: statusText(connectState),
          ),
        ],
      ),
    );
  }
}
