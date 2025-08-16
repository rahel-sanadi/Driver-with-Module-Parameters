#include "payload.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static void float_to_bytes(float value, uint8_t *bytes) {
    union {
        float f;
        uint8_t b[4];
    } converter;
    converter.f = value;
    for (int i = 0; i < 4; i++) {
        bytes[i] = converter.b[i];
    }
}

int create_payload(const SensorData *data, uint8_t *payload, size_t *payload_len) {
    if (!data || !payload || !payload_len) return -1;
    *payload_len = 12;

    float_to_bytes(data->temperature, payload);
    float_to_bytes(data->latitude, payload + 4);
    float_to_bytes(data->longitude, payload + 8);
    return 0;
}

void print_payload_hex(const uint8_t *payload, size_t payload_len) {
    for (size_t i = 0; i < payload_len; i++) {
        printf("%02X", payload[i]);
    }
    printf("\n");
}

int parse_downlink_message(const char *hex_msg, int *reporting_interval) {
    if (!hex_msg || !reporting_interval) return -1;

    size_t len = strlen(hex_msg);
    if (len != 8) return -2;

    for (size_t i = 0; i < len; i++) {
        if (!isxdigit((unsigned char)hex_msg[i])) return -3;
    }

    unsigned int value = 0;
    sscanf(hex_msg, "%08X", &value);
    *reporting_interval = (int)value;
    return 0;
}
