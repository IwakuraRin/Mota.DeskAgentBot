import 'dart:typed_data';

enum AppMenuPanel {
  profile,
  privacy,
}

class MenuProfileState {
  const MenuProfileState({
    required this.nickname,
    required this.avatarEmoji,
    this.avatarImageBytes,
  });

  final String nickname;
  final String avatarEmoji;
  final Uint8List? avatarImageBytes;

  MenuProfileState copyWith({
    String? nickname,
    String? avatarEmoji,
    Uint8List? avatarImageBytes,
    bool clearAvatarImage = false,
  }) {
    return MenuProfileState(
      nickname: nickname ?? this.nickname,
      avatarEmoji: avatarEmoji ?? this.avatarEmoji,
      avatarImageBytes:
          clearAvatarImage ? null : avatarImageBytes ?? this.avatarImageBytes,
    );
  }
}
