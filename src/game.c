// game.c
#include <stdio.h>
#include "game.h"
#include "screen.h"

void drawGame(const Player *player, const EnemyFormation *formation, const Bullet bullets[]) {
    screenClear();
    screenDrawBorders();
    drawPlayer(player);
    drawEnemyFormation(formation);
    drawBullets(bullets, MAX_BULLETS);
    screenHomeCursor();
}

int checkCollision(const Bullet *bullet, EnemyFormation *formation) {
    int bx = bullet->x;
    int by = bullet->y;

    for (int row = 0; row < ENEMY_ROWS; row++) {
        for (int col = 0; col < ENEMY_COLS; col++) {
            if (formation->alive[row][col]) {
                int ex = formation->x + col;
                int ey = formation->y + row;

                
                if (bx >= ex - 1 && bx <= ex + 1 && by >= ey - 1 && by <= ey + 1) {
                    formation->alive[row][col] = 0;
                    return 1;
                }
            }
        }
    }
    return 0;
}

int checkAllEnemiesDestroyed(const EnemyFormation *formation) {
    for (int row = 0; row < ENEMY_ROWS; row++) {
        for (int col = 0; col < ENEMY_COLS; col++) {
            if (formation->alive[row][col]) {
                return 0;  
            }
        }
    }
    return 1;  
}


int checkGameOver(const EnemyFormation *formation) {
    for (int row = 0; row < ENEMY_ROWS; row++) {
        for (int col = 0; col < ENEMY_COLS; col++) {
            if (formation->alive[row][col] && formation->y + row >= MAXY - 1) {
                return 1; 
            }
        }
    }
    return 0;
}
