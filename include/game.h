// game.h
#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "enemy.h"


int checkAllEnemiesDestroyed(const EnemyFormation *formation);
int checkGameOver(const EnemyFormation *formation);

void drawGame(const Player *player, const EnemyFormation *formation, const Bullet bullets[]);
int checkCollision(const Bullet *bullet, EnemyFormation *formation);

#endif

