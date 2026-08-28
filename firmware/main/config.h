#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>
#include <stdbool.h>

// Device Metadata
#define DEVICE_NAME             "BIOCHEST-ECG-EMG"
#define FIRMWARE_VERSION        "v1.0.0-PROTOTYPE"
#define HARDWARE_REVISION       "HW-REV-A (4-Layer)"

// Hardware Pinout Definitions (ESP32-S3-MINI-1)
#define PIN_SPI_SCLK            12
#define PIN_SPI_MOSI            11
#define PIN_SPI_MISO            13
#define PIN_SPI_CS              10
#define PIN_ADS_DRDY            9

#define PIN_I2C_SDA             8
#define PIN_I2C_SCL             9

#define PIN_LED_STATUS          5
#define PIN_LED_ALERT           6
#define PIN_ADC_BATTERY         4

// Sampling & DSP Configuration
#define SAMPLING_RATE_HZ        512
#define ECG_BUFFER_SIZE         1024
#define WINDOW_PRE_EVENT_SEC    10
#define WINDOW_POST_EVENT_SEC   10

// Event Severity Codes
typedef enum {
    EVENT_NORMAL = 0,
    EVENT_SUSPECT,
    EVENT_ALERT,
    EVENT_CRITICAL,
    EVENT_INVALID_SIGNAL,
    EVENT_LOW_BATTERY,
    EVENT_COMM_FAILURE
} event_severity_t;

// Telemetry Alert Channels
typedef enum {
    CHANNEL_TELEGRAM = 0,
    CHANNEL_WHATSAPP_BACKEND,
    CHANNEL_SMS_GATEWAY
} alert_channel_t;

// Event Payload Structure
typedef struct {
    event_severity_t severity;
    uint32_t timestamp_unix;
    float heart_rate_bpm;
    float rr_interval_ms;
    float sqi_quality_index;
    bool lead_off_detected;
    uint8_t battery_soc_pct;
    char reason[64];
} event_data_t;

#endif // CONFIG_H
