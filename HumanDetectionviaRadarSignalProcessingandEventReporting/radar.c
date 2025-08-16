#include "radar.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int read_radar_data(const char *filename, double data[], size_t max_len) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Error opening file");
        return -1;
    }
    int count = 0;
    while (count < (int)max_len && fscanf(fp, "%lf", &data[count]) == 1) {
        count++;
    }
    fclose(fp);
    return count;
}

int generate_random_data(double data[], int n) {
    srand((unsigned)time(NULL));
    for (int i = 0; i < n; i++) {
        data[i] = (rand() % 100) / 100.0; // 0.00 to 1.00
    }
    return n;
}
