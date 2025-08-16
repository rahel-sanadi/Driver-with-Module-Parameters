#ifndef LOGGER_H
#define LOGGER_H

#include "detector.h"

int log_events_text(const char *path, const DetectionList *dl);
void print_events_console_and_json(const DetectionList *dl);
int write_events_binary(const char *path, const DetectionList *dl);

#endif
