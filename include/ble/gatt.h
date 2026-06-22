/** @file include/ble/gatt.h
 *  @brief Mota BLE GATT 服务接口定义。
 */
#pragma once

#include "esp_err.h"
#include "host/ble_uuid.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 注册 Mota GATT 服务和 characteristic。
 * @return 注册成功返回 ESP_OK。
 */
esp_err_t ble_gatt_init(void);
/**
 * @brief 获取 Mota 主服务 UUID，供广播包声明服务使用。
 * @return Mota 主服务 UUID 指针。
 */
const ble_uuid128_t *ble_gatt_service_uuid(void);

#ifdef __cplusplus
}
#endif
