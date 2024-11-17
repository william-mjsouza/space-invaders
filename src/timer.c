// timer.c
#include <time.h>
#include <unistd.h>
#include "timer.h"

static int interval_ms;
static struct timespec last_time;

void timerInit(int interval) {
    interval_ms = interval;
    clock_gettime(CLOCK_MONOTONIC, &last_time);
}

int timerTimeOver() {
    struct timespec current_time;
    clock_gettime(CLOCK_MONOTONIC, &current_time);

    long elapsed = (current_time.tv_sec - last_time.tv_sec) * 1000 +
                   (current_time.tv_nsec - last_time.tv_nsec) / 1000000;

    if (elapsed >= interval_ms) {
        last_time = current_time;
        return 1;
    }
    return 0;
}

void timerDestroy() {
    // Não há nada específico para destruir no temporizador
}