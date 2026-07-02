// 文件作用：管理 Mota 文本对话的发送状态，并调用用户配置的大模型 API 获取回复。

import 'dart:async';
import 'dart:io';

import 'package:flutter/foundation.dart';

import '../../../core/llm/mota_llm_chat_client.dart';
import '../../../core/llm/mota_llm_settings_store.dart';
import '../models/mota_chat_message.dart';

class MotaChatController extends ChangeNotifier {
  MotaChatController({
    MotaLlmSettingsStore? settingsStore,
    MotaLlmChatClient? llmClient,
    HttpClient? httpClient,
    Duration timeout = const Duration(seconds: 30),
  })  : _settingsStore = settingsStore ?? MotaLlmSettingsStore(),
        _llmClient = llmClient ??
            MotaLlmChatClient(
              httpClient: httpClient,
              timeout: timeout,
            );

  final MotaLlmSettingsStore _settingsStore;
  final MotaLlmChatClient _llmClient;
  final List<MotaChatMessage> _messages = <MotaChatMessage>[];

  bool _isSending = false;
  String? _errorText;

  List<MotaChatMessage> get messages => List.unmodifiable(_messages);
  bool get isSending => _isSending;
  String? get errorText => _errorText;

  Future<void> send(String rawText) async {
    final text = rawText.trim();
    if (text.isEmpty || _isSending) {
      return;
    }

    _messages.add(_createMessage(MotaChatSender.user, text));
    final assistantMessage = _createMessage(MotaChatSender.assistant, '');
    _messages.add(assistantMessage);
    _isSending = true;
    _errorText = null;
    notifyListeners();

    try {
      await _requestReplyStream(assistantMessage.id);
    } on MotaChatException catch (error) {
      _removeEmptyAssistantMessage(assistantMessage.id);
      _errorText = error.message;
    } on MotaLlmChatException catch (error) {
      _removeEmptyAssistantMessage(assistantMessage.id);
      _errorText = error.message;
    } on TimeoutException {
      _removeEmptyAssistantMessage(assistantMessage.id);
      _errorText = 'Mota 响应超时，请稍后再试';
    } on SocketException {
      _removeEmptyAssistantMessage(assistantMessage.id);
      _errorText = '网络连接失败，请检查网络后再试';
    } on FormatException {
      _removeEmptyAssistantMessage(assistantMessage.id);
      _errorText = 'Mota 返回的数据格式无法识别';
    } catch (_) {
      _removeEmptyAssistantMessage(assistantMessage.id);
      _errorText = 'Mota 暂时没有回应，请稍后再试';
    } finally {
      _isSending = false;
      notifyListeners();
    }
  }

  void clearError() {
    if (_errorText == null) {
      return;
    }
    _errorText = null;
    notifyListeners();
  }

  Future<void> _requestReplyStream(String assistantMessageId) async {
    final profile = await _settingsStore.readSelectedProfile();
    if (profile == null || !profile.isReady) {
      throw const MotaChatException('请点击输入框左侧 + 添加并选择 AI');
    }

    await _llmClient.streamChatCompletion(
      profile: profile,
      messages: _chatMessagesPayload(),
      onText: (text) => _updateAssistantMessage(assistantMessageId, text),
    );
  }

  List<MotaLlmChatMessage> _chatMessagesPayload() {
    final start = (_messages.length - 20).clamp(0, _messages.length);
    final conversationMessages = _messages.skip(start).where((message) {
      return message.text.trim().isNotEmpty;
    }).map((message) {
      return MotaLlmChatMessage(
        role: message.isUser ? 'user' : 'assistant',
        content: message.text,
      );
    }).toList(growable: false);

    return <MotaLlmChatMessage>[
      const MotaLlmChatMessage(
        role: 'system',
        content: '你是 Mota，一个温柔、简洁、会陪用户聊天的机器人伙伴。',
      ),
      ...conversationMessages,
    ];
  }

  MotaChatMessage _createMessage(MotaChatSender sender, String text) {
    return MotaChatMessage(
      id: DateTime.now().microsecondsSinceEpoch.toString(),
      sender: sender,
      text: text,
      createdAt: DateTime.now(),
    );
  }

  void _updateAssistantMessage(String messageId, String text) {
    final index = _messages.indexWhere((message) => message.id == messageId);
    if (index == -1) {
      return;
    }

    _messages[index] = _messages[index].copyWith(text: text);
    notifyListeners();
  }

  void _removeEmptyAssistantMessage(String messageId) {
    final index = _messages.indexWhere((message) => message.id == messageId);
    if (index == -1 || _messages[index].text.trim().isNotEmpty) {
      return;
    }

    _messages.removeAt(index);
  }

  @override
  void dispose() {
    _llmClient.close(force: true);
    super.dispose();
  }
}

class MotaChatException implements Exception {
  const MotaChatException(this.message);

  final String message;
}
