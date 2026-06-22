/** @file src/ble/gap.c
 *  @brief BLE GAP 生命周期管理实现。
 */
#include "ble/gap.h"

#include "ble/advertising.h"
#include "ble/gatt.h"
#include "ble/stream.h"
#include "esp_log.h"
#include "host/ble_gap.h"
#include "host/ble_hs.h"

static const char *TAG = "ble_gap";  ///< 本模块日志标签。

static uint8_t own_addr_type;  ///< NimBLE 推断出的本机 BLE 地址类型。

static void ble_gap_advertise(void);

/** @brief 处理连接、断开和广播完成事件。 */
static int ble_gap_event(struct ble_gap_event *event, void *arg)
{
    (void)arg;

    ble_stream_on_gap_event(event);

    switch (event->type) {
    case BLE_GAP_EVENT_CONNECT:
        if (event->connect.status != 0) {
            ble_gap_advertise();
        }
        return 0;

    case BLE_GAP_EVENT_DISCONNECT:
        ble_gap_advertise();
        return 0;

    case BLE_GAP_EVENT_ADV_COMPLETE:
        ble_gap_advertise();
        return 0;

    default:
        return 0;
    }
}

/** @brief 使用当前地址类型和 GATT 主服务 UUID 启动广播。 */
static void ble_gap_advertise(void)
{
    int rc = ble_advertising_start(own_addr_type, ble_gatt_service_uuid(),
                                   ble_gap_event);  ///< 广播启动返回码。
    if (rc != 0) {
        ESP_LOGE(TAG, "advertising failed: %d", rc);
    }
}

void ble_gap_on_reset(int reason)
{
    ESP_LOGE(TAG, "NimBLE reset: %d", reason);
}

void ble_gap_on_sync(void)
{
    int rc = ble_hs_id_infer_auto(0, &own_addr_type);  ///< 地址类型推断返回码。
    if (rc != 0) {
        ESP_LOGE(TAG, "failed to infer address type: %d", rc);
        return;
    }

    ble_gap_advertise();
}
