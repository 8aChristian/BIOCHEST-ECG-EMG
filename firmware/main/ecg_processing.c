#include "ecg_processing.h"
#include <string.h>
#include <math.h>

void ecg_dsp_init(pan_tompkins_state_t *st) {
    memset(st, 0, sizeof(pan_tompkins_state_t));
    st->adaptive_thresh = 0.05f;
    st->sqi_score = 1.0f;
}

bool ecg_dsp_process_sample(pan_tompkins_state_t *st, float raw_sample, float *filtered_out) {
    st->sample_counter++;

    // 1. High-Pass Filter (0.5 Hz)
    float hp = 0.995f * (st->hp_prev_y + raw_sample - st->hp_prev_x);
    st->hp_prev_x = raw_sample;
    st->hp_prev_y = hp;

    // 2. Low-Pass Filter (40 Hz)
    st->lp_val = st->lp_val + 0.35f * (hp - st->lp_val);
    if (filtered_out) *filtered_out = st->lp_val;

    // 3. Moving Window Integration & Peak Detection
    float sq = st->lp_val * st->lp_val;
    st->mwi_sum -= st->mwi_buffer[st->mwi_idx];
    st->mwi_buffer[st->mwi_idx] = sq;
    st->mwi_sum += sq;
    st->mwi_idx = (st->mwi_idx + 1) % 64;

    float mwi_val = st->mwi_sum / 64.0f;

    // 4. QRS Detection with 200ms Refractory Window
    if (mwi_val > st->adaptive_thresh && (st->sample_counter - st->last_qrs_sample) > 102) {
        uint32_t delta_samples = st->sample_counter - st->last_qrs_sample;
        st->last_qrs_sample = st->sample_counter;

        st->current_rr_ms = (delta_samples * 1000.0f) / SAMPLING_RATE_HZ;
        if (st->current_rr_ms > 200.0f && st->current_rr_ms < 2000.0f) {
            st->current_hr_bpm = 60000.0f / st->current_rr_ms;
        }

        // Adapt threshold
        st->adaptive_thresh = 0.4f * st->adaptive_thresh + 0.6f * (0.25f * mwi_val);
        return true; // QRS Beat Detected!
    }

    return false;
}
