// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>       // Added for timing functions
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

        initScore();

        // Start timing the game
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
                    // End the game and display Game Over
                    endTime = clock();
                    elapsedTime = ((double)(endTime - startTime)) / CLOCKS_PER_SEC;

                    screenClear();
                    screenGotoxy(MAXX / 2 - 5, MAXY / 2);
                    printf("GAME OVER");

                    gameEnded = 1;
                    break;
                }

                if (checkAllEnemiesDestroyed(&formation)) {
                    // End the game and display Victory screen
                    endTime = clock();
                    elapsedTime = ((double)(endTime - startTime)) / CLOCKS_PER_SEC;

                    keyboardDestroy(); // Restore terminal settings for user input

                    // Display final score
                    screenClear();
                    screenGotoxy(MAXX / 2 - 10, MAXY / 2 - 2);
                    printf("Parabéns! Você venceu!");
                    screenGotoxy(MAXX / 2 - 10, MAXY / 2);
                    printf("Seu tempo: %.2f segundos", elapsedTime);
                    screenGotoxy(MAXX / 2 - 10, MAXY / 2 + 2);
                    printf("Digite seu nome: ");

                    char name[30];
                    fgets(name, sizeof(name), stdin);
                    // Remove newline character if present
                    size_t len = strlen(name);
                    if (len > 0 && name[len - 1] == '\n') {
                        name[len - 1] = '\0';
                    }

                    // Save the score
                    saveScoreToFile(name, elapsedTime);

                    // Ask if the player wants to play again
                    char choice;
                    screenGotoxy(MAXX / 2 - 10, MAXY / 2 + 4);
                    printf("Deseja jogar novamente? (S/N): ");
                    scanf(" %c", &choice);
                    // Clear input buffer
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF);

                    if (choice == 'S' || choice == 's') {
                        playAgain = 1;
                    } else {
                        playAgain = 0;
                    }

                    keyboardInit(); // Re-initialize keyboard for game input
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
