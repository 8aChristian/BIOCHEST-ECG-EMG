#ifndef ECG_PROCESSING_H
#define ECG_PROCESSING_H

#include "config.h"

typedef struct {
    float hp_prev_x;
    float hp_prev_y;
    float lp_val;
    float mwi_buffer[64];
    uint8_t mwi_idx;
    float mwi_sum;
    float adaptive_thresh;
    uint32_t last_qrs_sample;
    uint32_t sample_counter;
    float current_hr_bpm;
    float current_rr_ms;
    float sqi_score;
} pan_tompkins_state_t;

void ecg_dsp_init(pan_tompkins_state_t *st);
bool ecg_dsp_process_sample(pan_tompkins_state_t *st, float raw_sample, float *filtered_out);

#endif // ECG_PROCESSING_H
