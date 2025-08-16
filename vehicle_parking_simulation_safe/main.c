#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sensor.h"
#include "api.h"

#define MAX_PAYLOAD 64

/* simple helper to safely read a line */
static void read_line(char *buf, size_t sz) {
    if (fgets(buf, (int)sz, stdin) == NULL) {
        buf[0] = '\0';
        return;
    }
    buf[strcspn(buf, "\n")] = '\0';
}

/* pack + print hex */
static void make_and_print_payload(float t, float lat, float lon) {
    unsigned char payload[MAX_PAYLOAD];
    size_t n = pack_payload(t, lat, lon, payload);

    char hex[MAX_PAYLOAD * 2 + 1];
    bytes_to_hex(payload, n, hex);

    printf("Payload (hex): %s\n", hex);
}

int main(void) {
    srand((unsigned)time(NULL));

    char line[64];
    int choice;

    printf("Select Test Case (1-5): ");
    if (!fgets(line, sizeof(line), stdin)) {
        fprintf(stderr, "read error\n");
        return 1;
    }
    choice = atoi(line);

    float t, lat, lon;
    char downlink[64];

    switch (choice) {
    case 1:
        /* Normal Run */
        printf("\n[TEST CASE 1: Normal Run]\n");

        printf("Temperature (-20..50) or Enter for random: ");
        read_line(line, sizeof(line));
        t = (line[0] == '\0') ? gen_temperature() : (float)atof(line);

        printf("Latitude (-90..90) or Enter for random: ");
        read_line(line, sizeof(line));
        lat = (line[0] == '\0') ? gen_latitude() : (float)atof(line);

        printf("Longitude (-180..180) or Enter for random: ");
        read_line(line, sizeof(line));
        lon = (line[0] == '\0') ? gen_longitude() : (float)atof(line);

        printf("\nSensor Data:\n");
        printf("  T = %.2f C, Lat = %.6f, Lon = %.6f\n", t, lat, lon);

        make_and_print_payload(t, lat, lon);

        printf("Downlink hex (e.g., 0000003C for 60s): ");
        read_line(downlink, sizeof(downlink));
        {
            int interval = parse_downlink_interval(downlink);
            if (interval < 0) {
                printf("Invalid downlink message.\n");
            } else {
                printf("Updated reporting interval: %d seconds\n", interval);
            }
        }
        break;

    case 2:
        /* Data Limits */
        printf("\n[TEST CASE 2: Data Limits]\n");
        printf("Min values (-20.0, -90.0, -180.0):\n");
        make_and_print_payload(-20.0f, -90.0f, -180.0f);

        printf("Max values (50.0, 90.0, 180.0):\n");
        make_and_print_payload(50.0f, 90.0f, 180.0f);

        printf("Downlink hex (e.g., 000000FF for 255s): ");
        read_line(downlink, sizeof(downlink));
        {
            int interval = parse_downlink_interval(downlink);
            if (interval < 0) {
                printf("Invalid downlink message.\n");
            } else {
                printf("Updated reporting interval: %d seconds\n", interval);
            }
        }
        break;

    case 3: {
        /* API Fail */
        printf("\n[TEST CASE 3: API Fail]\n");

        printf("Temperature or Enter for random: ");
        read_line(line, sizeof(line));
        t = (line[0] == '\0') ? gen_temperature() : (float)atof(line);

        printf("Latitude or Enter for random: ");
        read_line(line, sizeof(line));
        lat = (line[0] == '\0') ? gen_latitude() : (float)atof(line);

        printf("Longitude or Enter for random: ");
        read_line(line, sizeof(line));
        lon = (line[0] == '\0') ? gen_longitude() : (float)atof(line);

        make_and_print_payload(t, lat, lon);

        printf("Downlink hex (type INVALID to test): ");
        read_line(downlink, sizeof(downlink));
        if (parse_downlink_interval(downlink) < 0) {
            printf("Error: invalid downlink message.\n");
            return 1; /* non-zero exit as per requirement */
        } else {
            printf("This was supposed to fail, but parsed OK.\n");
        }
        break;
    }

    case 4:
        /* Empty Payload (we just skip packing and still parse downlink) */
        printf("\n[TEST CASE 4: Empty Payload]\n");
        printf("Output: (empty payload string)\n");

        printf("Downlink hex (e.g., 0000001E for 30s): ");
        read_line(downlink, sizeof(downlink));
        {
            int interval = parse_downlink_interval(downlink);
            if (interval < 0) {
                printf("Invalid downlink message.\n");
            } else {
                printf("Interval: %d seconds\n", interval);
            }
        }
        break;

    case 5:
        /* Interval Variety */
        printf("\n[TEST CASE 5: Interval Variety]\n");

        printf("Enter first downlink hex (e.g., 00000001 for 1s): ");
        read_line(downlink, sizeof(downlink));
        {
            int i1 = parse_downlink_interval(downlink);
            if (i1 < 0) printf("Interval 1 invalid.\n");
            else printf("Interval 1: %d seconds\n", i1);
        }

        printf("Enter second downlink hex (e.g., 00000384 for 900s): ");
        read_line(downlink, sizeof(downlink));
        {
            int i2 = parse_downlink_interval(downlink);
            if (i2 < 0) printf("Interval 2 invalid.\n");
            else printf("Interval 2: %d seconds\n", i2);
        }
        break;

    default:
        printf("Invalid choice.\n");
        return 1;
    }

    return 0;
}
