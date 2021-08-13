/* timestamp.c: Timestamp Functions */

#include "timestamp.h"

#include <time.h>
#include <sys/time.h>

/**
 * Return current timestamp as a double.
 *
 * Utilizes gettimeofday for precision (accounting for seconds and
 * microseconds) and falls back to time (only account for seconds) if that
 * fails.
 **/
double timestamp() {
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    double seconds= current_time.tv_sec;
    double microseconds= current_time.tv_usec;

    double timestamp = seconds + (microseconds / 1000000.0);

    return timestamp;
}

/* vim: set expandtab sts=4 sw=4 ts=8 ft=c: */
