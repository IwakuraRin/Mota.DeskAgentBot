/** @file src/protocol/protocol.c
 *  @brief JSON 协议序列化与反序列化实现。
 */
#include "protocol/protocol.h"

#include "cJSON.h"

protocol_json_t *protocol_json_parse(const char *json, size_t len)
{
    if (json == NULL) {
        return NULL;
    }

    return (protocol_json_t *)cJSON_ParseWithLength(json, len);
}

char *protocol_json_serialize_unformatted(const protocol_json_t *message)
{
    if (message == NULL) {
        return NULL;
    }

    return cJSON_PrintUnformatted((const cJSON *)message);
}

void protocol_json_delete(protocol_json_t *message)
{
    cJSON_Delete((cJSON *)message);
}

void protocol_json_free(char *json)
{
    cJSON_free(json);
}

bool protocol_json_is_valid(const char *json, size_t len)
{
    protocol_json_t *message = protocol_json_parse(json, len);  ///< 临时解析出的 JSON 对象。
    if (message == NULL) {
        return false;
    }

    protocol_json_delete(message);
    return true;
}
