#include <stdio.h>
#include "score.h"
#include "screen.h"

int score = 0;

void initScore() {
    score = 0;
}

void updateScore(int points) {
    score += points;
}

void drawScore() {
    screenGotoxy(2, MAXY + 1);
    printf("Score: %d", score);
}