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

   
    fprintf(file, "%s %.2f\n", name, elapsedTime);
    fclose(file);

    
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

    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (entries[i].time > entries[j].time) {
                ScoreEntry temp = entries[i];
                entries[i] = entries[j];
                entries[j] = temp;
            }
        }
    }

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

    free(entries);
}

void getTopScores(char names[][30], double times[], int count) {
    FILE *file = fopen("score.txt", "r");
    if (file == NULL) {
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

    for (; i < count; i++) {
        strcpy(names[i], "---");
        times[i] = 0.0;
    }

    fclose(file);
}
