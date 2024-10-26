#include "game.h"
#include "screen.h"
#include "player.h"
#include "enemy.h"

void initGame() {
    screenClear();           // Limpa a tela uma vez no início
    screenDrawBorders();      // Desenha as bordas uma vez no início
    initPlayer();             // Inicializa o jogador
    initEnemies();            // Inicializa os inimigos
}

void drawGame() {
    drawPlayer();             // Desenha apenas o jogador
    drawEnemies();            // Desenha apenas os inimigos
    screenHomeCursor();       // Retorna o cursor para o início
}