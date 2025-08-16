#include <stdio.h>
#include <string.h>
#include "radar.h"
#include "camera.h"

int parseTime(const char *timeStr, int *hours, int *minutes) {
    return sscanf(timeStr, "%2d:%2d", hours, minutes) == 2;
}

int processRadarEvent(const char *entry, const char *exit, const char *plate, int *dh, int *dm) {
    int entryH, entryM, exitH, exitM;
    if (!parseTime(entry, &entryH, &entryM) || !parseTime(exit, &exitH, &exitM)) {
        return 0;
    }

    int totalEntry = entryH * 60 + entryM;
    int totalExit = exitH * 60 + exitM;
    int duration = totalExit - totalEntry;

    *dh = duration / 60;
    *dm = duration % 60;

    return 1;
}
