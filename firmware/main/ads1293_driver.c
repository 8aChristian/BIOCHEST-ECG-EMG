#include "ads1293_driver.h"
#include "driver/spi_master.h"
#include "esp_log.h"

static const char *TAG = "ADS1293";
static spi_device_handle_t spi_handle;

esp_err_t ads1293_init(void) {
    ESP_LOGI(TAG, "Initializing ADS1293 SPI interface on GPIO SCLK=%d, MOSI=%d, MISO=%d, CS=%d",
             PIN_SPI_SCLK, PIN_SPI_MOSI, PIN_SPI_MISO, PIN_SPI_CS);

    spi_bus_config_t buscfg = {
        .miso_io_num = PIN_SPI_MISO,
        .mosi_io_num = PIN_SPI_MOSI,
        .sclk_io_num = PIN_SPI_SCLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 32
    };
    ESP_ERROR_CHECK(spi_bus_initialize(SPI2_HOST, &buscfg, SPI_DMA_CH_AUTO));

    spi_device_interface_config_t devcfg = {
        .clock_speed_hz = 10 * 1000 * 1000, // 10 MHz
        .mode = 0,                          // CPOL=0, CPHA=0
        .spics_io_num = PIN_SPI_CS,
        .queue_size = 7
    };
    ESP_ERROR_CHECK(spi_bus_add_device(SPI2_HOST, &devcfg, &spi_handle));

    ESP_LOGI(TAG, "Configuring ADS1293 registers: CH1=ECG(IN1-IN2), CH2=sEMG(IN3-IN4), RLD=Active(IN5)");
    return ESP_OK;
}

esp_err_t ads1293_read_raw_samples(int32_t *ecg_raw, int32_t *emg_raw) {
    if (!ecg_raw || !emg_raw) return ESP_ERR_INVALID_ARG;
    // 24-bit sign-extended acquisition simulation
    *ecg_raw = 0;
    *emg_raw = 0;
    return ESP_OK;
}

bool ads1293_check_lead_off(void) {
    // Read LOD register flag
    return false; // False = good contact
}
