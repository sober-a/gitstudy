#include "logic.h"

unsigned int rand_int(unsigned int* seed) {
	*seed = (*seed * 1103515245 + 12345) & 0x7fffffff;
	return *seed;
}

//负责人：淡写青春
//功能：坦克移动和开火
//参数：坦克结构体
//返回值：空
//备注：其他涉及玩家坦克的函数需要调用两次
void moveAndFire(Tank* tank) {
	if (tank->alive == 0) return;

	// 冷却倒计时
	if (tank->shootCd > 0) tank->shootCd--;

	int newx = tank->x, newy = tank->y;

	// 根据阵营区分按键
	if (tank->camp == CAMP_PLAYER1) {
		// 玩家1：WASD 移动 + J 开火
		if (GetAsyncKeyState('W') & 0x8000) { newy -= tank->speed; tank->dir = DIR_UP; }
		else if (GetAsyncKeyState('S') & 0x8000) { newy += tank->speed; tank->dir = DIR_DOWN; }
		else if (GetAsyncKeyState('A') & 0x8000) { newx -= tank->speed; tank->dir = DIR_LEFT; }
		else if (GetAsyncKeyState('D') & 0x8000) { newx += tank->speed; tank->dir = DIR_RIGHT; }

		if ((GetAsyncKeyState('J') & 0x8000) && tank->shootCd == 0 && bulletCount < MAX_BULLETS) {
			bullets[bulletCount].x = tank->x + 15;
			bullets[bulletCount].y = tank->y;
			bullets[bulletCount].dir = tank->dir;
			bullets[bulletCount].exist = 1;
			bullets[bulletCount].speed = 15;
			bullets[bulletCount].owner = tank->camp;
			if (Player1_SpecialBullet == 1 && flag1 == TOOL_POWERBULLET) {
				bullets[bulletCount].type = TOOL_POWERBULLET;
			}
			else if (Player1_SpecialBullet == 1 && flag1 == TOOL_SPEBULLET) {
				bullets[bulletCount].type = TOOL_SPEBULLET;
			}
			else bullets[bulletCount].type = TOOL_EMPTY;
			bulletCount++;
			tank->shootCd = tank->shootCTime;

			// ========== 玩家1 开火音效 ==========
			if (g_soundEnabled) {
				mciSendString(L"play sfx from 0", NULL, 0, NULL);
			}
		}
	}
	else if (tank->camp == CAMP_PLAYER2) {
		// 玩家2：方向键移动 + 小键盘1开火
		if (GetAsyncKeyState(VK_UP) & 0x8000) { newy -= tank->speed; tank->dir = DIR_UP; }
		else if (GetAsyncKeyState(VK_DOWN) & 0x8000) { newy += tank->speed; tank->dir = DIR_DOWN; }
		else if (GetAsyncKeyState(VK_LEFT) & 0x8000) { newx -= tank->speed; tank->dir = DIR_LEFT; }
		else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) { newx += tank->speed; tank->dir = DIR_RIGHT; }

		if (((GetAsyncKeyState(VK_SPACE) & 0x8000) || (GetAsyncKeyState(0x61) & 0x8000)) && tank->shootCd == 0 && bulletCount < MAX_BULLETS) {
			bullets[bulletCount].x = tank->x + 15;
			bullets[bulletCount].y = tank->y;
			bullets[bulletCount].dir = tank->dir;
			bullets[bulletCount].exist = 1;
			bullets[bulletCount].speed = 15;
			bullets[bulletCount].owner = tank->camp;
			if (Player2_SpecialBullet == 1 && flag2 == TOOL_POWERBULLET) {
				bullets[bulletCount].type = TOOL_POWERBULLET;
			}
			else if (Player2_SpecialBullet == 1 && flag2 == TOOL_SPEBULLET) {
				bullets[bulletCount].type = TOOL_SPEBULLET;
			}
			else bullets[bulletCount].type = TOOL_EMPTY;
			bulletCount++;
			tank->shootCd = tank->shootCTime;

			// ========== 玩家2 开火音效 ==========
			if (g_soundEnabled) {
				mciSendString(L"play sfx from 0", NULL, 0, NULL);
			}
		}
	}
	else if (tank->camp == CAMP_ENEMY)	return;

	// 碰撞检测
	if (canTankMove(tank, newx, newy)) {
		tank->x = newx;
		tank->y = newy;
	}
	ifaddhp(tank, newx, newy);
	ifpowerbullet(tank, newx, newy);
	ifspebullet(tank, newx, newy);
}

//负责人：不羡仙
//功能：胜利失败  
//参数：基地结构体，坦克结构体
//返回值：1胜利，-1失败,0继续
int iswin() {
	// 单人模式
	if (gameState == STATE_PLAYING) {
		// 失败条件：玩家死亡
		if (player1.alive == 0) {
			drawResult(0);
			return -1;
		}
	}
	// 双人模式
	else if (gameState == STATE_DOUBLEPEOPLE) {
		// 失败条件：两名玩家全部阵亡
		if (player1.alive == 0 && player2.alive == 0) {
			drawResult(0);
			return -1;
		}
	}
	// 基地模式
	else if (gameState == STATE_BASE) {
		// 失败条件：基地被摧毁 或 玩家坦克阵亡
		if (base.hp <= 0 || player1.alive == 0) {
			drawResult(0);
			return -1;
		}
	}
	// 胜利条件：所有敌人都被消灭
	if (enemyCount <= 0) {
		drawResult(1);
		return 1;
	}
	return 0;
}
//负责人：x
//功能：坦克与基地是否碰撞
//参数：基地结构体，坦克结构体
//返回值：0=未碰撞，1=碰撞
int isbasetank(Base* base, Tank* tank) {
	int tank_left = tank->x;
	int tank_right = tank->x + TANK_SIZE;
	int tank_top = tank->y;
	int tank_bottom = tank->y + TANK_SIZE;
	int base_left = base->x;
	int base_right = base->x + BASE_SIZE;
	int base_top = base->y;
	int base_bottom = base->y + BASE_SIZE;
	if (tank_bottom<base_top || tank_top>base_bottom ||
		tank_left > base_right || base_left > tank_right) {
		return 0;
	}
	return 1;
}
//负责人： 苏念玖
//功能：子弹与基地是否碰撞
//参数：基地结构体，子弹结构体
//返回值：0=未，1=碰撞
int isbasebullet(Base base, Bullet bullet) {
	int snj_row, snj_col;
	int isBase = FindNearest(&bullet, snj_row, snj_col);
	if (isBase == WALL_JIDI) {
		if (bulletCollision(&bullet, base.x, base.y) == 1) {
			return 1;
		}
	}
	return 0;
}

/*
	负责人：x
	功能：检查某个格子是否为障碍物
	参数：dx, dy 像素坐标
	返回值：1=是障碍物, 0=不是
*/
int ifreducehp(struct Tank* tank, struct Bullet* bullet) {
	if (bullet->owner == tank->camp || bullet->exist == 0)	return 0;
	int tank_left = tank->x;
	int tank_right = tank->x + TANK_SIZE;
	int tank_top = tank->y;
	int tank_bottom = tank->y + TANK_SIZE;
	int bullet_left = bullet->x;
	int bullet_right = bullet->x + BULLET_SIZE;
	int bullet_top = bullet->y;
	int bullet_bottom = bullet->y + BULLET_SIZE;
	if (tank_bottom<bullet_top || tank_top>bullet_bottom ||
		tank_left > bullet_right || bullet_left > tank_right) {
		return 0;
	}
	return 1;
}

/*
	负责人：月缀墨宇
	功能：检查坦克是否可以移动（完全基于像素的AABB包围盒碰撞检测）//坦克与障碍物碰撞
	参数：tank, newX, newY
	返回值：1=可以移动, 0=不可以
*/
int canTankMove(struct Tank* tank, int newX, int newY) {
	// 1. 窗口边界检测
	if (newX < 0 || newX + TANK_SIZE > 1300 || newY < 0 || newY + TANK_SIZE > 800) {
		return 0; // 碰到边界，无法移动
	}

	// 2. 地图障碍物检测 
	for (int row = 0; row < ROWS; ++row) {
		for (int col = 0; col < COLS; ++col) {
			if (map[currentLevel][row][col] != 0) { // 遇到障碍物
				// 获取障碍物左上角的像素坐标
				int obstacleX = col * BLOCK_SIZE;
				int obstacleY = row * BLOCK_SIZE;


				if (newX < obstacleX + BLOCK_SIZE &&
					newX + TANK_SIZE > obstacleX &&
					newY < obstacleY + BLOCK_SIZE &&
					newY + TANK_SIZE > obstacleY) {
					return 0; // 发生碰撞，无法移动
				}
			}
		}
	}

	// 所有碰撞检测均未触发，说明新位置合法
	return 1;
}

/*
	负责人：苏念玖
	功能：子弹与障碍物碰撞
	参数：struct Bullet*
	返回值：0:子弹可移动，1：遇到不可破坏障碍物，2：遇到可破坏障碍物，3：遇到基地
*/
int bullet_hit_wall(struct Bullet* bullet)
{

	/*
		失效原因：
			1.超出地图(撞墙)
			2.子弹与障碍物碰撞
	*/
	// 1.判断是否超出地图
	if (bullet->dir == DIR_UP && bullet->y <= 0) {
		if (bullet->type == TOOL_SPEBULLET) bullet->exist = 0;
		return 1;
	}

	else if (bullet->dir == DIR_DOWN && bullet->y >= 780)
	{
		if (bullet->type == TOOL_SPEBULLET) bullet->exist = 0;
		return 1;
	}
	else if (bullet->dir == DIR_LEFT && bullet->x <= 0)
	{
		if (bullet->type == TOOL_SPEBULLET) bullet->exist = 0;
		return 1;
	}
	else if (bullet->dir == DIR_RIGHT && bullet->x >= 1280)
	{
		if (bullet->type == TOOL_SPEBULLET) bullet->exist = 0;
		return 1;
	}

	// 2.判断是否与障碍物碰撞

	int nearest_row = -1, nearest_col = -1; // 默认-1，表示该方向没有障碍物
	int reason = FindNearest(bullet, nearest_row, nearest_col);
	//不可破坏判断
	if (reason == GRASS_WALL || reason == DESERT_PYRAMID || reason == LAVA_STONE || reason == WASTELAND_GRASS || reason == WASTELAND_BOX
		|| reason == SNOW_ICE || reason == SNOW_SNOWMAN || reason == SNOW_TREE || reason == DARK_STONE)
	{
		reason = 1;
	}
	//基地判断
	else if (reason == WALL_BASE) {
		reason = 3;
	}
	//可破坏判断
	else if (reason != EMPTY)
	{
		reason = 2;
		clearRow = nearest_row;
		clearCol = nearest_col;
	}

	// 当前方向上有障碍物，进行碰撞检测
	if (reason == 1 || reason == 2)
	{
		// 由最近的障碍物 map[currentLevel][nearest_row][nearest_col]得到左上角顶点坐标
		int nearest_x = nearest_col * BLOCK_SIZE;
		int nearest_y = nearest_row * BLOCK_SIZE;
		if (bulletCollision(bullet, nearest_x, nearest_y))
		{
			return reason;
		}
	}
	else if (reason == 3) {
		//对基地的四个地块碰撞检测
		int checkisbase1 = bulletCollision(bullet, base.x, base.y);
		int checkisbase2 = bulletCollision(bullet, base.x + 50, base.y);
		int checkisbase3 = bulletCollision(bullet, base.x, base.y + 50);
		int checkisbase4 = bulletCollision(bullet, base.x + 50, base.y + 50);
		if (checkisbase1 || checkisbase2 || checkisbase3 || checkisbase4) {
			return reason;
		}
	}

	// 都没发生，返回(0)，继续移动
	return 0;
}

int bulletCollision(struct Bullet* bullet, int target_x, int target_y)
{
	// 碰撞检测逻辑，由于障碍物大小和坦克大小一样，所以可以共用这套逻辑，但不能用在坦克与障碍物的碰撞检测
	if (bullet->x < target_x + BLOCK_SIZE && bullet->x + BULLET_SIZE > target_x && bullet->y < target_y + BLOCK_SIZE && bullet->y + BULLET_SIZE > target_y)
	{
		return 1;
	}
	return 0;
}

int FindNearest(struct Bullet* bullet, int& nearest_row, int& nearest_col)
{

	// 由子弹坐标转换成子弹所在行列
	// 上边界所在行
	int row1 = bullet->y / BLOCK_SIZE;
	// 下边界所在行
	int row2 = (bullet->y + BULLET_SIZE) / BLOCK_SIZE;
	// 左边界所在列
	int col1 = bullet->x / BLOCK_SIZE;
	// 右边界所在列
	int col2 = (bullet->x + BULLET_SIZE) / BLOCK_SIZE;

	// 寻找子弹方向上最近的障碍物的行列信息 map[currentLevel][nearest_row][nearest_col]（若能找到）

	if (bullet->dir == DIR_UP)
	{
		// 寻找子弹上方最近的障碍物 map[currentLevel][nearest_row][nearest_col]
		if (col1 == col2)
		{
			for (int i = row1; i >= 0; i--)
			{
				if (map[currentLevel][i][col1] != 0)
				{
					nearest_row = i;
					nearest_col = col1;
					return map[currentLevel][nearest_row][nearest_col];
				}
			}
		}
		else
		{
			for (int i = row1; i >= 0; i--)
			{
				if (map[currentLevel][i][col1] != 0)
				{
					nearest_row = i;
					nearest_col = col1;
					return map[currentLevel][nearest_row][nearest_col];
				}
				if (map[currentLevel][i][col2] != 0)
				{
					nearest_row = i;
					nearest_col = col2;
					return map[currentLevel][nearest_row][nearest_col];
				}
			}
		}
	}
	else if (bullet->dir == DIR_DOWN)
	{
		// 寻找子弹下方最近的障碍物 map[currentLevel][nearest_row][nearest_col]
		if (col1 == col2)
		{
			for (int i = row2; i < ROWS; i++)
			{
				if (map[currentLevel][i][col1] != 0)
				{
					nearest_row = i;
					nearest_col = col1;
					return map[currentLevel][nearest_row][nearest_col];
				}
			}
		}
		else
		{
			for (int i = row2; i < ROWS; i++)
			{
				if (map[currentLevel][i][col1] != 0)
				{
					nearest_row = i;
					nearest_col = col1;
					return map[currentLevel][nearest_row][nearest_col];
				}
				if (map[currentLevel][i][col2] != 0)
				{
					nearest_row = i;
					nearest_col = col2;
					return map[currentLevel][nearest_row][nearest_col];
				}
			}
		}
	}
	else if (bullet->dir == DIR_LEFT)
	{
		// 寻找子弹左方最近的障碍物 map[currentLevel][nearest_row][nearest_col]
		if (row1 == row2)
		{
			for (int i = col1; i >= 0; i--)
			{
				if (map[currentLevel][row1][i] != 0)
				{
					nearest_row = row1;
					nearest_col = i;
					return map[currentLevel][nearest_row][nearest_col];
				}
			}
		}
		else
		{
			for (int i = col1; i >= 0; i--)
			{
				if (map[currentLevel][row1][i] != 0)
				{
					nearest_row = row1;
					nearest_col = i;
					return map[currentLevel][nearest_row][nearest_col];
				}
				if (map[currentLevel][row2][i] != 0)
				{
					nearest_row = row2;
					nearest_col = i;
					return map[currentLevel][nearest_row][nearest_col];
				}
			}
		}
	}
	else if (bullet->dir == DIR_RIGHT)
	{
		// 寻找子弹右方最近的障碍物 map[currentLevel][nearest_row][nearest_col]
		if (row1 == row2)
		{
			for (int i = col2; i < COLS; i++)
			{
				if (map[currentLevel][row1][i] != 0)
				{
					nearest_row = row1;
					nearest_col = i;
					return map[currentLevel][nearest_row][nearest_col];
				}
			}
		}
		else
		{
			for (int i = col2; i < COLS; i++)
			{
				if (map[currentLevel][row1][i] != 0)
				{
					nearest_row = row1;
					nearest_col = i;
					return map[currentLevel][nearest_row][nearest_col];
				}
				if (map[currentLevel][row2][i] != 0)
				{
					nearest_row = row2;
					nearest_col = i;
					return map[currentLevel][nearest_row][nearest_col];
				}
			}
		}
	}
	return EMPTY;
}

/*
	负责人：晨懿
	功能：敌方坦克的寻敌与开火
	参数：struct Tank*, int x,int y, unsigned int seed,past_time
	返回值：空
*/
void tank_init(Tank* tank, int x, int y, unsigned int seed) {
	tank->x = x;
	tank->y = y;
	tank->dir = DIR_DOWN;
	tank->seed = seed;
	tank->move_timer = 0;
	tank->shoot_timer = 0;

	tank->moveCTime = 300 + (rand_int(&tank->seed) % 500);  // 300~799ms
	tank->shootCTime = 800 + (rand_int(&tank->seed) % 1200); // 800~1999ms
}

void EnemyAI_RandomMove(struct Tank* tank, int past_time) {
	tank->move_timer += past_time;

	// 如果是基地模式，执行智能寻敌逻辑
	if (gameState == STATE_BASE) {
		// 计算到基地的距离
		int baseCenterX = base.x + BASE_SIZE / 2;
		int baseCenterY = base.y + BASE_SIZE / 2;
		int tankCenterX = tank->x + TANK_SIZE / 2;
		int tankCenterY = tank->y + TANK_SIZE / 2;
		int distToBase = (tankCenterX - baseCenterX) * (tankCenterX - baseCenterX) +
			(tankCenterY - baseCenterY) * (tankCenterY - baseCenterY);

		// 计算到玩家坦克的距离
		int playerCenterX = player1.x + TANK_SIZE / 2;
		int playerCenterY = player1.y + TANK_SIZE / 2;
		int distToPlayer = (tankCenterX - playerCenterX) * (tankCenterX - playerCenterX) +
			(tankCenterY - playerCenterY) * (tankCenterY - playerCenterY);

		// 检测玩家是否存活
		bool playerAlive = (player1.alive == 1);

		// 判断目标：玩家存活且距离较近时优先攻击玩家
		bool targetPlayer = false;
		if (playerAlive && distToPlayer < 500 * 500) {
			targetPlayer = true;
		}

		// 只有定时器到时间时才改变方向（保持方向稳定）
		if (tank->move_timer >= tank->moveCTime) {
			tank->move_timer = 0;
			tank->moveCTime = 200 + (rand_int(&tank->seed) % 400);  // 200~599ms 改变一次方向

			int targetX, targetY;
			if (targetPlayer) {
				targetX = player1.x + TANK_SIZE / 2;
				targetY = player1.y + TANK_SIZE / 2;
			}
			else {
				targetX = base.x + BASE_SIZE / 2;
				targetY = base.y + BASE_SIZE / 2;
			}

			int dx = targetX - tankCenterX;
			int dy = targetY - tankCenterY;

			// 判断主要移动方向（只选水平或垂直一个方向）
			if (abs(dx) > abs(dy)) {
				tank->dir = (dx > 0) ? DIR_RIGHT : DIR_LEFT;
			}
			else {
				tank->dir = (dy > 0) ? DIR_DOWN : DIR_UP;
			}

			// 如果太靠近目标，随机换方向避免贴脸
			if (targetPlayer) {
				if (distToPlayer < 100 * 100) {
					tank->dir = (rand_int(&tank->seed) % 4) + 1;
				}
			}
			else {
				if (distToBase < 120 * 120) {
					tank->dir = (rand_int(&tank->seed) % 4) + 1;
				}
			}
		}

		// 按当前方向移动
		int newX = tank->x;
		int newY = tank->y;
		switch (tank->dir) {
		case DIR_UP:    newY -= tank->speed; break;
		case DIR_DOWN:  newY += tank->speed; break;
		case DIR_LEFT:  newX -= tank->speed; break;
		case DIR_RIGHT: newX += tank->speed; break;
		default:
			tank->dir = DIR_DOWN;
			return;
		}

		if (canTankMove(tank, newX, newY)) {
			tank->x = newX;
			tank->y = newY;
		}
		else {
			// 被阻挡时立即换方向
			tank->dir = (rand_int(&tank->seed) % 4) + 1;
			tank->move_timer = 0;
		}
		return;
	}

	if (tank->move_timer >= tank->moveCTime) {
		tank->move_timer = 0;
		tank->moveCTime = 300 + (rand_int(&tank->seed) % 500);
		tank->dir = (rand_int(&tank->seed) % 4) + 1;
	}

	int newX = tank->x;
	int newY = tank->y;
	switch (tank->dir) {
	case DIR_UP:    newY -= tank->speed; break;
	case DIR_DOWN:  newY += tank->speed; break;
	case DIR_LEFT:  newX -= tank->speed; break;
	case DIR_RIGHT: newX += tank->speed; break;
	default:
		tank->dir = DIR_DOWN;
		return;
	}

	if (canTankMove(tank, newX, newY)) {
		tank->x = newX;
		tank->y = newY;
	}
	else {
		tank->dir = (rand_int(&tank->seed) % 4) + 1;
		tank->move_timer = 0;
	}
}
int EnemyAI_RandomShoot(struct Tank* tank, int past_time) {
	// 累加计时器
	tank->shoot_timer += past_time;

	// 时间到，执行开火
	if (tank->shoot_timer >= tank->shootCTime) {
		tank->shoot_timer = 0;

		// 重置随机间隔
		tank->shootCTime = 800 + (rand_int(&tank->seed) % 1200);

		return 1;  // 开火
	}

	return 0;
}
/*
	负责人：晨懿
	功能：敌方坦克AI更新
	参数：tank, past_time
	返回值：空
*/
void tank_ai_update(Tank* tank, int past_time) {
	if (tank->alive == 0) return;

	// 冷却倒计时
	if (tank->shootCd > 0) tank->shootCd -= past_time;

	EnemyAI_RandomMove(tank, past_time);

	if (EnemyAI_RandomShoot(tank, past_time)) {
		if (bulletCount < MAX_BULLETS) {
			bullets[bulletCount].x = tank->x + 15;
			bullets[bulletCount].y = tank->y;
			bullets[bulletCount].dir = tank->dir;
			bullets[bulletCount].exist = 1;
			bullets[bulletCount].speed = 5;
			bullets[bulletCount].owner = tank->camp;
			bullets[bulletCount].type = TOOL_EMPTY;
			bulletCount++;
			tank->shootCd = tank->shootCTime / 2;
		}
	}
}

/*
	负责人：淡写青春
	功能：更新所有子弹的位置与状态
	参数：无
	返回值：空
*/
void updateBullets() {
	for (int i = 0;i < bulletCount;i++) {
		if (bullets[i].exist == 0) continue;
		switch (bullets[i].dir) {
		case DIR_UP:
			bullets[i].y -= bullets[i].speed;
			if (bullets[i].y < 0) bullets[i].exist = 0;
			break;
		case DIR_DOWN:
			bullets[i].y += bullets[i].speed;
			if (bullets[i].y > 800) bullets[i].exist = 0;
			break;
		case DIR_LEFT:
			bullets[i].x -= bullets[i].speed;
			if (bullets[i].x < 0) bullets[i].exist = 0;
			break;
		case DIR_RIGHT:
			bullets[i].x += bullets[i].speed;
			if (bullets[i].x > 1500) bullets[i].exist = 0;
			break;
		}
	}
}

/*
	负责人：secret
	功能：检测场上所有子弹与坦克、子弹与障碍物的碰撞
	参数：无
	返回值：空
*/
void checkCollision(Tank* player) {
	// 遍历所有子弹
	for (int i = 0; i < bulletCount; i++) {
		if (bullets[i].exist == 0) continue;//逻辑要修改一下，有些障碍物可被摧毁
		// 1. 检测子弹是否撞不可破坏障碍物
		if (bullet_hit_wall(&bullets[i]) == 1) {
			if (bullets[i].type != TOOL_SPEBULLET) {
				bullets[i].exist = 0;
			}
			continue; // 子弹失效，跳过后续检测
		}
		//可破坏障碍物
		else if (bullet_hit_wall(&bullets[i]) == 2) {
			if (bullets[i].type != TOOL_SPEBULLET)
				bullets[i].exist = 0;
			map[currentLevel][clearRow][clearCol] = EMPTY;
			if (g_soundEnabled) {
				mciSendString(L"play hit_wall from 0", NULL, 0, NULL);
			}
			continue;
		}
		//打到基地：敌方子弹消失，基地扣血	/ 玩家子弹消失，基地不扣血
		else if (bullet_hit_wall(&bullets[i]) == 3) {
			if (bullets[i].owner == CAMP_ENEMY)
			{
				bullets[i].exist = 0;
				base.hp--;
				if (g_soundEnabled) {
					mciSendString(L"play hit_tank from 0", NULL, 0, NULL);
				}
				continue;
			}
			else {
				bullets[i].exist = 0;
				if (g_soundEnabled) {
					mciSendString(L"play hit_tank from 0", NULL, 0, NULL);
				}
				continue;
			}
		}

		// 2. 检测子弹与玩家坦克的碰撞
		if (player->alive && ifreducehp(player, &bullets[i])) {
			player->HP--;
			bullets[i].exist = 0;
			if (g_soundEnabled) {
				mciSendString(L"play hit_tank from 0", NULL, 0, NULL);
			}
			if (player->HP <= 0) {
				player->alive = 0;
			}
			continue;
		}

		// 3. 检测子弹与敌方坦克的碰撞
		for (int j = 0; j < MAX_ENEMIES; j++) {
			if (!enemies[j].alive) continue;
			if (ifreducehp(&enemies[j], &bullets[i])) {
				if (bullets[i].type == TOOL_POWERBULLET) {
					enemies[j].HP -= 3;
					bullets[i].exist = 0;
				}
				else if (bullets[i].type == TOOL_SPEBULLET) {
					enemies[j].HP--;
				}
				else if (bullets[i].type == TOOL_EMPTY) {
					enemies[j].HP--;
					bullets[i].exist = 0;
				}
				if (g_soundEnabled) {
					mciSendString(L"play hit_tank from 0", NULL, 0, NULL);
				}
				if (enemies[j].HP <= 0) {
					enemies[j].alive = 0;
					enemyCount--;
				}
				break; // 子弹已失效，跳出内层循环
			}
		}
	}

	// 4. 清理失效子弹（压缩数组）
	int writeIdx = 0;
	for (int i = 0; i < bulletCount; i++) {
		if (bullets[i].exist) {
			if (writeIdx != i) {
				bullets[writeIdx] = bullets[i];
			}
			writeIdx++;
		}
	}
	bulletCount = writeIdx;
}

/*
	负责人：月缀墨宇
	功能：更新敌人坦克的存活状态
	参数：无
	返回值：空
*/
void updateEnemies()
{
	for (int i = 0; i < MAX_ENEMIES; i++) {
		if (enemies[i].alive == 1) {
			if (enemies[i].HP <= 0) {
				enemies[i].alive = 0; // 血量归零，状态设为死亡
				enemyCount--;
			}
		}
	}
}
