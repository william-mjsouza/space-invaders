// game.h
#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "enemy.h"

void drawGame(const Player *player, const EnemyFormation *formation, const Bullet *bullet);
int checkCollision(const Bullet *bullet, EnemyFormation *formation);
int checkGameOver(const EnemyFormation *formation);

#endif
