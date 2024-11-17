// game.c
#include <stdio.h>
#include "game.h"
#include "screen.h"

// Função para desenhar o estado atual do jogo
void drawGame(const Player *player, const EnemyFormation *formation, const Bullet bullets[]) {
    screenClear();
    screenDrawBorders();
    drawPlayer(player);
    drawEnemyFormation(formation);
    drawBullets(bullets, MAX_BULLETS);
    screenHomeCursor();
}

// Função para verificar colisão entre balas e inimigos
int checkCollision(const Bullet *bullet, EnemyFormation *formation) {
    int bx = bullet->x;
    int by = bullet->y;

    for (int row = 0; row < ENEMY_ROWS; row++) {
        for (int col = 0; col < ENEMY_COLS; col++) {
            if (formation->alive[row][col]) {
                int ex = formation->x + col;
                int ey = formation->y + row;

                // Define uma área de colisão em torno do inimigo
                if (bx >= ex - 1 && bx <= ex + 1 && by >= ey - 1 && by <= ey + 1) {
                    formation->alive[row][col] = 0; // Marca o inimigo como destruído
                    return 1; // Colisão detectada
                }
            }
        }
    }
    return 0;
}

// Função para verificar se todos os inimigos foram destruídos
int checkAllEnemiesDestroyed(const EnemyFormation *formation) {
    for (int row = 0; row < ENEMY_ROWS; row++) {
        for (int col = 0; col < ENEMY_COLS; col++) {
            if (formation->alive[row][col]) {
                return 0;  // Ainda existem inimigos vivos
            }
        }
    }
    return 1;  // Todos os inimigos foram destruídos
}

// Função para verificar se o jogo acabou (inimigos alcançaram a linha inferior)
int checkGameOver(const EnemyFormation *formation) {
    for (int row = 0; row < ENEMY_ROWS; row++) {
        for (int col = 0; col < ENEMY_COLS; col++) {
            if (formation->alive[row][col] && formation->y + row >= MAXY - 1) {
                return 1; // Game Over
            }
        }
    }
    return 0;
}
