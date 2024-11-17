// enemy.h
#ifndef ENEMY_H
#define ENEMY_H

#define ENEMY_ROWS 5
#define ENEMY_COLS 10

typedef struct {
    int x, y;
    int speedX, speedY;
    int direction;
    int alive[ENEMY_ROWS][ENEMY_COLS];
} EnemyFormation;

void initEnemyFormation(EnemyFormation *formation);
void updateEnemyFormation(EnemyFormation *formation);
void drawEnemyFormation(const EnemyFormation *formation);

#endif