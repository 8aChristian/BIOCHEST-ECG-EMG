#ifndef ALERT_MANAGER_H
#define ALERT_MANAGER_H

#include "config.h"
#include "esp_err.h"

esp_err_t sendEmergencyAlert(alert_channel_t channel, const event_data_t *event);

#endif // ALERT_MANAGER_H
