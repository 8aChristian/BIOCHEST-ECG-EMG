#ifndef ADS1293_DRIVER_H
#define ADS1293_DRIVER_H

#include "config.h"
#include "esp_err.h"

// Key ADS1293 Register Map
#define ADS1293_REG_CONFIG          0x00
#define ADS1293_REG_FLEX_CH1_CN     0x01
#define ADS1293_REG_FLEX_CH2_CN     0x02
#define ADS1293_REG_FLEX_CH3_CN     0x03
#define ADS1293_REG_RLD_CN          0x0C
#define ADS1293_REG_LOD_CN          0x12
#define ADS1293_REG_DATA_LOOP       0x50

esp_err_t ads1293_init(void);
esp_err_t ads1293_read_raw_samples(int32_t *ecg_raw, int32_t *emg_raw);
bool ads1293_check_lead_off(void);

#endif // ADS1293_DRIVER_H
