#include "sensor.h"
#include <stdlib.h>

static float randf(float min, float max) {
    return min + ((float)rand() / (float)RAND_MAX) * (max - min);
}

float gen_temperature(void) { return randf(-20.0f, 50.0f); }
float gen_latitude(void)    { return randf(-90.0f, 90.0f); }
float gen_longitude(void)   { return randf(-180.0f, 180.0f); }
