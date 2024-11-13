// player.h
#ifndef PLAYER_H
#define PLAYER_H

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
void initBullet(Bullet *bullet);
void updateBullet(Bullet *bullet);
void drawBullet(const Bullet *bullet);

#endif
