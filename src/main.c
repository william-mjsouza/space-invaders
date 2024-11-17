// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include "game.h"
#include "player.h"
#include "enemy.h"
#include "score.h"

// Função para exibir a tela de início
void showStartScreen(char *playerName, int *difficulty) {
    screenClear();
    screenDrawBorders();

    screenGotoxy(MAXX / 2 - 20, MAXY / 2 - 4);
    printf("Bem-vindo ao Space Invaders ASCII!");

    screenGotoxy(MAXX / 2 - 20, MAXY / 2 - 2);
    printf("Digite seu nome: ");
    scanf("%29s", playerName);

    screenGotoxy(MAXX / 2 - 20, MAXY / 2);
    printf("Escolha a dificuldade:");
    screenGotoxy(MAXX / 2 - 20, MAXY / 2 + 1);
    printf("1. Fácil");
    screenGotoxy(MAXX / 2 - 20, MAXY / 2 + 2);
    printf("2. Médio");
    screenGotoxy(MAXX / 2 - 20, MAXY / 2 + 3);
    printf("3. Difícil");
    screenGotoxy(MAXX / 2 - 20, MAXY / 2 + 5);
    printf("Selecione (1-3): ");

    int choice = 0;
    while (choice < 1 || choice > 3) {
        scanf("%d", &choice);
        if (choice < 1 || choice > 3) {
            screenGotoxy(MAXX / 2 - 20, MAXY / 2 + 6);
            printf("Escolha inválida. Tente novamente: ");
        }
    }

    *difficulty = choice;

    // Limpa o buffer de entrada
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    screenClear();
    screenDrawBorders();
    screenGotoxy(MAXX / 2 - 20, MAXY / 2);
    printf("Pressione Enter para iniciar o jogo...");
    getchar(); // Espera o usuário pressionar Enter
}

int main() {
    char playerName[30];
    int difficulty;

    screenInit(1);

    // Chama a tela de início antes de alterar as configurações do teclado
    showStartScreen(playerName, &difficulty);

    keyboardInit(); // Configura o teclado após a tela de início
    timerInit(100);

    Player player;
    initPlayer(&player);

    EnemyFormation formation;
    initEnemyFormation(&formation, difficulty);

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
        } else {
            player.speedX = 0;
        }

        if (timerTimeOver()) {
            updatePlayer(&player);
            updateBullets(bullets, MAX_BULLETS);
            updateEnemyFormation(&formation);

            for (int i = 0; i < MAX_BULLETS; i++) {
                if (bullets[i].active && checkCollision(&bullets[i], &formation)) {
                    bullets[i].active = 0;
                    updateScore(10); // Incrementa a pontuação ao destruir um inimigo
                }
            }

            if (checkGameOver(&formation)) {
                screenClear();
                screenGotoxy(MAXX / 2 - 5, MAXY / 2);
                printf("GAME OVER");
                break;
            }

            if (checkAllEnemiesDestroyed(&formation)) {
                showFinalScore(playerName);
                saveScoreToFile(playerName);
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
