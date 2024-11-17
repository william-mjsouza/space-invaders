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
    printf("\033[35m"); // Código ANSI para roxo
    for (int x = 0; x <= MAXX; x++) {
        screenGotoxy(x, 0);
        printf("═");
        screenGotoxy(x, MAXY);
        printf("═");
    }
    for (int y = 0; y <= MAXY; y++) {
        screenGotoxy(0, y);
        printf("║");
        screenGotoxy(MAXX, y);
        printf("║");
    }
    screenGotoxy(0, 0);
    printf("╔");
    screenGotoxy(MAXX, 0);
    printf("╗");
    screenGotoxy(0, MAXY);
    printf("╚");
    screenGotoxy(MAXX, MAXY);
    printf("╝");
    printf("\033[0m"); // Restaura cor padrão
}

void screenGotoxy(int x, int y) {
    printf("\033[%d;%dH", y + 1, x + 1);
}

void screenHomeCursor() {
    printf("\033[H");
}
