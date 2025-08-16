#ifndef COMMON_H
#define COMMON_H

#define MAX_VALUES 1000
#define DEFAULT_THRESHOLD 0.3
#define DEFAULT_WINDOW 3

typedef enum {
    MODE_THRESHOLD = 1,
    MODE_MOVING_AVG = 2
} DetectMode;

#endif
