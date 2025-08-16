#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "radar.h"
#include "detector.h"
#include "logger.h"

static void usage(const char *prog) {
    printf("Usage: %s [--file <path>] [--count <n>] [--mode threshold|ma]\n"
           "          [--threshold <v>] [--window <n>] [--log <path>] [--bin <path>]\n", prog);
}

int main(int argc, char **argv) {
    const char *file = NULL;
    int count = 100;
    DetectMode mode = MODE_THRESHOLD;
    double threshold = DEFAULT_THRESHOLD;
    int window = DEFAULT_WINDOW;
    const char *log_path = "detections.log";
    const char *bin_path = NULL;

    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "--file") && i + 1 < argc) {
            file = argv[++i];
        } else if (!strcmp(argv[i], "--count") && i + 1 < argc) {
            count = atoi(argv[++i]);
        } else if (!strcmp(argv[i], "--mode") && i + 1 < argc) {
            const char *m = argv[++i];
            if (!strcmp(m, "threshold")) mode = MODE_THRESHOLD;
            else if (!strcmp(m, "ma")) mode = MODE_MOVING_AVG;
            else {
                fprintf(stderr, "Unknown mode: %s\n", m);
                return 1;
            }
        } else if (!strcmp(argv[i], "--threshold") && i + 1 < argc) {
            threshold = atof(argv[++i]);
        } else if (!strcmp(argv[i], "--window") && i + 1 < argc) {
            window = atoi(argv[++i]);
        } else if (!strcmp(argv[i], "--log") && i + 1 < argc) {
            log_path = argv[++i];
        } else if (!strcmp(argv[i], "--bin") && i + 1 < argc) {
            bin_path = argv[++i];
        } else {
            usage(argv[0]);
            return 1;
        }
    }

    double data[MAX_VALUES];
    int n = 0;

    if (file) {
        n = read_radar_data(file, data, MAX_VALUES);
        if (n < 0) {
            return 1;
        }
    } else {
        if (count > MAX_VALUES) count = MAX_VALUES;
        n = generate_random_data(data, count);
    }

    DetectionList dl;
    dl.events = NULL;
    dl.count = 0;

    int detections = 0;
    if (mode == MODE_THRESHOLD) {
        detections = detect_threshold(data, n, threshold, &dl);
    } else {
        detections = detect_moving_average(data, n, window, threshold, &dl);
    }

    if (detections <= 0) {
        printf("No detections.\n");
        free_detections(&dl);
        return 0;
    }

    print_events_console_and_json(&dl);

    if (log_events_text(log_path, &dl) == 0) {
        printf("Logged %zu detections to %s\n", dl.count, log_path);
    } else {
        fprintf(stderr, "Failed to write log file.\n");
    }

    if (bin_path) {
        if (write_events_binary(bin_path, &dl) == 0) {
            printf("Binary events written to %s\n", bin_path);
        } else {
            fprintf(stderr, "Failed to write binary events.\n");
        }
    }

    free_detections(&dl);
    return 0;
}
