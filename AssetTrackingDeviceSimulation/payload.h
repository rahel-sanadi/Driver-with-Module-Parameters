#ifndef PAYLOAD_H
#define PAYLOAD_H

#include <stdint.h>
#include <stddef.h>   // Added for size_t

typedef struct {
    float temperature;
    float latitude;
    float longitude;
} SensorData;

int create_payload(const SensorData *data, uint8_t *payload, size_t *payload_len);
int parse_downlink_message(const char *hex_msg, int *reporting_interval);
void print_payload_hex(const uint8_t *payload, size_t payload_len);

#endif
