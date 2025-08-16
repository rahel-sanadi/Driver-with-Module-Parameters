#ifndef API_H
#define API_H

#include <stddef.h>
#include <stdint.h>

size_t pack_payload(float t, float lat, float lon, unsigned char *out);
void bytes_to_hex(const unsigned char *buf, size_t len, char *hex);
int parse_downlink_interval(const char *hex_msg);

#endif /* API_H */
