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

// Função para salvar a pontuação no arquivo
void saveScoreToFile(const char *name, double elapsedTime) {
    FILE *file = fopen("score.txt", "a+");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    // Escreve a nova pontuação no arquivo
    fprintf(file, "%s %.2f\n", name, elapsedTime);
    fclose(file);

    // Agora ordena o arquivo do menor tempo para o maior
    sortScores();
}

// Função para ordenar as pontuações
void sortScores() {
    typedef struct {
        char name[30];
        double time;
    } ScoreEntry;

    ScoreEntry entries[100]; // Ajuste o tamanho conforme necessário
    int count = 0;

    // Lê as pontuações do arquivo
    FILE *file = fopen("score.txt", "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo para leitura");
        return;
    }

    while (fscanf(file, "%29s %lf", entries[count].name, &entries[count].time) == 2) {
        count++;
        if (count >= 100) break; // Evita overflow
    }
    fclose(file);

    // Ordena as entradas do menor tempo para o maior
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (entries[i].time > entries[j].time) {
                ScoreEntry temp = entries[i];
                entries[i] = entries[j];
                entries[j] = temp;
            }
        }
    }

    // Escreve as pontuações ordenadas de volta no arquivo
    file = fopen("score.txt", "w");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo para escrita");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %.2f\n", entries[i].name, entries[i].time);
    }
    fclose(file);
}
