// score.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "score.h"
#include "screen.h"

// Removemos a variável 'score' e funções relacionadas

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

// Função para obter os top scores
void getTopScores(char names[][30], double times[], int count) {
    typedef struct {
        char name[30];
        double time;
    } ScoreEntry;

    ScoreEntry entries[100]; // Ajuste o tamanho conforme necessário
    int totalEntries = 0;

    FILE *file = fopen("score.txt", "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo para leitura");
        // Preenche com valores padrão se o arquivo não existir
        for (int i = 0; i < count; i++) {
            strcpy(names[i], "---");
            times[i] = 0.0;
        }
        return;
    }

    while (fscanf(file, "%29s %lf", entries[totalEntries].name, &entries[totalEntries].time) == 2) {
        totalEntries++;
        if (totalEntries >= 100) break; // Evita overflow
    }
    fclose(file);

    // Copia os top 'count' scores para os arrays de saída
    for (int i = 0; i < count && i < totalEntries; i++) {
        strcpy(names[i], entries[i].name);
        times[i] = entries[i].time;
    }

    // Se houver menos entradas do que o solicitado, preenche o restante com valores padrão
    for (int i = totalEntries; i < count; i++) {
        strcpy(names[i], "---");
        times[i] = 0.0;
    }
}
