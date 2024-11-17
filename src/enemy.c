// enemy.c
#include <stdio.h>
#include "enemy.h"
#include "screen.h"

void initEnemyFormation(EnemyFormation *formation, int difficulty) {
    formation->x = 1;
    formation->y = 1;
    formation->direction = 1;
    formation->verticalMoveCounter = 0;

    // Ajusta a velocidade com base na dificuldade
    switch (difficulty) {
        case 1: // Fácil
            formation->speedX = 1;
            formation->speedY = 1; // Menor velocidade de descida
            break;
        case 2: // Médio
            formation->speedX = 2;
            formation->speedY = 2;
            break;
        case 3: // Difícil
            formation->speedX = 2;
            formation->speedY = 3; // Maior velocidade de descida
            break;
        default:
            formation->speedX = 1;
            formation->speedY = 1;
    }

    // Inicializa todos os inimigos como "vivos"
    for (int row = 0; row < ENEMY_ROWS; row++) {
        for (int col = 0; col < ENEMY_COLS; col++) {
            formation->alive[row][col] = 1;
        }
    }
}

void updateEnemyFormation(EnemyFormation *formation) {
    formation->x += formation->speedX * formation->direction;

    if (formation->x <= 1 || formation->x + ENEMY_COLS >= MAXX - 1) {
        formation->direction *= -1;
    }

    // Incrementa o contador vertical
    formation->verticalMoveCounter += formation->speedY;

    if (formation->verticalMoveCounter >= SOME_THRESHOLD) {
        formation->y += 1; // Desce uma linha
        formation->verticalMoveCounter = 0;
    }
}

void drawEnemyFormation(const EnemyFormation *formation) {
    for (int row = 0; row < ENEMY_ROWS; row++) {
        for (int col = 0; col < ENEMY_COLS; col++) {
            if (formation->alive[row][col]) {
                screenGotoxy(formation->x + col, formation->y + row);
                printf("\033[31mM\033[0m"); // M vermelho para os inimigos
            }
        }
    }
}
