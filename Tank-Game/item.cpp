#include "item.h"

//===================扩展部分函数===============

//负责人secret
//功能：判断坦克是否拾取“爱心”，若拾取则实现回血效果，该生成点type归空。
//参数：坦克结构体
//返回值：空
void ifaddhp(Tank* tank, int newX, int newY) {
	// 1. 窗口边界检测
	if (newX < 0 || newX + TANK_SIZE > 1300 || newY < 0 || newY + TANK_SIZE > 800) return; // 碰到边界，无法移动
	// 2. 遍历道具点
	for (int i = 0; i < 4; ++i) {
		if (items[currentLevel][i].type == TOOL_ADDHP) {
			// 获取道具左上角的像素坐标
			int ToolX = items[currentLevel][i].x;
			int ToolY = items[currentLevel][i].y;
			if (newX < ToolX + BLOCK_SIZE &&
				newX + TANK_SIZE > ToolX &&
				newY < ToolY + BLOCK_SIZE &&
				newY + TANK_SIZE > ToolY) {
				//玩家1
				if (tank->camp == CAMP_PLAYER1) {
					if (tank->HP != tank->Max_HP) tank->HP++;
					items[currentLevel][i].type = TOOL_EMPTY;
					items[currentLevel][i].exist = 0;
				}
				//玩家2
				else if (tank->camp == CAMP_PLAYER2) {
					if (tank->HP != tank->Max_HP) tank->HP++;
					items[currentLevel][i].type = TOOL_EMPTY;
					items[currentLevel][i].exist = 0;
				}
			}
		}
	}
}

//负责人：月缀墨宇
//功能：判断坦克是否拾取“强力子弹”，若拾取则下一发子弹伤害双倍，该生成点type归空。
//参数：坦克结构体
//返回值：空
void ifpowerbullet(Tank* tank, int newX, int newY) {
	// 1. 窗口边界检测
	if (newX < 0 || newX + TANK_SIZE > 1300 || newY < 0 || newY + TANK_SIZE > 800) return; // 碰到边界，无法移动
	// 2. 遍历道具点
	for (int i = 0; i < 4; ++i) {
		if (items[currentLevel][i].type == TOOL_POWERBULLET) {
			// 获取道具左上角的像素坐标
			int ToolX = items[currentLevel][i].x;
			int ToolY = items[currentLevel][i].y;
			if (newX < ToolX + BLOCK_SIZE &&
				newX + TANK_SIZE > ToolX &&
				newY < ToolY + BLOCK_SIZE &&
				newY + TANK_SIZE > ToolY) {
				//玩家1
				if (tank->camp == CAMP_PLAYER1) {
					Player1_SpecialBullet = 1;
					flag1 = 1;
					items[currentLevel][i].type = TOOL_EMPTY;
					items[currentLevel][i].exist = 0;
				}
				//玩家2
				else if (tank->camp == CAMP_PLAYER2) {
					Player2_SpecialBullet = 1;
					flag2 = 1;
					items[currentLevel][i].type = TOOL_EMPTY;
					items[currentLevel][i].exist = 0;
				}
			}
		}
	}
}

//负责人：淡写青春
//功能：判断坦克是否拾取“穿墙子弹”，若拾取则下一发子弹可穿墙，需要坦克与障碍物碰撞函数。该生成点type归空。
//参数：坦克结构体
//返回值：空
void ifspebullet(Tank* tank, int newX, int newY) {
	// 1. 窗口边界检测
	if (newX < 0 || newX + TANK_SIZE > 1300 || newY < 0 || newY + TANK_SIZE > 800) return; // 碰到边界，无法移动
	// 2. 遍历道具点
	for (int i = 0; i < 4; ++i) {
		if (items[currentLevel][i].type == TOOL_SPEBULLET) {
			// 获取道具左上角的像素坐标
			int ToolX = items[currentLevel][i].x;
			int ToolY = items[currentLevel][i].y;
			if (newX < ToolX + BLOCK_SIZE &&
				newX + TANK_SIZE > ToolX &&
				newY < ToolY + BLOCK_SIZE &&
				newY + TANK_SIZE > ToolY) {
				//玩家1
				if (tank->camp == CAMP_PLAYER1) {
					Player1_SpecialBullet = 1;
					flag1 = TOOL_SPEBULLET;
					items[currentLevel][i].type = TOOL_EMPTY;
					items[currentLevel][i].exist = 0;
				}
				//玩家2
				else if (tank->camp == CAMP_PLAYER2) {
					Player2_SpecialBullet = 1;
					flag2 = TOOL_SPEBULLET;
					items[currentLevel][i].type = TOOL_EMPTY;
					items[currentLevel][i].exist = 0;
				}
			}
		}
	}
}
/*
	负责人：淡写青春
	功能：在没有道具的道具点间隔生成道具
	参数：无
	返回值：空
*/
void appearitems() {
	if (itemSpawnTimer >= 5000) {
		itemSpawnTimer = 0;
		for (int i = 0;i < MAX_ITEM_POS;i++) {
			if (items[currentLevel][i].exist) continue;
			//判定地块是否生成道具
			int chance = rand() % 100;
			if (chance < 50) {
				int num = rand() % 100;
				//30%生成血包
				if (num <= 30)items[currentLevel][i].type = TOOL_ADDHP;
				//30%生成强力子弹
				else if (num > 30 && num <= 60) {
					items[currentLevel][i].type = TOOL_POWERBULLET;
				}
				//40%生成穿墙弹
				else if (num > 60 && num < 100) {
					items[currentLevel][i].type = TOOL_SPEBULLET;
				}
				items[currentLevel][i].exist = 1;
			}
		}
	}
}
