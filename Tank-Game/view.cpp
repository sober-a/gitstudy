#include "view.h"
#include "map.h"

void drawAlpha(int picture_x, int picture_y, IMAGE* picture) {
	// 1. 获取源图指针和尺寸
	DWORD* src = GetImageBuffer(picture);
	int picture_width = picture->getwidth();
	int picture_height = picture->getheight();

	// 2. 获取目标绘图窗口的宽高和显存指针
	int graphWidth = getwidth();
	int graphHeight = getheight();
	DWORD* dst = GetImageBuffer();  // 目标窗口指针，只获取一次

	// 3. 逐像素混合
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			// 计算目标像素在窗口中的坐标
			int dstX = ix + picture_x;
			int dstY = iy + picture_y;

			// 边界检查：直接判断坐标是否在屏幕内
			if (dstX >= 0 && dstX < graphWidth && dstY >= 0 && dstY < graphHeight)
			{
				// 源图像素的数组索引
				int srcIndex = ix + iy * picture_width;
				// 目标像素的数组索引
				int dstIndex = dstX + dstY * graphWidth;

				// 分离源图的ARGB
				int sa = (src[srcIndex] >> 24) & 0xFF;
				int sr = (src[srcIndex] >> 16) & 0xFF;
				int sg = (src[srcIndex] >> 8) & 0xFF;
				int sb = src[srcIndex] & 0xFF;

				// 分离目标的RGB
				int dr = (dst[dstIndex] >> 16) & 0xFF;
				int dg = (dst[dstIndex] >> 8) & 0xFF;
				int db = dst[dstIndex] & 0xFF;

				// Alpha混合公式：Cp = αp * FP + (1 - αp) * BP
				int r = (sr * sa + dr * (255 - sa)) / 255;
				int g = (sg * sa + dg * (255 - sa)) / 255;
				int b = (sb * sa + db * (255 - sa)) / 255;

				// 写回目标显存
				dst[dstIndex] = (255 << 24) | (r << 16) | (g << 8) | b;
			}
		}
	}
}

//负责人：柿子
// 绘制基地
void drawBase()
{
	// 绘制外框矩形
	//rectangle(base.x, base.y, base.x + BASE_SIZE, base.y + BASE_SIZE);
	// 图片完整填充矩形内部
	putimage(base.x, base.y, &img_base);
}

// ==================== view 层函数声明 ====================

/*
	负责人：不羡仙
	功能：打印主菜单
	参数：无
	返回值：空
*/
void drawMainMenu() {
	cleardevice();

	ExMessage msg;
	putimage(0, 0, &ui_mainmenu_bg);
	putimage(550, 300, &ui_mainmeau_choose);
	//非阻塞获取消息，没有消息立刻返回
	while (peekmessage(&msg, EX_MOUSE)) {

		if (msg.message == WM_LBUTTONDOWN) {
			if (msg.x > 585 && msg.y > 400 && msg.x < 780 && msg.y < 450) {
				cleardevice();
				//打印游戏选关界面
				lastState = STATE_MENU;
				gameState = STATE_SELECT_LEVEL1;
				break;
			}
			else if (msg.x > 585 && msg.y > 450 && msg.x < 780 && msg.y < 500) {
				cleardevice();
				//打印游戏选关界面
				lastState = STATE_MENU;
				gameState = STATE_SELECT_LEVEL2;
				break;
			}
			else if (msg.x > 585 && msg.y > 500 && msg.x < 780 && msg.y < 550) {
				cleardevice();
				//打印游戏选关界面
				lastState = STATE_MENU;
				gameState = STATE_SELECT_LEVEL3;
				break;
			}
			else if (msg.x > 845 && msg.y > 400 && msg.x < 1000 && msg.y < 450) {
				cleardevice();
				//打印游戏帮助界面
				lastState = STATE_MENU;
				gameState = STATE_HELP;
				break;
			}
			else if (msg.x > 845 && msg.y > 450 && msg.x < 1000 && msg.y < 500) {
				cleardevice();
				//打印游戏设置界面
				lastState = STATE_MENU;
				gameState = STATE_SETTING;
				break;
			}
			else if (msg.x > 845 && msg.y > 500 && msg.x < 1000 && msg.y < 550) {
				//直接退出游戏
				stopBGM();
				closegraph();
			}
		}
	}
}
/*
	负责人：不羡仙
	功能：打印游戏帮助界面
	参数：无
	返回值：空
*/
void drawHelp() {
	putimage(0, 0, &ui_help);
	ExMessage msg;
	// 检测按键消息
	if (peekmessage(&msg, EX_KEY))
	{
		if (msg.message == WM_KEYDOWN && msg.vkcode == VK_ESCAPE)
		{
			//如果上一级是暂停界面
			if (lastState == STATE_PAUSE) {
				render();
				printMessage(&player1);
				lastState = STATE_HELP;
				gameState = STATE_PAUSE;
			}
			// 返回主菜单
			else
			{
				lastState = STATE_HELP;
				gameState = STATE_MENU;
			}
		}
	}
}

/*
	负责人：柿子
	功能：打印单人模式选关1界面
	参数：空
	返回值：空
*/
void drawSelectLevel01() {
	wchar_t levelText[6][20] = {
		L"1-1",
		L"1-2",
		L"1-3",
		L"1-4",
		L"1-5",
		L"1-6"
	};
	RECT btnRect[6] = {
		{193, 110, 686, 266},    // btn1 关卡1
		{817, 110, 1310, 266},    // btn2 关卡2
		{193, 322, 686, 488},    // btn3 关卡3
		{817, 322 ,1310,488},    // btn4 关卡4
		{193, 544,686,700},    // btn5 关卡5
		{817,544,1310,700}     // btn6 关卡6
	};

	cleardevice();
	putimage(0, 0, &ui_mainmenu_bg);
	putimage(0, 0, &ui_select_bg);
	rectangle(193, 110, 686, 266);
	rectangle(817, 110, 1310, 266);
	rectangle(193, 322, 686, 488);
	rectangle(817, 322, 1310, 488);
	rectangle(193, 544, 686, 700);
	rectangle(817, 544, 1310, 700);
	putimage(193, 110, &btn_level1);
	putimage(817, 110, &btn_level2);
	putimage(193, 322, &btn_level3);
	putimage(817, 322, &btn_level4);
	putimage(193, 544, &btn_level5);
	putimage(817, 544, &btn_level6);
	setbkmode(TRANSPARENT);
	settextcolor(WHITE);
	settextstyle(30, 0, L"黑体");
	outtextxy(347, 277, levelText[0]);
	outtextxy(971, 277, levelText[1]);
	outtextxy(347, 500, levelText[2]);
	outtextxy(971, 500, levelText[3]);
	outtextxy(347, 722, levelText[4]);
	outtextxy(971, 722, levelText[5]);
	ExMessage msg;
	while (peekmessage(&msg, EX_KEY | EX_MOUSE)) {

		if (msg.message == WM_KEYDOWN && msg.vkcode == VK_ESCAPE) {
			lastState = STATE_SELECT_LEVEL1;
			gameState = STATE_MENU;
			return;                     // 直接返回，主循环下次会调用 drawMainMenu
		}
		if (msg.message == WM_LBUTTONDOWN) {
			int mx = msg.x;
			int my = msg.y;
			for (int i = 0; i < 6; i++) {
				if (mx >= btnRect[i].left && mx <= btnRect[i].right && my >= btnRect[i].top && my <= btnRect[i].bottom) {
					currentLevel = i;
					initMapData01();

					initGame(currentLevel);
					lastState = STATE_SELECT_LEVEL1;
					gameState = STATE_PLAYING;
				}
			}
		}

	}

}

/*
	负责人：柿子
	功能：打印选关2界面
	参数：空
	返回值：空
*/
void drawSelectLevel02() {
	wchar_t levelText[6][20] = {
		L"1-1",
		L"1-2",
		L"1-3",
		L"1-4",
		L"1-5",
		L"1-6"
	};
	RECT btnRect[6] = {
		{193, 110, 686, 266},    // btn1 关卡1
		{817, 110, 1310, 266},    // btn2 关卡2
		{193, 322, 686, 488},    // btn3 关卡3
		{817, 322 ,1310,488},    // btn4 关卡4
		{193, 544,686,700},    // btn5 关卡5
		{817,544,1310,700}     // btn6 关卡6
	};

	cleardevice();
	putimage(0, 0, &ui_mainmenu_bg);
	putimage(0, 0, &ui_select_bg);
	rectangle(193, 110, 686, 266);
	rectangle(817, 110, 1310, 266);
	rectangle(193, 322, 686, 488);
	rectangle(817, 322, 1310, 488);
	rectangle(193, 544, 686, 700);
	rectangle(817, 544, 1310, 700);
	putimage(193, 110, &btn_level1);
	putimage(817, 110, &btn_level2);
	putimage(193, 322, &btn_level3);
	putimage(817, 322, &btn_level4);
	putimage(193, 544, &btn_level5);
	putimage(817, 544, &btn_level6);
	setbkmode(TRANSPARENT);
	settextcolor(WHITE);
	settextstyle(30, 0, L"黑体");
	outtextxy(347, 277, levelText[0]);
	outtextxy(971, 277, levelText[1]);
	outtextxy(347, 500, levelText[2]);
	outtextxy(971, 500, levelText[3]);
	outtextxy(347, 722, levelText[4]);
	outtextxy(971, 722, levelText[5]);

	//在选关2界面初始化玩家2位置
	playerSpawn2[0][0][0] = 9;
	playerSpawn2[0][0][1] = 6;
	playerSpawn2[1][0][0] = 2;
	playerSpawn2[1][0][1] = 15;
	playerSpawn2[2][0][0] = 12;
	playerSpawn2[2][0][1] = 6;
	playerSpawn2[3][0][0] = 7;
	playerSpawn2[3][0][1] = 15;
	playerSpawn2[4][0][0] = 4;
	playerSpawn2[4][0][1] = 15;
	playerSpawn2[5][0][0] = 7;
	playerSpawn2[5][0][1] = 15;

	ExMessage msg;
	while (peekmessage(&msg, EX_KEY | EX_MOUSE)) {

		if (msg.message == WM_KEYDOWN && msg.vkcode == VK_ESCAPE) {
			lastState = STATE_SELECT_LEVEL2;
			gameState = STATE_MENU;
			return;                     // 直接返回，主循环下次会调用 drawMainMenu
		}
		if (msg.message == WM_LBUTTONDOWN) {
			int mx = msg.x;
			int my = msg.y;
			for (int i = 0; i < 6; i++) {
				if (mx >= btnRect[i].left && mx <= btnRect[i].right && my >= btnRect[i].top && my <= btnRect[i].bottom) {
					currentLevel = i;
					initMapData02();

					initGame(currentLevel);
					lastState = STATE_SELECT_LEVEL2;
					gameState = STATE_DOUBLEPEOPLE;
				}
			}
		}

	}

}

/*
	负责人：柿子
	功能：打印基地模式选关3界面
	参数：空
	返回值：空
*/
void drawSelectLevel03() {
	wchar_t levelText[6][20] = {
		L"1-1",
		L"1-2",
		L"1-3",
		L"1-4",
		L"1-5",
		L"1-6"
	};
	RECT btnRect[6] = {
		{193, 110, 686, 266},    // btn1 关卡1
		{817, 110, 1310, 266},    // btn2 关卡2
		{193, 322, 686, 488},    // btn3 关卡3
		{817, 322 ,1310,488},    // btn4 关卡4
		{193, 544,686,700},    // btn5 关卡5
		{817,544,1310,700}     // btn6 关卡6
	};

	cleardevice();
	putimage(0, 0, &ui_mainmenu_bg);
	putimage(0, 0, &ui_select_bg);
	rectangle(193, 110, 686, 266);
	rectangle(817, 110, 1310, 266);
	rectangle(193, 322, 686, 488);
	rectangle(817, 322, 1310, 488);
	rectangle(193, 544, 686, 700);
	rectangle(817, 544, 1310, 700);
	putimage(193, 110, &btn_level1);
	putimage(817, 110, &btn_level2);
	putimage(193, 322, &btn_level3);
	putimage(817, 322, &btn_level4);
	putimage(193, 544, &btn_level5);
	putimage(817, 544, &btn_level6);
	setbkmode(TRANSPARENT);
	settextcolor(WHITE);
	settextstyle(30, 0, L"黑体");
	outtextxy(347, 277, levelText[0]);
	outtextxy(971, 277, levelText[1]);
	outtextxy(347, 500, levelText[2]);
	outtextxy(971, 500, levelText[3]);
	outtextxy(347, 722, levelText[4]);
	outtextxy(971, 722, levelText[5]);
	ExMessage msg;
	while (peekmessage(&msg, EX_KEY | EX_MOUSE)) {

		if (msg.message == WM_KEYDOWN && msg.vkcode == VK_ESCAPE) {
			lastState = STATE_SELECT_LEVEL3;
			gameState = STATE_MENU;
			return;                     // 直接返回，主循环下次会调用 drawMainMenu
		}
		if (msg.message == WM_LBUTTONDOWN) {
			int mx = msg.x;
			int my = msg.y;
			for (int i = 0; i < 6; i++) {
				if (mx >= btnRect[i].left && mx <= btnRect[i].right && my >= btnRect[i].top && my <= btnRect[i].bottom) {
					currentLevel = i;
					initMapData03();


					//基地初始化
					baseinit();
					initGame(currentLevel);
					lastState = STATE_SELECT_LEVEL3;
					gameState = STATE_BASE;
				}
			}
		}

	}

}

/*
	负责人：晨懿
	功能：打印地图
	参数：level 关卡编号
	返回值：空
*/
// ==================== 地图绘制函数（switch-case版本） ====================
void drawMap(int level) {
	switch (level) {
	case 0: putimage(0, 0, &img_bg_level1); break;
	case 1: putimage(0, 0, &img_bg_level2); break;
	case 2: putimage(0, 0, &img_bg_level3); break;
	case 3: putimage(0, 0, &img_bg_level4); break;
	case 4: putimage(0, 0, &img_bg_level5); break;
	case 5: putimage(0, 0, &img_bg_level6); break;
	}

	for (int row = 0; row < ROWS; row++) {
		for (int col = 0; col < COLS; col++) {
			int type = map[level][row][col];
			if (type == EMPTY) continue;
			int x = col * BLOCK_SIZE;
			int y = row * BLOCK_SIZE;
			switch (type) {
			case GRASS_WALL:       putimage(x, y, &tile_grass_wall); break;
			case GRASS_FOREST:     drawAlpha(x, y, &tile_grass_forest); break;
			case DESERT_PYRAMID:   drawAlpha(x, y, &tile_desert_pyramid); break;
			case DESERT_BRICK:     putimage(x, y, &tile_desert_brick); break;
			case LAVA_STONE:       putimage(x, y, &tile_lava_stone); break;
			case LAVA_BRICK:       drawAlpha(x, y, &tile_lava_brick); break;
			case WASTELAND_GRASS:  putimage(x, y, &tile_wasteland_grass); break;
			case WASTELAND_TREE:   drawAlpha(x, y, &tile_wasteland_tree); break;
			case WASTELAND_SHRUB:  drawAlpha(x, y, &tile_wasteland_shrub); break;
			case WASTELAND_BOX:    putimage(x, y, &tile_wasteland_box); break;
			case SNOW_ICE:         putimage(x, y, &tile_snow_ice); break;
			case SNOW_BRICK:       putimage(x, y, &tile_snow_brick); break;
			case SNOW_SNOWMAN:     drawAlpha(x, y, &tile_snow_snowman); break;
			case SNOW_TREE:        drawAlpha(x, y, &tile_snow_tree); break;
			case DARK_STONE:       putimage(x, y, &tile_dark_stone); break;
			case DARK_IRON:        drawAlpha(x, y, &tile_dark_iron); break;
			case WALL_BASE:			putimage(base.x, base.y, &img_base);break;
			}
		}
	}
}
/*
	负责人：苏念玖
	功能：打印单人模式信息栏
	参数：Tank* player
	返回值：空
*/
void printMessage(Tank* player1) {

	//打印背景板
	putimage(1300, 0, &ui_info_bk1);
	//打印HP，合适坐标(1350,180),(1387,180),(1425,180)
	if (player1->HP == 3) {
		putimage(1350, 180, &ui_hp);
		putimage(1387, 180, &ui_hp);
		putimage(1425, 180, &ui_hp);
	}
	else if (player1->HP == 2) {
		putimage(1350, 180, &ui_hp);
		putimage(1387, 180, &ui_hp);
	}
	else if (player1->HP == 1) {
		putimage(1350, 180, &ui_hp);
	}
	//打印关卡信息,合适坐标(1390,400)
	switch (currentLevel) {
	case 0:drawAlpha(1390, 400, &ui_num1);break;
	case 1:drawAlpha(1390, 400, &ui_num2);break;
	case 2:drawAlpha(1390, 400, &ui_num3);break;
	case 3:drawAlpha(1390, 400, &ui_num4);break;
	case 4:drawAlpha(1390, 400, &ui_num5);break;
	case 5:drawAlpha(1390, 400, &ui_num6);break;
	default:break;
	}
	//打印剩余敌人数量,合适坐标(1390,590),数字10的坐标（1380，589）和（1400，590）
	switch (enemyCount) {
	case 1:drawAlpha(1390, 590, &ui_num1);break;
	case 2:drawAlpha(1390, 590, &ui_num2);break;
	case 3:drawAlpha(1390, 590, &ui_num3);break;
	case 4:drawAlpha(1390, 590, &ui_num4);break;
	case 5:drawAlpha(1390, 590, &ui_num5);break;
	case 6:drawAlpha(1390, 590, &ui_num6);break;
	case 7:drawAlpha(1390, 590, &ui_num7);break;
	case 8:drawAlpha(1390, 590, &ui_num8);break;
	case 9:drawAlpha(1390, 590, &ui_num9);break;
	case 10:drawAlpha(1380, 589, &ui_num1);drawAlpha(1400, 590, &ui_num0);break;
	default:break;
	}
}

//打印双人模式信息栏，负责人：苏念玖
void printMessage(Tank* player1, Tank* player2) {

	//打印背景板
	putimage(1300, 0, &ui_info_bk2);
	//打印玩家1的HP，合适坐标(1355,160),(1395,160),(1435,160)
	if (player1->HP == 3) {
		putimage(1355, 160, &ui_hp);
		putimage(1395, 160, &ui_hp);
		putimage(1435, 160, &ui_hp);
	}
	else if (player1->HP == 2) {
		putimage(1355, 160, &ui_hp);
		putimage(1395, 160, &ui_hp);
	}
	else if (player1->HP == 1) {
		putimage(1355, 160, &ui_hp);
	}
	//打印玩家2的HP，合适坐标(1355,230),(1395,230),(1435,230)
	if (player2->HP == 3) {
		putimage(1355, 355, &ui_hp);
		putimage(1395, 355, &ui_hp);
		putimage(1435, 355, &ui_hp);
	}
	else if (player2->HP == 2) {
		putimage(1355, 355, &ui_hp);
		putimage(1395, 355, &ui_hp);
	}
	else if (player2->HP == 1) {
		putimage(1355, 355, &ui_hp);
	}
	//打印关卡信息,合适坐标(1390,543)
	switch (currentLevel) {
	case 0:drawAlpha(1390, 543, &ui_num1);break;
	case 1:drawAlpha(1390, 543, &ui_num2);break;
	case 2:drawAlpha(1390, 543, &ui_num3);break;
	case 3:drawAlpha(1390, 543, &ui_num4);break;
	case 4:drawAlpha(1390, 543, &ui_num5);break;
	case 5:drawAlpha(1390, 543, &ui_num6);break;
	default:break;
	}
	//打印剩余敌人数量,合适坐标(1390,720),数字10的坐标（1380，719）和（1400，720）
	switch (enemyCount) {
	case 1:drawAlpha(1390, 720, &ui_num1);break;
	case 2:drawAlpha(1390, 720, &ui_num2);break;
	case 3:drawAlpha(1390, 720, &ui_num3);break;
	case 4:drawAlpha(1390, 720, &ui_num4);break;
	case 5:drawAlpha(1390, 720, &ui_num5);break;
	case 6:drawAlpha(1390, 720, &ui_num6);break;
	case 7:drawAlpha(1390, 720, &ui_num7);break;
	case 8:drawAlpha(1390, 720, &ui_num8);break;
	case 9:drawAlpha(1390, 720, &ui_num9);break;
	case 10:drawAlpha(1380, 719, &ui_num1);drawAlpha(1400, 720, &ui_num0);break;
	default:break;
	}
}
//打印基地模式信息栏，负责人：苏念玖
void printMessage(Tank* player1, Base* base) {
	//打印背景板
	putimage(1300, 0, &ui_info_bk3);
	//打印玩家的HP，合适坐标(1355,160),(1395,160),(1435,160)
	if (player1->HP == 3) {
		putimage(1355, 160, &ui_hp);
		putimage(1388, 160, &ui_hp);
		putimage(1421, 160, &ui_hp);
	}
	else if (player1->HP == 2) {
		putimage(1355, 160, &ui_hp);
		putimage(1388, 160, &ui_hp);
	}
	else if (player1->HP == 1) {
		putimage(1355, 160, &ui_hp);
	}
	//打印基地的HP，合适坐标(1355,230),(1395,230),(1435,230)
	if (base->hp == 3) {
		putimage(1355, 365, &ui_hp_jidi);
		putimage(1388, 365, &ui_hp_jidi);
		putimage(1421, 365, &ui_hp_jidi);
	}
	else if (base->hp == 2) {
		putimage(1355, 365, &ui_hp_jidi);
		putimage(1388, 365, &ui_hp_jidi);
	}
	else if (base->hp == 1) {
		putimage(1355, 365, &ui_hp_jidi);
	}
	//打印关卡信息,合适坐标(1390,543)
	switch (currentLevel) {
	case 0:drawAlpha(1390, 543, &ui_num1);break;
	case 1:drawAlpha(1390, 543, &ui_num2);break;
	case 2:drawAlpha(1390, 543, &ui_num3);break;
	case 3:drawAlpha(1390, 543, &ui_num4);break;
	case 4:drawAlpha(1390, 543, &ui_num5);break;
	case 5:drawAlpha(1390, 543, &ui_num6);break;
	default:break;
	}
	//打印剩余敌人数量,合适坐标(1390,720),数字10的坐标（1380，719）和（1400，720）
	switch (enemyCount) {
	case 1:drawAlpha(1390, 720, &ui_num1);break;
	case 2:drawAlpha(1390, 720, &ui_num2);break;
	case 3:drawAlpha(1390, 720, &ui_num3);break;
	case 4:drawAlpha(1390, 720, &ui_num4);break;
	case 5:drawAlpha(1390, 720, &ui_num5);break;
	case 6:drawAlpha(1390, 720, &ui_num6);break;
	case 7:drawAlpha(1390, 720, &ui_num7);break;
	case 8:drawAlpha(1390, 720, &ui_num8);break;
	case 9:drawAlpha(1390, 720, &ui_num9);break;
	case 10:drawAlpha(1380, 719, &ui_num1);drawAlpha(1400, 720, &ui_num0);break;
	default:break;
	}
}
/*
	负责人：月缀墨宇
	功能：打印设置界面
	参数：无
	返回值：空
*/

void drawSetting()
{
	const int imageWidth = 1067;
	const int imageHeight = 800;
	const int imageLeft = (1500 - imageWidth) / 2;

	//显示当前音效状态图片
	putimage(imageLeft, 0, g_soundEnabled ? &ui_setting_on : &ui_setting_off);
	BeginBatchDraw();
	//文字背景透明
	setbkmode(TRANSPARENT);
	settextstyle(38, 0, _T("Microsoft YaHei"));
	settextcolor(WHITE);
	TCHAR volumeText[16];
	_stprintf_s(volumeText, _T("%d"), g_soundVolume);
	outtextxy(imageLeft + 670 - textwidth(volumeText) / 2, 495, volumeText);

	//获取鼠标左键点击位置
	MOUSEMSG mouseMsg = GetMouseMsg();
	if (mouseMsg.uMsg == WM_LBUTTONDOWN)
	{
		//点击音效开关按钮
		if (mouseMsg.x >= imageLeft + 685 && mouseMsg.x <= imageLeft + 803 &&
			mouseMsg.y >= 278 && mouseMsg.y <= 325)
		{
			g_soundEnabled = !g_soundEnabled;
			if (!g_soundEnabled) {
				mciSendString(L"stop sfx", NULL, 0, NULL);
				mciSendString(L"stop hit_tank", NULL, 0, NULL);
				mciSendString(L"stop hit_wall", NULL, 0, NULL);
			}
			putimage(imageLeft, 0, g_soundEnabled ? &ui_setting_on : &ui_setting_off);
			_stprintf_s(volumeText, _T("%d"), g_soundVolume);
			outtextxy(imageLeft + 670 - textwidth(volumeText) / 2, 495, volumeText);
		}
		//点击音量增加按钮
		else if (mouseMsg.x >= imageLeft + 742 && mouseMsg.x <= imageLeft + 790 &&
			mouseMsg.y >= 488 && mouseMsg.y <= 535)
		{
			if (g_soundVolume < 100)
			{
				++g_soundVolume;
				SetApplicationVolume(g_soundVolume);
			}
			putimage(imageLeft, 0, g_soundEnabled ? &ui_setting_on : &ui_setting_off);
			_stprintf_s(volumeText, _T("%d"), g_soundVolume);
			outtextxy(imageLeft + 670 - textwidth(volumeText) / 2, 495, volumeText);
			//按住鼠标左键持续增加音量
			while ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) && g_soundVolume < 100)
			{
				Sleep(100);
				if (!(GetAsyncKeyState(VK_LBUTTON) & 0x8000))
				{
					break;
				}
				++g_soundVolume;
				SetApplicationVolume(g_soundVolume);
				putimage(imageLeft, 0, g_soundEnabled ? &ui_setting_on : &ui_setting_off);
				_stprintf_s(volumeText, _T("%d"), g_soundVolume);
				outtextxy(imageLeft + 670 - textwidth(volumeText) / 2, 495, volumeText);
			}
		}

		//点击音量减少按钮
		else if (mouseMsg.x >= imageLeft + 548 && mouseMsg.x <= imageLeft + 594 &&
			mouseMsg.y >= 488 && mouseMsg.y <= 535)
		{
			if (g_soundVolume > 0)
			{
				--g_soundVolume;
				SetApplicationVolume(g_soundVolume);
			}
			putimage(imageLeft, 0, g_soundEnabled ? &ui_setting_on : &ui_setting_off);
			_stprintf_s(volumeText, _T("%d"), g_soundVolume);
			outtextxy(imageLeft + 670 - textwidth(volumeText) / 2, 495, volumeText);
			//按住鼠标左键持续减少音量
			while ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) && g_soundVolume > 0)
			{
				Sleep(100);
				if (!(GetAsyncKeyState(VK_LBUTTON) & 0x8000))
				{
					break;
				}
				--g_soundVolume;
				SetApplicationVolume(g_soundVolume);
				putimage(imageLeft, 0, g_soundEnabled ? &ui_setting_on : &ui_setting_off);
				_stprintf_s(volumeText, _T("%d"), g_soundVolume);
				outtextxy(imageLeft + 670 - textwidth(volumeText) / 2, 495, volumeText);
			}
		}
		//点击返回按钮，清空设置界面
		else if (mouseMsg.x >= imageLeft + 387 && mouseMsg.x <= imageLeft + 674 &&
			mouseMsg.y >= 663 && mouseMsg.y <= 748)
		{
			cleardevice();
			if (lastState == STATE_MENU)
			{
				lastState = STATE_SETTING;
				gameState = STATE_MENU;
			}
			else if (lastState == STATE_PAUSE) {
				//渲染一帧游戏画面
				if (lastTwoState == STATE_PLAYING)
				{
					render();
					printMessage(&player1);
				}
				else if (lastTwoState == STATE_DOUBLEPEOPLE)
				{
					render();
					printMessage(&player1);
				}
				else if (lastTwoState == STATE_BASE)
				{
					render();
					printMessage(&player1);
				}
				lastState = STATE_SETTING;
				gameState = STATE_PAUSE;
			}
		}

	}
}
/*
	负责人：月缀墨宇
	功能：打印暂停界面
	参数：无
	返回值：1:继续游戏，2：设置，3：帮助，4：主菜单

*/
int drawPause() {
	const int imageWidth = 888;
	const int imageLeft = (1500 - imageWidth) / 2;
	// 用 peekmessage 非阻塞等待鼠标点击
	ExMessage msg;

	while (peekmessage(&msg, EX_MOUSE) && msg.message == WM_LBUTTONDOWN) {

		int x = msg.x;
		int y = msg.y;

		// 继续游戏
		if (x >= imageLeft + 205 && x <= imageLeft + 670 &&
			y >= 234 && y <= 326) {
			cleardevice();
			return 1;
		}
		// 设置界面
		if (x >= imageLeft + 205 && x <= imageLeft + 670 &&
			y >= 360 && y <= 452) {
			FlushBatchDraw();
			cleardevice();
			return 2;
		}
		// 帮助界面
		if (x >= imageLeft + 205 && x <= imageLeft + 670 &&
			y >= 486 && y <= 578) {
			//gameState = STATE_HELP;
			FlushBatchDraw();
			cleardevice();
			return 3;
		}
		// 返回主菜单
		if (x >= imageLeft + 205 && x <= imageLeft + 670 &&
			y >= 609 && y <= 706) {
			gameState = STATE_MENU;
			return 4;
		}
		Sleep(10);
	}
	return 0;
}
/*
	负责人：淡写青春
	功能：绘制单个坦克
	参数：struct Tank*
	返回值：空
*/
void drawTank(struct Tank* tank) {
	if (tank->alive == 0) return;

	IMAGE* img = NULL;
	if (tank->camp == CAMP_PLAYER1) {
		switch (tank->dir) {
		case DIR_UP:    img = &tank_player1_up;    break;
		case DIR_DOWN:  img = &tank_player1_down;  break;
		case DIR_LEFT:  img = &tank_player1_left;  break;
		case DIR_RIGHT: img = &tank_player1_right; break;
		}
	}
	else if (tank->camp == CAMP_ENEMY) {
		switch (tank->dir) {
		case DIR_UP:    img = &tank_enemy_up;    break;
		case DIR_DOWN:  img = &tank_enemy_down;  break;
		case DIR_LEFT:  img = &tank_enemy_left;  break;
		case DIR_RIGHT: img = &tank_enemy_right; break;
		}
	}
	else if (tank->camp == CAMP_PLAYER2) {
		switch (tank->dir) {
		case DIR_UP:    img = &tank_player2_up;    break;
		case DIR_DOWN:  img = &tank_player2_down;  break;
		case DIR_LEFT:  img = &tank_player2_left;  break;
		case DIR_RIGHT: img = &tank_player2_right; break;
		}
	}
	if (img) drawAlpha(tank->x, tank->y, img);
}

/*
	负责人：淡写青春
	功能：绘制单个子弹
	参数：struct Bullet*
	返回值：空
*/
void drawBullet(struct Bullet* bullet) {
	if (bullet->exist == 0) return;

	IMAGE* img = NULL;
	switch (bullet->type) {
	case TOOL_EMPTY:
		switch (bullet->dir) {
		case DIR_UP:    img = &bullet_up;    break;
		case DIR_DOWN:  img = &bullet_down;  break;
		case DIR_LEFT:  img = &bullet_left;  break;
		case DIR_RIGHT: img = &bullet_right; break;
		}
		break;
	case TOOL_POWERBULLET: {
		switch (bullet->dir) {
		case DIR_UP:    img = &powbullet_up;	break;
		case DIR_DOWN:  img = &powbullet_down;  break;
		case DIR_LEFT:  img = &powbullet_left;  break;
		case DIR_RIGHT: img = &powbullet_right; break;
		}
		if (bullet->owner == CAMP_PLAYER1) {
			Player1_SpecialBullet = 0;
			flag1 = TOOL_EMPTY;
		}
		else if (bullet->owner == CAMP_PLAYER2) {
			Player2_SpecialBullet = 0;
			flag2 = TOOL_EMPTY;
		}
		break;
	}
	case TOOL_SPEBULLET:
		switch (bullet->dir) {
		case DIR_UP:    img = &spebullet_up;    break;
		case DIR_DOWN:  img = &spebullet_down;  break;
		case DIR_LEFT:  img = &spebullet_left;  break;
		case DIR_RIGHT: img = &spebullet_right; break;
		}
		if (bullet->owner == CAMP_PLAYER1) {
			Player1_SpecialBullet = 0;
			flag1 = TOOL_EMPTY;
		}
		else if (bullet->owner == CAMP_PLAYER2) {
			Player2_SpecialBullet = 0;
			flag2 = TOOL_EMPTY;
		}
		break;
	}
	if (img) drawAlpha(bullet->x, bullet->y, img);
}
/*
	负责人：淡写青春
	功能：绘制道具
	参数：struct Items* item
	返回值：空
*/
void drawItems(struct Items* item) {
	if (!item->exist) return;
	switch (item->type) {
	case TOOL_EMPTY:
		break;
	case TOOL_ADDHP:
		drawAlpha(item->x, item->y, &item_hp);
		break;
	case TOOL_POWERBULLET:
		drawAlpha(item->x, item->y, &pos_pow);
		break;
	case TOOL_SPEBULLET:
		drawAlpha(item->x, item->y, &pos_spe);
		break;
	}
}

/*
	负责人：淡写青春
	功能：绘制所有游戏对象
	参数：无
	返回值：空
*/
void render() {
	drawMap(currentLevel);
	drawTank(&player1);
	if (player2.alive && gameState == STATE_DOUBLEPEOPLE) drawTank(&player2);
	//绘制道具
	for (int i = 0;i < MAX_ITEM_POS;i++) {
		if (items[currentLevel][i].exist) drawItems(&items[currentLevel][i]);
	}
	//绘制子弹
	for (int i = 0; i < MAX_ENEMIES; i++) {
		if (enemies[i].alive) drawTank(&enemies[i]);
	}
	//绘制敌人
	for (int i = 0; i < bulletCount; i++) {
		if (bullets[i].exist) drawBullet(&bullets[i]);
	}
	
}

/*
	负责人：柿子
	功能：打印胜利或失败界面
	参数：type 0=失败, 1=胜利
	返回值：空
*/
void drawResult(int type) {
	cleardevice();
	if (lastTwoState == STATE_PLAYING) {
		render();
		printMessage(&player1);
	}
	else if (lastTwoState == STATE_DOUBLEPEOPLE) {
		render();
		printMessage(&player1, &player2);
	}
	else if (lastTwoState == STATE_BASE) {
		render();
		printMessage(&player1, &base);
	}
	if (type == 0) {
		putimage(350, 100, &ui_defeat);   // 用全局加载好的图
	}
	else {
		putimage(350, 100, &ui_victory);
	}
	FlushBatchDraw();
}
/*
	负责人：柿子
	功能：游戏失败后的选择
	参数：无
	返回值：0=重新开始, 1=返回主菜单
*/
int Defeat() {
	drawResult(0);
	ExMessage msg;
	while (1) {
		if (peekmessage(&msg, EX_MOUSE))
		{
			if (msg.message == WM_LBUTTONDOWN) {
				int mx = msg.x;
				int my = msg.y;
				if ((mx >= 593 && mx <= 860) && (my >= 438 && my < 492)) {
					cleardevice();
					return 0;
				}
				if ((mx >= 593 && mx <= 860) && (my >= 519 && my < 566)) {
					cleardevice();
					return 1;
				}
			}
		}
		Sleep(10);
	}
}

/*
	负责人：柿子
	功能：游戏胜利后的选择
	参数：无
	返回值: 1=回到关卡概览, 2=返回主菜单
*/
int Victory() {
	drawResult(1);
	ExMessage msg;
	while (1) {
		if (peekmessage(&msg, EX_MOUSE))
		{
			if (msg.message == WM_LBUTTONDOWN) {
				int mx = msg.x;
				int my = msg.y;
				if ((mx >= 487 && mx <= 487 + 275) && (my >= 455 && my < 455 + 62)) {
					cleardevice();
					return 1;
				}
				if ((mx >= 487 && mx <= 487 + 275) && (my >= 516 && my < 516 + 62)) {
					cleardevice();
					return 2;
				}
			}
		}
		Sleep(10);
	}
}

