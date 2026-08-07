#include "common.h"
#include "runGame.h"

// ==================== View ====================
void runGame() {
	//加载图片资源
	//初始化图形窗口


	//初始化随机种子
	//设置游戏初始状态
	//主游戏循环
	while (true) {
		cleardevice();
		switch (gameState) {
		case STATE_MENU:
			drawMainMenu();
			break;

		case STATE_SELECT_LEVEL1:
			lastState = STATE_SELECT_LEVEL1;
			drawSelectLevel01();
			initGame(currentLevel);
			break;

		case STATE_SELECT_LEVEL2:
			lastState = STATE_SELECT_LEVEL2;
			drawSelectLevel02();
			initGame(currentLevel);
			break;

		case STATE_SELECT_LEVEL3:
			lastState = STATE_SELECT_LEVEL3;
			drawSelectLevel03();
			initGame(currentLevel);
			break;


		case STATE_PLAYING: {

			// ========== 游戏循环 ==========
			while (gameState == STATE_PLAYING) {
				//记录状态
				lastTwoState = STATE_PLAYING;
				//更新时间
				itemSpawnTimer += 16;
				// 处理输入
				moveAndFire(&player1);
				// 更新敌人AI
				for (int i = 0; i < MAX_ENEMIES; i++) {
					if (enemies[i].alive) {
						tank_ai_update(&enemies[i], 16);
					}
				}

				// 更新子弹
				updateBullets();

				// 碰撞检测
				checkCollision(&player1);

				// 更新敌人状态
				updateEnemies();
				//更新信息栏
				printMessage(&player1);
				//生成道具
				appearitems();

				// 渲染
				render();

				// 检查胜利/失败
				int result = iswin();
				if (result == 1) {
					lastState = STATE_PLAYING;
					gameState = STATE_VICTORY;
					break;  // 退出帧循环
				}
				else if (result == -1) {
					lastState = STATE_PLAYING;
					gameState = STATE_DEFEAT;
					break;  // 退出帧循环
				}

				// 检测暂停（ESC键）
				if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
					lastState = STATE_PLAYING;
					gameState = STATE_PAUSE;
					Sleep(100);  // 防止连续触发
					break;  // 退出帧循环
				}
				FlushBatchDraw();
				Sleep(16);
			}
			break;  // 退出 switch
		}
		case STATE_DOUBLEPEOPLE: {
			// ========== 双人模式游戏循环 ==========
			while (gameState == STATE_DOUBLEPEOPLE) {
				//记录状态
				lastTwoState = STATE_DOUBLEPEOPLE;
				//更新时间
				itemSpawnTimer += 16;
				// 处理输入
				moveAndFire(&player1);
				moveAndFire(&player2);
				// 更新敌人AI
				for (int i = 0; i < MAX_ENEMIES; i++) {
					if (enemies[i].alive) {
						tank_ai_update(&enemies[i], 16);
					}
				}

				// 更新子弹
				updateBullets();

				// 碰撞检测
				checkCollision(&player1);
				checkCollision(&player2);

				// 更新敌人状态
				updateEnemies();
				//更新信息栏
				printMessage(&player1, &player2);
				//生成道具
				appearitems();

				// 渲染
				render();

				// 检查胜利/失败
				int result = iswin();
				if (result == 1) {
					lastState = STATE_DOUBLEPEOPLE;
					gameState = STATE_VICTORY;
					break;  // 退出帧循环
				}
				else if (result == -1) {
					lastState = STATE_DOUBLEPEOPLE;
					gameState = STATE_DEFEAT;
					break;  // 退出帧循环
				}

				// 检测暂停（ESC键）
				if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
					lastState = STATE_DOUBLEPEOPLE;
					gameState = STATE_PAUSE;
					Sleep(100);  // 防止连续触发
					break;  // 退出帧循环
				}
				FlushBatchDraw();
				Sleep(16);
			}
			break;  // 退出 switch
		}

		case STATE_BASE: {

			// ========== 基地模式游戏循环 ==========
			while (gameState == STATE_BASE) {
				//记录状态
				lastTwoState = STATE_BASE;
				//更新时间
				itemSpawnTimer += 16;
				// 处理输入
				moveAndFire(&player1);
				// 更新敌人AI
				for (int i = 0; i < MAX_ENEMIES; i++) {
					if (enemies[i].alive) {
						tank_ai_update(&enemies[i], 16);
					}
				}

				// 更新子弹
				updateBullets();

				// 碰撞检测
				checkCollision(&player1);

				// 更新敌人状态
				updateEnemies();

				//打印基地
				drawBase();
				//更新信息栏
				printMessage(&player1, &base);
				//生成道具
				appearitems();
				// 渲染
				render();

				// 检查胜利/失败
				int result = iswin();
				if (result == 1) {
					lastState = STATE_BASE;
					gameState = STATE_VICTORY;
					break;  // 退出帧循环
				}
				else if (result == -1) {
					lastState = STATE_BASE;
					gameState = STATE_DEFEAT;
					break;  // 退出帧循环
				}

				// 检测暂停（ESC键）
				if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
					lastState = STATE_BASE;
					gameState = STATE_PAUSE;
					Sleep(100);  // 防止连续触发
					break;  // 退出帧循环
				}
				FlushBatchDraw();
				Sleep(16);
			}
			break;  // 退出 switch
		}

		case STATE_PAUSE:
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
			// 先画暂停界面
			putimage(306, 0, &ui_pause);
			FlushBatchDraw();
			pauseChoose = drawPause();
			if (pauseChoose == 1) {
				if (lastTwoState == STATE_PLAYING)
				{
					gameState = STATE_PLAYING;
				}
				else if (lastTwoState == STATE_DOUBLEPEOPLE) {
					gameState = STATE_DOUBLEPEOPLE;
				}
				else if (lastTwoState == STATE_BASE) {
					gameState = STATE_BASE;
				}

			}
			else if (pauseChoose == 2) {
				cleardevice();
				lastState = STATE_PAUSE;
				gameState = STATE_SETTING;
			}
			else if (pauseChoose == 3) {
				cleardevice();
				lastState = STATE_PAUSE;
				gameState = STATE_HELP;
			}
			else if (pauseChoose == 4) {
				gameState = STATE_MENU;
			}
			break;

		case STATE_VICTORY: {

			mciSendString(L"stop sfx", NULL, 0, NULL);
			mciSendString(L"stop hit_tank", NULL, 0, NULL);
			mciSendString(L"stop hit_wall", NULL, 0, NULL);

			int choice = Victory();
			if (choice == 2) {
				gameState = STATE_MENU;
			}
			else if (choice == 1) {
				if (lastState == STATE_PLAYING) {
					gameState = STATE_SELECT_LEVEL1;
				}
				else if (lastState == STATE_DOUBLEPEOPLE) {
					gameState = STATE_SELECT_LEVEL2;
				}
				else if (lastState == STATE_BASE) {
					gameState = STATE_SELECT_LEVEL3;
				}
			}
			break;
		}

		case STATE_DEFEAT: {

			mciSendString(L"stop sfx", NULL, 0, NULL);
			mciSendString(L"stop hit_tank", NULL, 0, NULL);
			mciSendString(L"stop hit_wall", NULL, 0, NULL);

			int choice = Defeat();
			if (choice == 0) {
				if (lastState == STATE_PLAYING) {
					gameState = STATE_SELECT_LEVEL1;
				}
				else if (lastState == STATE_DOUBLEPEOPLE) {
					gameState = STATE_SELECT_LEVEL2;
				}
				else if (lastState == STATE_BASE) {
					gameState = STATE_SELECT_LEVEL3;
				}
			}
			else if (choice == 1) {
				gameState = STATE_MENU;
			}
			break;
		}

		case STATE_HELP:
			cleardevice();
			drawHelp();
			break;

		case STATE_SETTING:
			cleardevice();
			drawSetting();
			break;

		default:
			break;
		}
		FlushBatchDraw();
	}
	// 6. 关闭图形窗口S
}
