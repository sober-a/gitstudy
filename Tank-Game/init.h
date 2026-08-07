#ifndef INIT_H
#define INIT_H

#include "common.h"
#include "map.h"

void initMap(int level);
void initGame(int level);
void initLevel(int level, const TileData tiles[], int count);
void baseinit();

#endif  