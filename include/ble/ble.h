/** @file include/ble/ble.h
 *  @brief Mota BLE 对外控制接口定义。
 */
#pragma once

#include <stdbool.h>
#include <stddef.h>

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @brief 收到完整 JSON 消息时触发的回调。 */
typedef void (*ble_rx_json_callback_t)(const char *json, size_t len);

/**
 * @brief 初始化 NimBLE、GAP/GATT 服务和广播流程。
 * @return 初始化成功返回 ESP_OK。
 */
esp_err_t ble_init(void);
/**
 * @brief 通过 BLE TX characteristic 发送一条 JSON 文本消息。
 * @param json 要发送的 JSON 文本。
 * @param len JSON 文本长度。
 * @return 发送成功返回 ESP_OK。
 */
esp_err_t ble_tx_json(const char *json, size_t len);
/**
 * @brief 查询当前 BLE TX 通道是否可发送通知。
 * @return 已连接且客户端订阅 TX 通知返回 true。
 */
bool ble_tx_ready(void);
/**
 * @brief 设置 BLE RX 完整 JSON 消息回调。
 * @param callback 收到 JSON 消息时调用的函数，可传 NULL 取消回调。
 */
void ble_set_rx_json_callback(ble_rx_json_callback_t callback);

#ifdef __cplusplus
}
#endif
