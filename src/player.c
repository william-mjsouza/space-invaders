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
    player->x += player->speedX;
    player->y += player->speedY;

    if (player->x < 1) player->x = 1;
    if (player->x > MAXX - 2) player->x = MAXX - 2;
}

void drawPlayer(const Player *player) {
    screenGotoxy(player->x, player->y);
    printf("\033[35mM\033[0m"); // M roxo para o jogador
}

void initBullet(Bullet *bullet) {
    bullet->x = 0;
    bullet->y = 0;
    bullet->active = 0;
}

void updateBullet(Bullet *bullet) {
    if (bullet->active) {
        bullet->y -= 2; // Velocidade dobrada para a bala
        if (bullet->y < 0) bullet->active = 0;
    }
}

void drawBullet(const Bullet *bullet) {
    if (bullet->active) {
        screenGotoxy(bullet->x, bullet->y);
        printf("\033[34m^\033[0m"); // Bala azul
    }
}
