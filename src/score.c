// score.c 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void showFinalScore() {
    screenClear();
    screenGotoxy(MAXX / 2 - 5, MAXY / 2);
    printf("Pontuação Final: %d", score);
    screenGotoxy(MAXX / 2 - 5, MAXY / 2 + 2);
}

void saveScoreToFile(const char *name) {
    FILE *file = fopen("score.txt", "a");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }
    fprintf(file, "Nome: %s - Pontuação: %d\n", name, score);
    fclose(file);
}
