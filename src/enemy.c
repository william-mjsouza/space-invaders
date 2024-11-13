// enemy.c
#include <stdio.h>
#include "enemy.h"
#include "screen.h"

void initEnemyFormation(EnemyFormation *formation) {
    formation->x = 1;
    formation->y = 1;
    formation->speedX = 1;
    formation->speedY = 1;
    formation->direction = 1;
    
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
        formation->y += formation->speedY;
    }
}

void drawEnemyFormation(const EnemyFormation *formation) {
    for (int row = 0; row < ENEMY_ROWS; row++) {
        for (int col = 0; col < ENEMY_COLS; col++) {
            if (formation->alive[row][col]) {
                screenGotoxy(formation->x + col, formation->y + row);
                printf("E");
            }
        }
    }
}
