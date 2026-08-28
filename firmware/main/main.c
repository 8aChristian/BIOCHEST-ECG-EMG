#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include "config.h"
#include "ads1293_driver.h"
#include "ecg_processing.h"
#include "event_classifier.h"
#include "alert_manager.h"

static const char *TAG = "MAIN";

void app_main(void) {
    ESP_LOGI(TAG, "==================================================");
    ESP_LOGI(TAG, "%s %s Starting...", DEVICE_NAME, FIRMWARE_VERSION);
    ESP_LOGI(TAG, "Hardware: %s", HARDWARE_REVISION);
    ESP_LOGI(TAG, "==================================================");

    // 1. Initialize Non-Volatile Storage (NVS) with encryption
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    // 2. Initialize Hardware Subsystems
    ESP_ERROR_CHECK(ads1293_init());
    event_classifier_init();

    pan_tompkins_state_t dsp_state;
    ecg_dsp_init(&dsp_state);

    ESP_LOGI(TAG, "System operational. Entering continuous telemetry & QRS acquisition loop.");

    // Telemetry loop
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
