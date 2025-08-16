#ifndef RADAR_H
#define RADAR_H

#include <stddef.h>

int read_radar_data(const char *filename, double data[], size_t max_len);
int generate_random_data(double data[], int n);

#endif
