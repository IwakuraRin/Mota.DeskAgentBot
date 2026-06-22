/** @file include/protocol/protocol.h
 *  @brief JSON 协议序列化与反序列化接口定义。
 */
#pragma once

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @brief 不暴露具体 JSON 库实现的 JSON 对象句柄。 */
typedef struct protocol_json protocol_json_t;

/**
 * @brief 将 JSON 文本反序列化为协议 JSON 对象。
 * @param json JSON 文本。
 * @param len JSON 文本长度。
 * @return 解析成功返回 JSON 对象，否则返回 NULL。
 */
protocol_json_t *protocol_json_parse(const char *json, size_t len);
/**
 * @brief 将协议 JSON 对象序列化为紧凑 JSON 文本。
 * @param message JSON 对象。
 * @return 序列化成功返回新分配的字符串，否则返回 NULL。
 */
char *protocol_json_serialize_unformatted(const protocol_json_t *message);
/**
 * @brief 释放反序列化得到的 JSON 对象。
 * @param message JSON 对象，可为 NULL。
 */
void protocol_json_delete(protocol_json_t *message);
/**
 * @brief 释放序列化得到的 JSON 文本。
 * @param json JSON 文本，可为 NULL。
 */
void protocol_json_free(char *json);
/**
 * @brief 检查输入文本是否为合法 JSON。
 * @param json JSON 文本。
 * @param len JSON 文本长度。
 * @return 合法 JSON 返回 true。
 */
bool protocol_json_is_valid(const char *json, size_t len);

#ifdef __cplusplus
}
#endif
