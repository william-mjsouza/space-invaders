#include <stdio.h>
#include "player.h"
#include "screen.h"

void initPlayer(Player *player) {
    player->x = MAXX / 2;
    player->y = MAXY - 2;
    player->speedX = 0;
    player->speedY = 0;
}

void updatePlayer(Player *player) {
    player->x += player->speedX * 2; // Dobrar a velocidade horizontal
    player->y += player->speedY;

    if (player->x < 1) player->x = 1;
    if (player->x > MAXX - 2) player->x = MAXX - 2;
}

void drawPlayer(const Player *player) {
    screenGotoxy(player->x, player->y);
    printf("\033[35mM\033[0m");  // Representação do jogador em roxo
}

void initBullets(Bullet bullets[], int count) {
    for (int i = 0; i < count; i++) {
        bullets[i].x = 0;
        bullets[i].y = 0;
        bullets[i].active = 0;
    }
}

void updateBullets(Bullet bullets[], int count) {
    for (int i = 0; i < count; i++) {
        if (bullets[i].active) {
            bullets[i].y -= 2; // Movimenta a bala duas posições para cima
            if (bullets[i].y < 0) bullets[i].active = 0; // Desativa a bala se sair da tela
        }
    }
}

void drawBullets(const Bullet bullets[], int count) {
    for (int i = 0; i < count; i++) {
        if (bullets[i].active) {
            screenGotoxy(bullets[i].x, bullets[i].y);
            printf("\033[34m^\033[0m");  // Bala representada na cor azul
        }
    }
}
