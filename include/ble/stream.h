/** @file include/ble/stream.h
 *  @brief BLE JSON 行协议收发流接口定义。
 */
#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "esp_err.h"

struct ble_gap_event;  ///< NimBLE GAP 事件对象。
struct os_mbuf;        ///< NimBLE mbuf 链式数据缓冲区。

#ifdef __cplusplus
extern "C" {
#endif

/** @brief 收到完整 JSON 行时触发的回调。 */
typedef void (*ble_stream_rx_callback_t)(const char *json, size_t len);

extern uint16_t ble_stream_tx_value_handle;  ///< TX characteristic value handle。

/**
 * @brief 处理客户端写入 RX characteristic 的数据。
 * @param om NimBLE 写入数据 mbuf。
 * @return GATT access 回调返回码。
 */
int ble_stream_rx_write(struct os_mbuf *om);
/**
 * @brief 处理连接、订阅和 MTU 相关 GAP 事件。
 * @param event NimBLE GAP 事件。
 */
void ble_stream_on_gap_event(const struct ble_gap_event *event);
/**
 * @brief 通过 TX notification 发送一条 JSON 行。
 * @param json 要发送的 JSON 文本。
 * @param len JSON 文本长度。
 * @return 发送成功返回 ESP_OK。
 */
esp_err_t ble_stream_tx_json(const char *json, size_t len);
/**
 * @brief 查询 TX notification 是否可用。
 * @return 已连接且已订阅返回 true。
 */
bool ble_stream_tx_ready(void);
/**
 * @brief 设置 RX JSON 行回调。
 * @param callback 收到完整 JSON 行时调用的函数，可传 NULL 取消回调。
 */
void ble_stream_set_rx_callback(ble_stream_rx_callback_t callback);

#ifdef __cplusplus
}
#endif
