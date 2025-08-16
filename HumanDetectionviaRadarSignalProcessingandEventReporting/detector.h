#ifndef DETECTOR_H
#define DETECTOR_H

#include <time.h>
#include <stddef.h>
#include "common.h"

typedef struct {
    size_t index;
    double value;
    double baseline;   // threshold or moving-average used
    time_t ts;
} DetectionEvent;

typedef struct {
    DetectionEvent *events;
    size_t count;
} DetectionList;

int detect_threshold(const double data[], int n, double threshold,
                     DetectionList *out);
int detect_moving_average(const double data[], int n, int window, double threshold,
                          DetectionList *out);
void free_detections(DetectionList *dl);

#endif
