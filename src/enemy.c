#include "enemy.h"
#include "screen.h"

#define NUM_ENEMIES_X 8
#define NUM_ENEMIES_Y 2
#define ENEMY_CHAR 'M'

void initEnemies() {
    // Inicialização estática dos inimigos
}

void drawEnemies() {
    for (int y = 0; y < NUM_ENEMIES_Y; y++) {
        for (int x = 0; x < NUM_ENEMIES_X; x++) {
            screenGotoxy(5 + x * 4, 2 + y * 2); // Espaçamento entre os inimigos
            printf("%c", ENEMY_CHAR);
        }
    }
}