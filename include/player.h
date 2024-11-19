#ifndef PLAYER_H
#define PLAYER_H

#define MAX_BULLETS 5 

typedef struct {
    int x, y;
    int speedX, speedY;
} Player;

typedef struct {
    int x, y;
    int active;
} Bullet;

void initPlayer(Player *player);
void updatePlayer(Player *player);
void drawPlayer(const Player *player);
void initBullets(Bullet bullets[], int count);
void updateBullets(Bullet bullets[], int count);
void drawBullets(const Bullet bullets[], int count);

#endif