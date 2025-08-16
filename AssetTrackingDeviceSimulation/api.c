#include "api.h"
#include <string.h>
#include <stdio.h>

size_t pack_payload(float t, float lat, float lon, unsigned char *out) {
    memcpy(out, &t, sizeof(float));
    memcpy(out + sizeof(float), &lat, sizeof(float));
    memcpy(out + 2 * sizeof(float), &lon, sizeof(float));
    return 3 * sizeof(float);
}

void bytes_to_hex(const unsigned char *buf, size_t len, char *hex) {
    for (size_t i = 0; i < len; ++i) {
        sprintf(hex + (i * 2), "%02X", buf[i]);
    }
    hex[len * 2] = '\0';
}

static int hex2byte(const char *h, unsigned char *out) {
    unsigned int v;
    if (sscanf(h, "%2x", &v) != 1) return -1;
    *out = (unsigned char)v;
    return 0;
}

/* expects exactly 4 bytes (8 hex chars), big-endian */
int parse_downlink_interval(const char *hex_msg) {
    size_t n = strlen(hex_msg);
    if (n != 8) return -1;

    unsigned char b[4];
    for (int i = 0; i < 4; ++i) {
        if (hex2byte(hex_msg + i * 2, &b[i]) != 0) return -1;
    }

    unsigned int val = ((unsigned int)b[0] << 24) |
                       ((unsigned int)b[1] << 16) |
                       ((unsigned int)b[2] << 8)  |
                       (unsigned int)b[3];

    return (int)val;
}
