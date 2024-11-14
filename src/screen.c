#include <stdio.h>
#include <stdlib.h>
#include "screen.h"

void screenInit(int borders) {
    screenClear();
    if (borders) screenDrawBorders();
}

void screenDestroy() {
    screenClear();
}

void screenClear() {
    printf("\033[2J\033[H");  // Limpa a tela e move o cursor para o início
}

void screenDrawBorders() {
    for (int x = 0; x <= MAXX + 1; x++) {
        screenGotoxy(x, 0);
        printf("═");
        screenGotoxy(x, MAXY + 1);
        printf("═");
    }
    for (int y = 0; y <= MAXY + 1; y++) {
        screenGotoxy(0, y);
        printf("║");
        screenGotoxy(MAXX + 1, y);
        printf("║");
    }
    screenGotoxy(0, 0);
    printf("╔");
    screenGotoxy(MAXX + 1, 0);
    printf("╗");
    screenGotoxy(0, MAXY + 1);
    printf("╚");
    screenGotoxy(MAXX + 1, MAXY + 1);
    printf("╝");
}

void screenGotoxy(int x, int y) {
    printf("\033[%d;%dH", y + 1, x + 1);
}

void screenHomeCursor() {
    printf("\033[H");
}
