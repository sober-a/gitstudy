#ifndef VIEW_H
#define VIEW_H

#include "common.h"

void drawAlpha(int picture_x, int picture_y, IMAGE* picture);
void drawMainMenu();
void drawHelp();
void drawSelectLevel01();
void drawSelectLevel02();
void drawSelectLevel03();
void drawMap(int level);
void printMessage(Tank* player1);
void printMessage(Tank* player1, Tank* player2);
void printMessage(Tank* player1, Base* base);
void drawSetting();
int drawPause();
void drawTank(struct Tank* tank);
void drawBullet(struct Bullet* bullet);
void drawItems(struct Items* item);
void render();
void drawResult(int type);
int Defeat();
int Victory();
void drawBase();

#endif
