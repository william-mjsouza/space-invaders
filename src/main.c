#include <stdio.h>
#include <stdlib.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include "game.h"
#include "player.h"
#include "enemy.h"
#include "score.h"

int main() {
    screenInit(1);
    keyboardInit();
    timerInit(100);

    Player player;
    initPlayer(&player);

    EnemyFormation formation;
    initEnemyFormation(&formation);

    Bullet bullets[MAX_BULLETS];
    initBullets(bullets, MAX_BULLETS);

    initScore();

    while (1) {
        if (keyhit()) {
            char key = readch();
            if (key == 'q') break;
            if (key == 'a') player.speedX = -1;
            if (key == 'd') player.speedX = 1;
            if (key == ' ') {
                for (int i = 0; i < MAX_BULLETS; i++) {
                    if (!bullets[i].active) {
                        bullets[i].x = player.x;
                        bullets[i].y = player.y - 1;
                        bullets[i].active = 1;
                        break;
                    }
                }
            }
        }

        if (timerTimeOver()) {
            updatePlayer(&player);
            updateBullets(bullets, MAX_BULLETS);
            updateEnemyFormation(&formation);

            for (int i = 0; i < MAX_BULLETS; i++) {
                if (bullets[i].active && checkCollision(&bullets[i], &formation)) {
                    bullets[i].active = 0;
                }
            }

            if (checkGameOver(&formation)) {
                screenClear();
                screenGotoxy(MAXX / 2 - 5, MAXY / 2);
                printf("GAME OVER");
                break;
            }

            if (checkAllEnemiesDestroyed(&formation)) {
                showFinalScore();
                
                char name[30];
                printf("Digite seu nome: ");
                scanf("%29s", name);

                saveScoreToFile(name);
                break;
            }

            drawGame(&player, &formation, bullets);
        }
    }

    keyboardDestroy();
    timerDestroy();
    screenDestroy();
    return 0;
}
