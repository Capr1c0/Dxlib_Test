#include "Main.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//Windowモード設定用
	ChangeWindowMode(TRUE);
	SetWaitVSyncFlag(TRUE);
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);
	SetGraphMode(1280, 720, 32);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}
	Main main;
	main.GameLoop();

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}

void Main::GameLoop() {
	int LED_HND = LoadGraph("data/LED.png");
	int LED_R = LoadGraph("data/red.png");
	int LED_G = LoadGraph("data/green.png");
	int LED_B = LoadGraph("data/blue.png");

	int LED_RED = MakeScreen(50, 50, TRUE);
	int LED_GREEN = MakeScreen(50, 50, TRUE);
	int LED_BLUE = MakeScreen(50, 50, TRUE);

	//赤
	SetDrawScreen(LED_RED);
	DrawGraph(0, 0, LED_HND, TRUE);
	GraphBlend(
		LED_RED,
		LED_R, 255, DX_GRAPH_BLEND_RGBA_SELECT_MIX,
		DX_RGBA_SELECT_BLEND_R,
		DX_RGBA_SELECT_BLEND_G,
		DX_RGBA_SELECT_BLEND_B,
		DX_RGBA_SELECT_SRC_A
	);

	//緑
	SetDrawScreen(LED_GREEN);
	DrawGraph(0, 0, LED_HND, TRUE);
	GraphBlend(
		LED_GREEN,
		LED_G, 255, DX_GRAPH_BLEND_RGBA_SELECT_MIX,
		DX_RGBA_SELECT_BLEND_R,
		DX_RGBA_SELECT_BLEND_G,
		DX_RGBA_SELECT_BLEND_B,
		DX_RGBA_SELECT_SRC_A
	);

	//青
	SetDrawScreen(LED_BLUE);
	DrawGraph(0, 0, LED_HND, TRUE);
	GraphBlend(
		LED_BLUE,
		LED_B, 255, DX_GRAPH_BLEND_RGBA_SELECT_MIX,
		DX_RGBA_SELECT_BLEND_R,
		DX_RGBA_SELECT_BLEND_G,
		DX_RGBA_SELECT_BLEND_B,
		DX_RGBA_SELECT_SRC_A
	);


	int offscreen = MakeScreen(1280, 720, TRUE);

	//各色情報を格納するハンドル
	int Colors[1024];
	for (int i = 0; i < 1024; i++) {
		if (i % 3 == 0)
		{
			Colors[i] = LED_RED;
		}
		else if (i % 3 == 1)
		{
			Colors[i] = LED_GREEN;

		}
		else {
			Colors[i] = LED_BLUE;
		}
	}

	int timer = 0;
	while (true) {
		timer++;
		if (timer > 12) {
			SetDrawScreen(offscreen);
			Colors[1023] = Colors[0];
			for (int i = 1; i < 1024; i++) {
				Colors[i - 1] = Colors[i];
			}
			for (int i = 0; i < 1024; i++) {
				int Row = i % 40;
				int Col = (i - Row) / 40;

				DrawGraph(25 * Row + 25, 25 * Col + 25, Colors[i], TRUE);
			}
			SetDrawScreen(DX_SCREEN_FRONT);
			ClearDrawScreen();
			DrawGraph(0, 0, offscreen, TRUE);
			timer = 0;
		}
		ScreenFlip();
	}

	//開放
	DeleteGraph(LED_HND);
	DeleteGraph(LED_R);
	DeleteGraph(LED_G);
	DeleteGraph(LED_B);
	DeleteGraph(LED_RED);
	DeleteGraph(LED_GREEN);
	DeleteGraph(LED_BLUE);
}
