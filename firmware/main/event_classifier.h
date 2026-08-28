#ifndef EVENT_CLASSIFIER_H
#define EVENT_CLASSIFIER_H

#include "config.h"

void event_classifier_init(void);
event_severity_t event_classifier_evaluate(float hr_bpm, float rr_ms, float sqi, bool lead_off, char *reason_out);

#endif // EVENT_CLASSIFIER_H
