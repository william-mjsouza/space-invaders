// game.c
#include "game.h"
#include "screen.h"
#include "player.h"
#include "enemy.h"

void drawGame(const Player *player, const EnemyFormation *formation, const Bullet *bullet) {
    screenClear();
    screenDrawBorders();
    drawPlayer(player);
    drawEnemyFormation(formation);
    drawBullet(bullet);
    screenHomeCursor();
}

int checkCollision(const Bullet *bullet, EnemyFormation *formation) {
    for (int row = 0; row < ENEMY_ROWS; row++) {
        for (int col = 0; col < ENEMY_COLS; col++) {
            if (formation->alive[row][col] && bullet->x == formation->x + col && bullet->y == formation->y + row) {
                formation->alive[row][col] = 0;
                return 1; // Colisão detectada
            }
        }
    }
    return 0;
}

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
