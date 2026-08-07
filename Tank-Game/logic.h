#ifndef LOGIC_H
#define LOGIC_H

#include "common.h"

int iswin();
void moveAndFire(struct Tank* tank);
int ifreducehp(struct Tank* tank, struct Bullet* bullet);
int canTankMove(struct Tank* tank, int newX, int newY);
int isbasetank(Base* base, Tank* tank);
void tank_init(Tank* tank, int x, int y, unsigned int seed);
void EnemyAI_RandomMove(struct Tank* tank, int past_time);
int EnemyAI_RandomShoot(struct Tank* tank, int past_time);
void tank_ai_update(Tank* tank, int past_time);
void updateEnemies();
int bullet_hit_wall(struct Bullet* bullet);
int bulletCollision(struct Bullet* bullet, int target_x, int target_y);
int FindNearest(struct Bullet* bullet, int& nearest_row, int& nearest_col);
void updateBullets();
void checkCollision(Tank* player);
int isbasebullet(Base base, Bullet bullet);

#endif
