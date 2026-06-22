/** @file src/ble/advertising.c
 *  @brief BLE 广播包配置与启动实现。
 */
#include "ble/advertising.h"

#include <string.h>

#include "esp_log.h"
#include "host/ble_hs.h"

static const char *TAG = "ble_advertising";  ///< 本模块日志标签。
static const char *BLE_ADVERTISING_NAME = "Mota";  ///< 广播包内的完整设备名称。

int ble_advertising_start(uint8_t own_addr_type,
                          const ble_uuid128_t *service_uuid,
                          ble_gap_event_fn *gap_event_cb)
{
    struct ble_gap_adv_params advertising_params;  ///< 可连接广播的 GAP 参数。
    struct ble_hs_adv_fields fields;               ///< Legacy advertising payload 字段集合。
    int rc;                                        ///< NimBLE API 返回码。

    memset(&fields, 0, sizeof(fields));
    fields.flags = BLE_HS_ADV_F_DISC_GEN | BLE_HS_ADV_F_BREDR_UNSUP;  ///< 通用可发现且不支持 BR/EDR。
    fields.name = (uint8_t *)BLE_ADVERTISING_NAME;                    ///< 完整本地名称字段内容。
    fields.name_len = strlen(BLE_ADVERTISING_NAME);                   ///< 完整本地名称字段长度。
    fields.name_is_complete = 1;                                      ///< 名称字段声明为完整名称。
    fields.uuids128 = (ble_uuid128_t[]){ *service_uuid };             ///< 广播声明的 128-bit 主服务 UUID。
    fields.num_uuids128 = 1;                                          ///< 128-bit 服务 UUID 数量。
    fields.uuids128_is_complete = 1;                                  ///< 服务 UUID 列表声明为完整列表。

    rc = ble_gap_adv_set_fields(&fields);
    if (rc != 0) {
        ESP_LOGE(TAG, "failed to set advertising fields: %d", rc);
        return rc;
    }

    memset(&advertising_params, 0, sizeof(advertising_params));
    advertising_params.conn_mode = BLE_GAP_CONN_MODE_UND;   ///< 使用可连接非定向广播。
    advertising_params.disc_mode = BLE_GAP_DISC_MODE_GEN;   ///< 使用通用发现模式。

    rc = ble_gap_adv_start(own_addr_type, NULL, BLE_HS_FOREVER,
                           &advertising_params, gap_event_cb, NULL);
    if (rc != 0) {
        ESP_LOGE(TAG, "failed to start advertising: %d", rc);
    }

    return rc;
}
