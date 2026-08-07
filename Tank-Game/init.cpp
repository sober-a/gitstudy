#include "init.h"

// ==================== 全局变量 ====================
int map[MAX_LEVEL][ROWS][COLS];                       // 存储地图信息
int enemiesSpawn[MAX_LEVEL][MAX_ENEMIES][2];          // 存储每关敌人生成点
int playerSpawn[MAX_LEVEL][1][2];                     // 存储玩家初始位置
int playerSpawn2[MAX_LEVEL][1][2];					  // 存储玩家2初始位置
Bullet bullets[MAX_BULLETS];                          // 子弹数组
int bulletCount = 0;                                  // 当前子弹数量
Tank enemies[MAX_ENEMIES];                            // 敌方坦克数组
int enemyCount = 0;                                   // 敌人数量计数器
GameState gameState = STATE_MENU;                     // 游戏状态
GameState lastState = STATE_MENU;					  //上一个游戏状态
GameState lastTwoState = STATE_MENU;				  //上上个游戏状态，判断暂停界面点继续游戏回到哪个模式
int currentLevel = 0;                                 // 当前关卡
int clearRow, clearCol;								  //传递被清除的可破坏障碍物的位置
int pauseChoose = 0;								  //暂停界面鼠标的选择，1：继续游戏，2：设置，3：帮助，4：主菜单

Base base;											  //基地
Tank player1, player2;//全局变量
int Player1_SpecialBullet = 0;	//玩家1特殊子弹
int Player2_SpecialBullet = 0;	//玩家2特殊子弹
int flag1 = 0;	//玩家1当前特殊子弹类型	0:穿墙弹	1:强力子弹
int flag2 = 0;	//玩家2当前特殊子弹类型	0:穿墙弹	1:强力子弹
Items items[MAX_LEVEL][MAX_ITEM_POS];	//道具生成
int itemSpawnTimer = 0;		//道具间隔生成变量

// 音效设置
bool g_soundEnabled = true;
int g_soundVolume = 50;
bool g_bgmPlaying = false;

/*
	负责人：咸鱼
	功能：初始化地图数组
	参数：level 关卡编号
	返回值：空
*/
void initMap(int level) {
	// 先把整张地图全部清空为空地0
	for (int y = 0; y < ROWS; y++)
	{
		for (int x = 0; x < COLS; x++)
		{
			map[0][y][x] = 0;
		}
	}
}

/*
	负责人:淡写青春
	功能:
		初始化所有对象
	参数:level 关卡编号
	返回值:空
*/
void initGame(int level) {
	//全局变量初始化
	Player1_SpecialBullet = 0;
	flag1 = TOOL_EMPTY;
	Player2_SpecialBullet = 0;
	flag2 = TOOL_EMPTY;
	bulletCount = 0;
	memset(bullets, 0, sizeof(bullets));
	memset(enemies, 0, sizeof(enemies));

	//初始化玩家生成位置
	player1.x = playerSpawn[level][0][0] * BLOCK_SIZE;
	player1.y = playerSpawn[level][0][1] * BLOCK_SIZE;
	//初始化玩家1坦克数据
	player1.dir = DIR_UP;
	player1.HP = 3;
	player1.Max_HP = 3;
	player1.speed = 5;
	player1.camp = CAMP_PLAYER1;
	player1.alive = 1;
	player1.shootCd = 0;
	player1.shootCTime = 20;
	if (gameState == STATE_DOUBLEPEOPLE) {
		//初始化玩家2位置
		player2.x = playerSpawn2[level][0][0] * BLOCK_SIZE;
		player2.y = playerSpawn2[level][0][1] * BLOCK_SIZE;
		//初始化玩家2数据
		player2.dir = DIR_UP;
		player2.HP = 3;
		player2.Max_HP = 3;
		player2.speed = 5;
		player2.camp = CAMP_PLAYER2;
		player2.alive = 1;
		player2.shootCd = 0;
		player2.shootCTime = 20;
	}
	//初始化敌人数量
	enemyCount = MAX_ENEMIES;
	//初始化敌人坦克数据
	for (int i = 0;i < MAX_ENEMIES;i++) {
		int spawnX = enemiesSpawn[level][i][0] * BLOCK_SIZE;
		int spawnY = enemiesSpawn[level][i][1] * BLOCK_SIZE;
		tank_init(&enemies[i], spawnX, spawnY, (unsigned int)(GetTickCount() + level * 97 + i * 131));
		enemies[i].speed = 2;
		enemies[i].HP = 3;
		enemies[i].Max_HP = 3;
		enemies[i].alive = 1;
		enemies[i].camp = CAMP_ENEMY;
		enemies[i].shootCd = 0;
	}
	//初始化道具生成点
	int itemspos[MAX_LEVEL][4][2] = { {{2,7},{6,14},{24,5},{24,10}},
		{{1,1},{2,14},{24,13},{20,2}},{{1,3},{8,3},{24,13},{24,5}},{{1,1},{1,14},{24,3},{23,14}},
		{{1,1},{1,14},{24,1},{24,14}},{{1,1},{1,14},{24,1},{24,14}} };
	for (int k = 0;k < MAX_LEVEL;k++) {
		for (int i = 0;i < MAX_ITEM_POS;i++) {
			items[k][i].x = itemspos[k][i][0] * BLOCK_SIZE;
			items[k][i].y = itemspos[k][i][1] * BLOCK_SIZE;
			items[k][i].exist = 0;
			items[k][i].type = TOOL_EMPTY;
		}
	}

}


/*
	负责人：晨懿
	功能：初始化一关的所有内容
	参数：level
	返回值：空
*/
void initLevel(int level, const TileData tiles[], int count) {
	// 清空地图
	memset(map[level], EMPTY, sizeof(map[level]));

	// 批量赋值
	for (int i = 0; i < count; i++) {
		if (tiles[i].row >= 0 && tiles[i].row < ROWS &&
			tiles[i].col >= 0 && tiles[i].col < COLS) {
			map[level][tiles[i].row][tiles[i].col] = tiles[i].type;
		}
	}
}

//负责人：柿子
//功能：基地生成  
//参数：坐标
//返回值：空

void baseinit() {
	base.x = 13 * BLOCK_SIZE;
	base.y = 14 * BLOCK_SIZE;
	base.hp = 3;
}

//void baseinit() {
//	int jd_col = (COLS - BASE_GRID_NUM) / 2;
//	int jd_row = (ROWS - BASE_GRID_NUM) / 2;
//	base.x = jd_col * BLOCK_SIZE;
//	base.y = jd_row * BLOCK_SIZE;
//	base.hp = 3;
//}
