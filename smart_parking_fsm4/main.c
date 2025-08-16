#include <stdio.h>
#include <stdlib.h>
#include "radar.h"

int main() {
    FILE *input = fopen("car_info.txt", "r");
    if (!input) {
        printf("Error: Could not open car_info.txt\n");
        return 1;
    }

    FILE *output = fopen("output.txt", "w");
    if (!output) {
        printf("Error: Could not open output.txt\n");
        fclose(input);
        return 1;
    }

    char entryTime[6], exitTime[6], plate[20];
    while (fscanf(input, "%5s %19s %5s", entryTime, plate, exitTime) == 3) {
        int durationHours, durationMinutes;
        int success = processRadarEvent(entryTime, exitTime, plate, &durationHours, &durationMinutes);
        if (success) {
            fprintf(output, "%s %02d:%02d\n", plate, durationHours, durationMinutes);
        }
    }

    fclose(input);
    fclose(output);
    return 0;
}
