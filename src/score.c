// score.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "score.h"
#include "screen.h"

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

void sortScores() {
    typedef struct {
        char name[30];
        double time;
    } ScoreEntry;

    ScoreEntry *entries = NULL;
    int count = 0;
    int capacity = 0;

    // Lê as pontuações do arquivo
    FILE *file = fopen("score.txt", "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo para leitura");
        return;
    }

    while (1) {
        ScoreEntry tempEntry;
        if (fscanf(file, "%29s %lf", tempEntry.name, &tempEntry.time) != 2) {
            break;
        }

        // Realoca o array se necessário
        if (count >= capacity) {
            capacity = (capacity == 0) ? 10 : capacity * 2;
            ScoreEntry *newEntries = realloc(entries, capacity * sizeof(ScoreEntry));
            if (newEntries == NULL) {
                perror("Erro ao alocar memória");
                free(entries);
                fclose(file);
                return;
            }
            entries = newEntries;
        }

        entries[count++] = tempEntry;
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
        free(entries);
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %.2f\n", entries[i].name, entries[i].time);
    }
    fclose(file);

    // Libera a memória alocada
    free(entries);
}

void getTopScores(char names[][30], double times[], int count) {
    FILE *file = fopen("score.txt", "r");
    if (file == NULL) {
        // Preenche com valores padrão se o arquivo não existir
        for (int i = 0; i < count; i++) {
            strcpy(names[i], "---");
            times[i] = 0.0;
        }
        return;
    }

    int i = 0;
    while (i < count) {
        if (fscanf(file, "%29s %lf", names[i], &times[i]) != 2) {
            break;
        }
        i++;
    }

    // Se houver menos entradas do que o solicitado, preenche o restante com valores padrão
    for (; i < count; i++) {
        strcpy(names[i], "---");
        times[i] = 0.0;
    }

    fclose(file);
}
