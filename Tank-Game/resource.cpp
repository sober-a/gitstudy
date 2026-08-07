#include "resource.h"

// ==================== 地图背景图 ====================
IMAGE img_bg_level1, img_bg_level2, img_bg_level3, img_bg_level4, img_bg_level5, img_bg_level6;

// ==================== 障碍物贴图 ====================
IMAGE tile_grass_wall, tile_grass_forest;
IMAGE tile_desert_pyramid, tile_desert_brick;
IMAGE tile_lava_stone, tile_lava_brick;
IMAGE tile_wasteland_grass, tile_wasteland_tree, tile_wasteland_shrub, tile_wasteland_box;
IMAGE tile_snow_ice, tile_snow_brick, tile_snow_snowman, tile_snow_tree;
IMAGE tile_dark_stone, tile_dark_iron;

// ==================== 坦克贴图 ====================
IMAGE tank_player1_up, tank_player1_down, tank_player1_left, tank_player1_right;
IMAGE tank_player2_up, tank_player2_down, tank_player2_left, tank_player2_right;
IMAGE tank_enemy_up, tank_enemy_down, tank_enemy_left, tank_enemy_right;

// ==================== 基地贴图 ====================
IMAGE img_base;

// ==================== 道具生成点贴图 ====================
IMAGE pos_pow, pos_spe,item_hp;

// ==================== 普通子弹贴图 ====================
IMAGE bullet_up, bullet_down, bullet_left, bullet_right;
// ==================== 道具贴图 ====================

IMAGE powbullet_up, powbullet_down, powbullet_left, powbullet_right;//强力子弹
IMAGE spebullet_up, spebullet_down, spebullet_left, spebullet_right;//穿墙弹

// ==================== 主菜单界面 ====================
IMAGE ui_mainmenu_bg, ui_mainmeau_choose;

// ==================== 帮助界面 =====================
IMAGE ui_help;

// ==================== 暂停界面 =====================
IMAGE ui_pause;

// ==================== 设置界面 =====================
IMAGE ui_setting_on, ui_setting_off;

// ==================== 结算界面 =====================
IMAGE ui_defeat, ui_victory;

// ==================== 选关概览图 ====================
IMAGE ui_select_bg;
IMAGE btn_level1, btn_level2, btn_level3, btn_level4, btn_level5, btn_level6;

// ==================== 信息栏贴图 ====================
IMAGE ui_info_bk1, ui_hp;
IMAGE ui_hp_jidi, ui_info_bk2, ui_info_bk3;	//拓展
IMAGE ui_num0, ui_num1, ui_num2, ui_num3, ui_num4;
IMAGE ui_num5, ui_num6, ui_num7, ui_num8, ui_num9;

// ==================== service 层函数声明 ====================
/*
	负责人:淡写青春
	功能:加载所有图片数据
	参数:无
	返回值:空
*/
void initImage() {
	// 第1关：草地
	loadimage(&img_bg_level1, L"image/bj1.png", 1300, 800);
	loadimage(&tile_grass_wall, L"image/1.1.png", 50, 50);
	loadimage(&tile_grass_forest, L"image/1.2.png", 50, 50);

	// 第2关：沙漠
	loadimage(&img_bg_level2, L"image/bj2.png", 1300, 800);
	loadimage(&tile_desert_brick, L"image/2.1.png", 50, 50);
	loadimage(&tile_desert_pyramid, L"image/2.2.png", 50, 50);

	// 第3关：岩浆
	loadimage(&img_bg_level3, L"image/bj3.png", 1300, 800);
	loadimage(&tile_lava_stone, L"image/3.1.png", 50, 50);
	loadimage(&tile_lava_brick, L"image/3.2.png", 50, 50);

	// 第4关：荒地
	loadimage(&img_bg_level4, L"image/bj4.png", 1300, 800);
	loadimage(&tile_wasteland_grass, L"image/4.1.jpg", 50, 50);
	loadimage(&tile_wasteland_tree, L"image/4.2.png", 50, 50);
	loadimage(&tile_wasteland_shrub, L"image/4.3.png", 50, 50);
	loadimage(&tile_wasteland_box, L"image/4.4.png", 50, 50);

	// 第5关：雪地
	loadimage(&img_bg_level5, L"image/bj5.png", 1300, 800);
	loadimage(&tile_snow_ice, L"image/5.1.png", 50, 50);
	loadimage(&tile_snow_brick, L"image/5.2.jpg", 50, 50);
	loadimage(&tile_snow_snowman, L"image/5.3.png", 50, 50);
	loadimage(&tile_snow_tree, L"image/5.4.png", 50, 50);

	// 第6关：地牢
	loadimage(&img_bg_level6, L"image/bj6.png", 1300, 800);
	loadimage(&tile_dark_stone, L"image/6.1.png", 50, 50);
	loadimage(&tile_dark_iron, L"image/6.2.png", 50, 50);
	//基地
	loadimage(&img_base, L"image/jidi.png", 100, 100);
	//道具及道具生成点
	loadimage(&item_hp, L"image/Medkit.png", 50, 50);
	loadimage(&pos_pow, L"image/item_bu_pro2.png", 50, 50);
	loadimage(&pos_spe, L"image/item_bu_pro1.png", 50, 50);
	// 玩家坦克
	loadimage(&tank_player1_up, L"image/tk1.1.png", 50, 50);
	loadimage(&tank_player1_down, L"image/tk1.2.png", 50, 50);
	loadimage(&tank_player1_left, L"image/tk1.3.png", 50, 50);
	loadimage(&tank_player1_right, L"image/tk1.4.png", 50, 50);
	loadimage(&tank_player2_up, L"image/tk2.1.png", 50, 50);
	loadimage(&tank_player2_down, L"image/tk2.2.png", 50, 50);
	loadimage(&tank_player2_left, L"image/tk2.3.png", 50, 50);
	loadimage(&tank_player2_right, L"image/tk2.4.png", 50, 50);

	// 敌方坦克
	loadimage(&tank_enemy_up, L"image/tk3.1.png", 50, 50);
	loadimage(&tank_enemy_down, L"image/tk3.2.png", 50, 50);
	loadimage(&tank_enemy_left, L"image/tk3.3.png", 50, 50);
	loadimage(&tank_enemy_right, L"image/tk3.4.png", 50, 50);

	// 子弹
	loadimage(&bullet_up, L"image/bu1.1.png", 25, 25);
	loadimage(&bullet_down, L"image/bu1.2.png", 25, 25);
	loadimage(&bullet_left, L"image/bu1.3.png", 25, 25);
	loadimage(&bullet_right, L"image/bu1.4.png", 25, 25);
	loadimage(&spebullet_up, L"image/bu_pro1.1.png", 25, 25);
	loadimage(&spebullet_down, L"image/bu_pro1.2.png", 25, 25);
	loadimage(&spebullet_left, L"image/bu_pro1.3.png", 25, 25);
	loadimage(&spebullet_right, L"image/bu_pro1.4.png", 25, 25);
	loadimage(&powbullet_up, L"image/bu_pro2.1.png", 25, 25);
	loadimage(&powbullet_down, L"image/bu_pro2.2.png", 25, 25);
	loadimage(&powbullet_left, L"image/bu_pro2.3.png", 25, 25);
	loadimage(&powbullet_right, L"image/bu_pro2.4.png", 25, 25);

	// 主界面UI
	loadimage(&ui_mainmenu_bg, L"image/STATE_MENU.png", 1500, 800);
	loadimage(&ui_mainmeau_choose, L"image/choose.png", 500, 300);

	//帮助，设置，暂停，结算界面
	loadimage(&ui_help, L"image/STATE_HELP.png", 1500, 800);
	loadimage(&ui_setting_on, L"image/STATE_SETTING_on.png", 1067, 800);
	loadimage(&ui_setting_off, L"image/STATE_SETTING_off.png", 1067, 800);
	loadimage(&ui_pause, L"image/STATE_PAUSE.png", 888, 800);
	loadimage(&ui_defeat, L"image/STATE_DEFEAT.png", 750, 500);
	loadimage(&ui_victory, L"image/STATE_VICTORY.png", 750, 500);

	// 关卡界面
	loadimage(&ui_select_bg, L"image/select_bg.png", 1500, 800);
	loadimage(&btn_level1, L"image/level1.png", 493, 156);
	loadimage(&btn_level2, L"image/level2.png", 493, 156);
	loadimage(&btn_level3, L"image/level3.png", 493, 156);
	loadimage(&btn_level4, L"image/level4.png", 493, 156);
	loadimage(&btn_level5, L"image/level5.png", 493, 156);
	loadimage(&btn_level6, L"image/level6.png", 493, 156);

	//信息栏UI
	loadimage(&ui_info_bk1, L"image/info_bk1.png", 200, 800);
	loadimage(&ui_info_bk2, L"image/info_bk2.png", 200, 800);
	loadimage(&ui_info_bk3, L"image/info_bk3.png", 200, 800);
	loadimage(&ui_hp_jidi, L"image/HP2.png", 25, 15);
	loadimage(&ui_hp, L"image/HP1.png", 25, 15);
	loadimage(&ui_num0, L"image/num0.png", 20, 30);
	loadimage(&ui_num1, L"image/num1.png", 20, 30);
	loadimage(&ui_num2, L"image/num2.png", 20, 30);
	loadimage(&ui_num3, L"image/num3.png", 20, 30);
	loadimage(&ui_num4, L"image/num4.png", 20, 30);
	loadimage(&ui_num5, L"image/num5.png", 20, 30);
	loadimage(&ui_num6, L"image/num6.png", 20, 30);
	loadimage(&ui_num7, L"image/num7.png", 20, 30);
	loadimage(&ui_num8, L"image/num8.png", 20, 30);
	loadimage(&ui_num9, L"image/num9.png", 20, 30);

}

/*
	负责人：晨懿
	功能：播放BGM（循环播放）
	参数：无
	返回值：空
*/
void playBGM() {
	if (!g_bgmPlaying) {
		// 使用 PlaySound 播放 WAV，循环播放
		PlaySound(L"music\\bgm.wav", NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
		g_bgmPlaying = true;
	}
}

/*
	负责人：晨懿
	功能：停止BGM
	参数：无
	返回值：空
*/
void stopBGM() {
	if (g_bgmPlaying) {
		PlaySound(NULL, NULL, 0);  // 停止所有播放
		g_bgmPlaying = false;
	}
}
/*
	负责人：晨懿
	功能：设置当前程序的音量
	参数：int volume
	返回值：空
*/
void SetApplicationVolume(int volume) {
	// 将 0~100 映射到 0x0000~0xFFFF
	WORD vol = (WORD)(volume * 65535 / 100);
	DWORD dwVol = (vol << 16) | vol;  // 左右声道相同
	waveOutSetVolume(0, dwVol);       // 0 表示默认音频设备
}

/*
	负责人：晨懿
	功能：获取当前程序音量
	参数：无
	返回值：int
*/
int GetApplicationVolume() {
	DWORD dwVol = 0;
	waveOutGetVolume(0, &dwVol);
	WORD vol = LOWORD(dwVol);  // 左右声道相同
	return (int)(vol * 100 / 65535);
}
