#include <stdio.h>
#include <stdlib.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include "game.h"
#include "player.h"
#include "enemy.h"

int main() {
    screenInit(1);
    keyboardInit();
    timerInit(100);

    Player player;
    initPlayer(&player);

    EnemyFormation formation;
    initEnemyFormation(&formation);

    Bullet bullet;
    initBullet(&bullet);

    while (1) {
        if (keyhit()) {
            char key = readch();
            if (key == 'q') break;
            if (key == 'a') player.speedX = -2; // Movimento mais rápido do jogador
            if (key == 'd') player.speedX = 2;  // Movimento mais rápido do jogador
            if (key == ' ') {
                if (!bullet.active) {
                    bullet.x = player.x;
                    bullet.y = player.y - 1;
                    bullet.active = 1;
                }
            }
        }

        if (timerTimeOver()) {
            updatePlayer(&player);
            updateBullet(&bullet);
            updateEnemyFormation(&formation);

            if (bullet.active && checkCollision(&bullet, &formation)) {
                bullet.active = 0; // Desativa o tiro após a colisão
            }

            if (checkGameOver(&formation)) {
                screenClear();
                screenGotoxy(MAXX / 2 - 5, MAXY / 2);
                printf("GAME OVER");
                break;
            }

            drawGame(&player, &formation, &bullet);
        }
    }

    keyboardDestroy();
    timerDestroy();
    screenDestroy();
    return 0;
}
