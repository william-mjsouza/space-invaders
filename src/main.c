// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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

    int playAgain = 1;
    while (playAgain) {
        clock_t startTime, endTime;
        double elapsedTime;

        Player player;
        initPlayer(&player);

        EnemyFormation formation;
        initEnemyFormation(&formation);

        Bullet bullets[MAX_BULLETS];
        initBullets(bullets, MAX_BULLETS);

        startTime = clock();

        int gameEnded = 0;
        while (!gameEnded) {
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
                    endTime = clock();
                    elapsedTime = ((double)(endTime - startTime)) / CLOCKS_PER_SEC;

                    keyboardDestroy(); 

                    screenClear();
                    screenGotoxy(MAXX / 2 - 10, MAXY / 2 - 2);
                    printf("GAME OVER");
                    screenGotoxy(MAXX / 2 - 10, MAXY / 2);
                    printf("Seu tempo: %.2f segundos", elapsedTime);

                    char choice;
                    screenGotoxy(MAXX / 2 - 10, MAXY / 2 + 2);
                    printf("Deseja jogar novamente? (S/N): ");
                    scanf(" %c", &choice);

                    int c;
                    while ((c = getchar()) != '\n' && c != EOF);

                    if (choice == 'S' || choice == 's') {
                        playAgain = 1;
                    } else {
                        playAgain = 0;
                    }

                    keyboardInit(); 
                    gameEnded = 1;
                    break;
                }

                if (checkAllEnemiesDestroyed(&formation)) {
                    endTime = clock();
                    elapsedTime = ((double)(endTime - startTime)) / CLOCKS_PER_SEC;

                    keyboardDestroy();

                    screenClear();
                    screenGotoxy(MAXX / 2 - 10, MAXY / 2);
                    printf("Digite seu nome: ");

                    char name[30];
                    fgets(name, sizeof(name), stdin);
                    size_t len = strlen(name);
                    if (len > 0 && name[len - 1] == '\n') {
                        name[len - 1] = '\0';
                    }

                    saveScoreToFile(name, elapsedTime);

                    char topNames[3][30];
                    double topTimes[3];
                    getTopScores(topNames, topTimes, 3);

                    screenClear();

                    screenGotoxy(MAXX / 2 - 15, 2);
                    printf("=== Top 3 Jogadores ===");
                    for (int i = 0; i < 3; i++) {
                        screenGotoxy(MAXX / 2 - 15, 4 + i);
                        printf("%d. %s - %.2f segundos", i + 1, topNames[i], topTimes[i]);
                    }

                    screenGotoxy(MAXX / 2 - 10, MAXY / 2 - 2);
                    printf("Parabéns! Você venceu!");
                    screenGotoxy(MAXX / 2 - 10, MAXY / 2);
                    printf("Seu tempo: %.2f segundos", elapsedTime);


                    char choice;
                    screenGotoxy(MAXX / 2 - 10, MAXY / 2 + 2);
                    printf("Deseja jogar novamente? (S/N): ");
                    scanf(" %c", &choice);

                    int c;
                    while ((c = getchar()) != '\n' && c != EOF);

                    if (choice == 'S' || choice == 's') {
                        playAgain = 1;
                    } else {
                        playAgain = 0;
                    }

                    keyboardInit(); 
                    gameEnded = 1;
                    break;
                }

                drawGame(&player, &formation, bullets);
            }
        }

        if (!playAgain) {
            break;
        }
    }

    keyboardDestroy();
    timerDestroy();
    screenDestroy();
    return 0;
}
