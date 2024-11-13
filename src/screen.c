// screen.c
#include <stdio.h>
#include <stdlib.h>
#include "screen.h"

void screenInit(int borders) {
    if (borders) screenDrawBorders();
}

void screenDestroy() {
    system("clear");
}

void screenClear() {
    system("clear");
}

void screenDrawBorders() {
    for (int x = 0; x < MAXX; x++) {
        printf("#");
    }
    for (int y = 1; y < MAXY; y++) {
        printf("#\n");
    }
}

void screenGotoxy(int x, int y) {
    printf("\033[%d;%dH", y + 1, x + 1);
}

void screenHomeCursor() {
    printf("\033[H");
}
