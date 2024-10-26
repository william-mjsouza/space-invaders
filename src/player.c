#include "player.h"
#include "screen.h"

// Definindo a posição inicial do jogador
#define PLAYER_INIT_X (MAXX / 2)
#define PLAYER_INIT_Y (MAXY - 2)

int playerX = PLAYER_INIT_X;
int playerY = PLAYER_INIT_Y;

void initPlayer() {
    playerX = PLAYER_INIT_X;
    playerY = PLAYER_INIT_Y;
}

void drawPlayer() {
    screenGotoxy(playerX, playerY);
    printf("M"); // Caractere da nave do jogador
}