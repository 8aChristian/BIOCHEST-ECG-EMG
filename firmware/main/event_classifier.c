#include "event_classifier.h"
#include <stdio.h>
#include <string.h>

void event_classifier_init(void) {
    // Initialize state
}

event_severity_t event_classifier_evaluate(float hr_bpm, float rr_ms, float sqi, bool lead_off, char *reason_out) {
    if (lead_off || sqi < 0.5f) {
        if (reason_out) strcpy(reason_out, "Lead-off or poor contact detected");
        return EVENT_INVALID_SIGNAL;
    }

    if (hr_bpm > 150.0f) {
        if (reason_out) snprintf(reason_out, 64, "Sustained extreme tachycardia: HR=%.1f bpm", hr_bpm);
        return EVENT_CRITICAL;
    }
    if (hr_bpm < 45.0f) {
        if (reason_out) snprintf(reason_out, 64, "Severe bradycardia: HR=%.1f bpm", hr_bpm);
        return EVENT_CRITICAL;
    }
    if (hr_bpm > 105.0f || hr_bpm < 50.0f) {
        if (reason_out) snprintf(reason_out, 64, "Elevated/unusual heart rate: HR=%.1f bpm", hr_bpm);
        return EVENT_ALERT;
    }

    if (reason_out) strcpy(reason_out, "Normal sinus pattern");
    return EVENT_NORMAL;
}
