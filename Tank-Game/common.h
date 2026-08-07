#ifndef COMMON_H
#define COMMON_H

// ==================== 头文件引入 ====================
#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <mmsystem.h>  // 添加多媒体库
#pragma comment(lib, "winmm.lib")  // 链接多媒体库
//宏定义
#define MAX_LEVEL 6			//关卡数量
#define ROWS 16				//地图高
#define COLS 26				//地图宽
#define MAX_BULLETS 100		//最大子弹数量
#define MAX_ENEMIES 10		//最大敌人数量
#define BLOCK_SIZE 50		//每块区域大小
#define TANK_SIZE 45		//坦克尺寸
#define BULLET_SIZE 25		//子弹尺寸
#define ITEMS_SIZE	50		//道具尺寸
#define BASE_SIZE   100		//基地尺寸
#define BASE_GRID_NUM 2		//基地初始化用到
#define MAX_ITEM_POS 4		//道具生成点
// ==================== 枚举定义 ====================
// 方向枚举
enum Direction {
	DIR_UP = 1,
	DIR_DOWN = 2,
	DIR_LEFT = 3,
	DIR_RIGHT = 4
};
// 阵营枚举
enum Camp {
	CAMP_PLAYER1 = 0,			//玩家1
	CAMP_ENEMY = 1,				//敌人
	CAMP_PLAYER2 = 2			//玩家2
};
enum Wall {
	WALL_KONGDI = 0,//空地
	WALL_TOOL = 1,  //道具生成点
	WALL_JIDI = 2,   //基地
	WALL_OBSTACLE = 3,  //障碍物
	WALL_SPEOBSTACLE = 4,  //可破坏障碍物
};
//道具枚举
enum Tool {
	TOOL_EMPTY = -1,						//无道具
	TOOL_ADDHP = 0,							//回血
	TOOL_POWERBULLET = 1,					//强力子弹
	TOOL_SPEBULLET = 2,						//穿墙弹
};
// 游戏状态枚举
enum GameState {
	STATE_MENU = 1,				//主菜单
	STATE_SELECT_LEVEL1 = 2,	//关卡概览,单人模式 
	STATE_SELECT_LEVEL2 = 3,    //关卡概览,双人模式
	STATE_SELECT_LEVEL3 = 4,    //关卡概览,基地模式
	STATE_PLAYING = 5,			//单人模式
	STATE_PAUSE = 6,            //ESC暂停
	STATE_HELP = 7,				//游戏帮助
	STATE_SETTING = 8,			//游戏设置
	STATE_VICTORY = 9,			//胜利界面
	STATE_DEFEAT = 10,			//失败界面
	STATE_DOUBLEPEOPLE = 11,	//双人模式
	STATE_BASE = 12,			//基地模式
};

enum WallType {
	EMPTY = 0,              // 空地（全部关卡）

	//第1关：草地
	GRASS_WALL = 1,         // 草地不可摧毁墙壁
	GRASS_FOREST = 2,       // 草地可摧毁森林（半透明）

	//第2关：沙漠
	DESERT_PYRAMID = 3,       // 沙漠不可摧毁砖墙（半透明）
	DESERT_BRICK = 4,      // 沙漠可摧毁砖墙

	//第3关：岩浆
	LAVA_STONE = 5,         // 岩浆不可摧毁石砖
	LAVA_BRICK = 6,         // 岩浆可摧毁砖块

	//第4关：荒地
	WASTELAND_GRASS = 7,    // 荒地草墩（不可摧毁）
	WASTELAND_TREE = 8,     // 荒地矮树（可摧毁，半透明）
	WASTELAND_SHRUB = 9,    // 荒地灌木丛（可摧毁，半透明）
	WASTELAND_BOX = 10,     // 荒地箱子（不可摧毁）

	//第5关：雪地
	SNOW_ICE = 11,          // 雪地冰块（不可摧毁）
	SNOW_BRICK = 12,        // 雪地砖块（可摧毁）
	SNOW_SNOWMAN = 13,      // 雪地雪人（不可摧毁，半透明）
	SNOW_TREE = 14,         // 雪地树木（不可摧毁，半透明）

	//第6关：地牢
	DARK_STONE = 15,        // 地牢石砖（不可摧毁）
	DARK_IRON = 16,          // 地牢铁栏（可摧毁，半透明）
	//基地地块
	WALL_BASE = 17
};

// ==================== 结构体定义 ====================

struct Bullet {
	int x, y;			//子弹坐标
	int type;			//子弹类型
	int dir;			//子弹方向
	int speed;			//子弹速度
	int owner;			//子弹归属
	int exist;			//子弹是否失效
};

struct Tank {
	int x, y;			//坦克当前坐标
	int HP;				//血量
	int Max_HP;         //最大血量
	int dir;			//方向
	int speed;			//速度
	int camp;			//阵营（敌我）
	int alive;			//根据血量是否大于0判断是否活着
	int shootCd;		//判断射击是否处于冷却
	unsigned int seed;	//随机数生成的种子，用于区分不同的敌方单位，使敌方坦克不至于完全同步
	int move_timer;		//敌方坦克移动计时器
	int shoot_timer;	//敌方坦克开火计时器
	int moveCTime;		//敌方坦克移动间隔
	int shootCTime;		//子弹射击间隔
};

//用于批量初始化地图性质（如果要加可破坏障碍物就必须得再加一个类型了，原先的数组存不下）
struct TileData {
	int row;
	int col;
	int type;
};
/// 道具生成点
struct Items {
	int x;
	int y;
	int type;	//道具类型
	int exist;	//判断道具是否存在
};
//基地结构体：
struct Base {
	int hp;   //基地血量
	int x;
	int y;
};

extern int map[MAX_LEVEL][ROWS][COLS];
extern int enemiesSpawn[MAX_LEVEL][MAX_ENEMIES][2];
extern int playerSpawn[MAX_LEVEL][1][2];
extern int playerSpawn2[MAX_LEVEL][1][2];
extern Bullet bullets[MAX_BULLETS];
extern int bulletCount;
extern Tank enemies[MAX_ENEMIES];
extern int enemyCount;
extern GameState gameState;
extern GameState lastState;
extern GameState lastTwoState;
extern int currentLevel;
extern int clearRow, clearCol;
extern int pauseChoose;
extern Base base;
extern Tank player1, player2;
extern int Player1_SpecialBullet;
extern int Player2_SpecialBullet;
extern int flag1;
extern int flag2;
extern Items items[MAX_LEVEL][MAX_ITEM_POS];
extern int itemSpawnTimer;
extern bool g_soundEnabled;
extern int g_soundVolume;
extern bool g_bgmPlaying;

extern IMAGE img_bg_level1, img_bg_level2, img_bg_level3, img_bg_level4, img_bg_level5, img_bg_level6;
extern IMAGE tile_grass_wall, tile_grass_forest;
extern IMAGE tile_desert_pyramid, tile_desert_brick;
extern IMAGE tile_lava_stone, tile_lava_brick;
extern IMAGE tile_wasteland_grass, tile_wasteland_tree, tile_wasteland_shrub, tile_wasteland_box;
extern IMAGE tile_snow_ice, tile_snow_brick, tile_snow_snowman, tile_snow_tree;
extern IMAGE tile_dark_stone, tile_dark_iron;
extern IMAGE tank_player1_up, tank_player1_down, tank_player1_left, tank_player1_right;
extern IMAGE tank_player2_up, tank_player2_down, tank_player2_left, tank_player2_right;
extern IMAGE tank_enemy_up, tank_enemy_down, tank_enemy_left, tank_enemy_right;
extern IMAGE img_base;
extern IMAGE pos_pow, pos_spe,item_hp;
extern IMAGE bullet_up, bullet_down, bullet_left, bullet_right;
extern IMAGE powbullet_up, powbullet_down, powbullet_left, powbullet_right;
extern IMAGE spebullet_up, spebullet_down, spebullet_left, spebullet_right;
extern IMAGE ui_mainmenu_bg, ui_mainmeau_choose;
extern IMAGE ui_help;
extern IMAGE ui_pause;
extern IMAGE ui_setting_on, ui_setting_off;
extern IMAGE ui_defeat, ui_victory;
extern IMAGE ui_select_bg;
extern IMAGE btn_level1, btn_level2, btn_level3, btn_level4, btn_level5, btn_level6;
extern IMAGE ui_info_bk1, ui_hp;
extern IMAGE ui_hp_jidi, ui_info_bk2, ui_info_bk3;
extern IMAGE ui_num0, ui_num1, ui_num2, ui_num3, ui_num4;
extern IMAGE ui_num5, ui_num6, ui_num7, ui_num8, ui_num9;

unsigned int rand_int(unsigned int* seed);
void drawAlpha(int picture_x, int picture_y, IMAGE* picture);
void initImage();
void initMap(int level);
void initGame(int level);
void initLevel(int level, const TileData tiles[], int count);
int iswin();
void moveAndFire(struct Tank* tank);
int ifreducehp(struct Tank* tank, struct Bullet* bullet);
int canTankMove(struct Tank* tank, int newX, int newY);
int isbasetank(Base* base, Tank* tank);
int bullet_hit_wall(struct Bullet* bullet);
int bulletCollision(struct Bullet* bullet, int target_x, int target_y);
int FindNearest(struct Bullet* bullet, int& nearest_row, int& nearest_col);
void updateBullets();
void checkCollision(Tank* player);
int isbasebullet(Base base, Bullet bullet);
void tank_init(Tank* tank, int x, int y, unsigned int seed);
void EnemyAI_RandomMove(struct Tank* tank, int past_time);
int EnemyAI_RandomShoot(struct Tank* tank, int past_time);
void tank_ai_update(Tank* tank, int past_time);
void updateEnemies();
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
void ifaddhp(Tank* tank, int newX, int newY);
void ifpowerbullet(Tank* tank, int newX, int newY);
void ifspebullet(Tank* tank, int newX, int newY);
void appearitems();
void baseinit();
void drawBase();
void playBGM();
void stopBGM();
void SetApplicationVolume(int volume);
int GetApplicationVolume();

#endif