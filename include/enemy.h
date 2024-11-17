// enemy.h
#ifndef ENEMY_H
#define ENEMY_H

#define ENEMY_ROWS 5
#define ENEMY_COLS 10
#define SOME_THRESHOLD 10 // Ajuste conforme necessário

typedef struct {
    int x, y;
    int speedX, speedY;
    int direction;
    int alive[ENEMY_ROWS][ENEMY_COLS];
    int verticalMoveCounter; // Novo atributo para controlar a descida
} EnemyFormation;

void initEnemyFormation(EnemyFormation *formation, int difficulty);
void updateEnemyFormation(EnemyFormation *formation);
void drawEnemyFormation(const EnemyFormation *formation);

#endif
