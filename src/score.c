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

// Removed showFinalScore() as we're using elapsed time now

void saveScoreToFile(const char *name, double elapsedTime) {
    FILE *file = fopen("score.txt", "a+");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    // Write the new score to the file
    fprintf(file, "%s %.2f\n", name, elapsedTime);
    fclose(file);

    // Now sort the file from highest time to lowest
    sortScores();
}

void sortScores() {
    typedef struct {
        char name[30];
        double time;
    } ScoreEntry;

    ScoreEntry entries[100]; // Adjust size as needed
    int count = 0;

    // Read scores from file
    FILE *file = fopen("score.txt", "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo para leitura");
        return;
    }

    while (fscanf(file, "%29s %lf", entries[count].name, &entries[count].time) == 2) {
        count++;
        if (count >= 100) break; // Prevent overflow
    }
    fclose(file);

    // Sort the entries from highest time to lowest
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (entries[i].time < entries[j].time) {
                ScoreEntry temp = entries[i];
                entries[i] = entries[j];
                entries[j] = temp;
            }
        }
    }

    // Write sorted scores back to file
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
