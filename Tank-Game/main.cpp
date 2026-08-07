#include "common.h"
#include "runGame.h"

int main() {
	initImage();
	initgraph(1500, 800);

	mciSendString(L"open \"music/fire.wav\" type waveaudio alias sfx", NULL, 0, NULL);
	mciSendString(L"open \"music/hit_tank.wav\" type waveaudio alias hit_tank", NULL, 0, NULL);
	mciSendString(L"open \"music/hit_wall.wav\" type waveaudio alias hit_wall", NULL, 0, NULL);
	SetApplicationVolume(g_soundVolume);
	BeginBatchDraw();
	srand((unsigned)time(NULL));
	gameState = STATE_MENU;
	playBGM();

	runGame();

	EndBatchDraw();
	stopBGM();
	closegraph();
	return 0;
}
