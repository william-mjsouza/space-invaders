#include <stdio.h>
#include <stdlib.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include "game.h"
#include "player.h"
#include "enemy.h"

int main() {
    screenInit(1);         // Inicializa a tela com bordas
    keyboardInit();        // Inicializa o teclado
    timerInit(100);        // Inicializa o timer com 100ms

    // Desenha o estado inicial do jogo
    initGame();            // Configura o jogo e inicializa o jogador e os inimigos
    drawGame();            // Exibe o jogador e os inimigos na tela

    // Loop principal do jogo
    while (1) {
        if (keyhit()) {    // Verifica se uma tecla foi pressionada
            char key = readch();
            if (key == 'q') break; // Sai do jogo com a tecla 'q'
        }

        if (timerTimeOver()) {
            drawGame();    // Atualiza o desenho do jogo (atualmente estático)
        }
    }

    // Finaliza os recursos
    keyboardDestroy();
    timerDestroy();
    screenDestroy();
    return 0;
}