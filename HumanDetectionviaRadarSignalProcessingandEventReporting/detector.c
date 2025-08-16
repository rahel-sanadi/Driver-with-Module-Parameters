#include "detector.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>

static int add_event(DetectionList *dl, size_t index, double value, double baseline, time_t ts) {
    size_t newCount = dl->count + 1;
    DetectionEvent *tmp = (DetectionEvent *)realloc(dl->events, newCount * sizeof(DetectionEvent));
    if (!tmp) return -1;
    dl->events = tmp;
    dl->events[dl->count].index = index;
    dl->events[dl->count].value = value;
    dl->events[dl->count].baseline = baseline;
    dl->events[dl->count].ts = ts;
    dl->count = newCount;
    return 0;
}

int detect_threshold(const double data[], int n, double threshold,
                     DetectionList *out) {
    out->events = NULL;
    out->count = 0;

    time_t base = time(NULL);
    for (int i = 0; i < n; i++) {
        if (data[i] >= threshold) {
            if (add_event(out, (size_t)i, data[i], threshold, base + i) != 0) {
                free_detections(out);
                return -1;
            }
        }
    }
    return (int)out->count;
}

static double moving_average(const double *data, int endIndex, int window) {
    double sum = 0.0;
    for (int i = endIndex - window + 1; i <= endIndex; i++) {
        sum += data[i];
    }
    return sum / (double)window;
}

int detect_moving_average(const double data[], int n, int window, double threshold,
                          DetectionList *out) {
    out->events = NULL;
    out->count = 0;

    if (window <= 0 || window > n) return 0;

    time_t base = time(NULL);
    for (int i = window - 1; i < n; i++) {
        double ma = moving_average(data, i, window);
        if (ma >= threshold) {
            if (add_event(out, (size_t)i, data[i], ma, base + i) != 0) {
                free_detections(out);
                return -1;
            }
        }
    }
    return (int)out->count;
}

void free_detections(DetectionList *dl) {
    if (!dl) return;
    free(dl->events);
    dl->events = NULL;
    dl->count = 0;
}
