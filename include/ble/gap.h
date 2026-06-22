/** @file include/ble/gap.h
 *  @brief BLE GAP 生命周期回调接口定义。
 */
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief NimBLE host reset 回调。
 * @param reason reset 原因码。
 */
void ble_gap_on_reset(int reason);
/** @brief NimBLE host sync 完成回调，负责推断地址并启动广播。 */
void ble_gap_on_sync(void);

#ifdef __cplusplus
}
#endif
