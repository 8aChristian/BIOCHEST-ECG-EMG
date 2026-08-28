#include "alert_manager.h"
#include "esp_log.h"
#include "esp_http_client.h"
#include <stdio.h>

static const char *TAG = "ALERT_MGR";

// Standard Mandatory Non-Diagnostic Advisory Notice:
#define ALERT_DISCLAIMER "Se detectó una señal potencialmente anómala. Verifique al usuario y solicite evaluación médica/emergencias según corresponda."

esp_err_t sendEmergencyAlert(alert_channel_t channel, const event_data_t *event) {
    if (!event) return ESP_ERR_INVALID_ARG;

    ESP_LOGW(TAG, ">>> DISPATCHING EMERGENCY TELEMETRY ALERT <<<");
    ESP_LOGW(TAG, "Severity: %d | HR: %.1f bpm | Reason: %s",
             event->severity, event->heart_rate_bpm, event->reason);
    ESP_LOGW(TAG, "Advisory Notice: %s", ALERT_DISCLAIMER);

    // In a real device, credentials and bot token are securely read from encrypted NVS:
    // https://api.telegram.org/bot<SECURE_TOKEN>/sendMessage?chat_id=<ID>&text=<MSG>
    return ESP_OK;
}
