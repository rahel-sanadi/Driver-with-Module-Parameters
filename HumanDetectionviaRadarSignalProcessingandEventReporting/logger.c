#include "logger.h"
#include <stdio.h>
#include <time.h>

static void format_ts(time_t t, char *buf, size_t n) {
    struct tm *tmv = localtime(&t);
    strftime(buf, n, "%Y-%m-%d %H:%M:%S", tmv);
}

int log_events_text(const char *path, const DetectionList *dl) {
    if (!dl) return -1;
    FILE *fp = fopen(path, "w");
    if (!fp) {
        perror("log file open");
        return -1;
    }
    char tsbuf[64];
    for (size_t i = 0; i < dl->count; i++) {
        format_ts(dl->events[i].ts, tsbuf, sizeof(tsbuf));
        fprintf(fp, "[%s] Human presence detected (value: %.2f)\n",
                tsbuf, dl->events[i].value);
    }
    fclose(fp);
    return 0;
}

void print_events_console_and_json(const DetectionList *dl) {
    if (!dl) return;
    char tsbuf[64];
    for (size_t i = 0; i < dl->count; i++) {
        format_ts(dl->events[i].ts, tsbuf, sizeof(tsbuf));

        printf("[%s] Human presence detected  (for %.2f)\n", tsbuf, dl->events[i].value);
        printf("{\"timestamp\": \"%s\", \"event\": \"Human presence detected\"}\n", tsbuf);
    }
}

int write_events_binary(const char *path, const DetectionList *dl) {
    if (!dl) return -1;
    FILE *fp = fopen(path, "wb");
    if (!fp) {
        perror("binary file open");
        return -1;
    }
    size_t wrote = fwrite(dl->events, sizeof(DetectionEvent), dl->count, fp);
    fclose(fp);
    return (wrote == dl->count) ? 0 : -1;
}
