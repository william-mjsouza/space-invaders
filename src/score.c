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

void showFinalScore(const char *name) {
    screenClear();
    screenGotoxy(MAXX / 2 - 10, MAXY / 2);
    printf("Parabéns, %s!", name);
    screenGotoxy(MAXX / 2 - 10, MAXY / 2 + 1);
    printf("Pontuação Final: %d", score);
    screenGotoxy(MAXX / 2 - 10, MAXY / 2 + 3);
    printf("Pressione qualquer tecla para sair...");
    getchar(); // Espera o usuário pressionar Enter
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
