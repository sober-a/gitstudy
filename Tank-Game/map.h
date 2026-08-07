#ifndef MAP_H
#define MAP_H

#include "common.h"

// 地图数据存储
extern int map[MAX_LEVEL][ROWS][COLS];
extern int enemiesSpawn[MAX_LEVEL][MAX_ENEMIES][2];
extern int playerSpawn[MAX_LEVEL][1][2];

void initMapData01();
void initMapData02();
void initMapData03();

#endif