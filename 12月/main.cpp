#include "DxLib.h"
#include "main.h"
#include "Struct.h"
#include "Enum.h"
#include "Player.h"
#include "Map.h"
#include "Change.h"
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// ウィンドウモードに設定
	ChangeWindowMode(TRUE);

	// ウィンドウサイズを手動では変更させず、
	// かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// タイトルを変更
	SetMainWindowText(TITLE);

	// 画面サイズの最大サイズ、カラービット数を設定(モニターの解像度に合わせる)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// 画面サイズを設定(解像度との比率で設定)
	SetWindowSizeExtendRate(1.0);

	// 画面の背景色を設定する
	SetBackgroundColor(0x00, 0x00, 0xFF);

	// DXlibの初期化
	if (DxLib_Init() == -1) { return -1; }

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	// 画像などのリソースデータの変数宣言と読み込み
	int mapChipHand[4];
	int mapChip = LoadDivGraph("unkoMapChip.png", 4, 4, 1, 32, 32, mapChipHand, true);
	int playerImage = LoadGraph("player.png");

	// ゲームループで使う変数の宣言
	// プレイヤー
	Player* player = new Player;

	MapChipInf playerMap = {};

	MapChipInf oldPlayerMap = {};

	MapChipInf jumpPlayerMap = {};

	Change chg =
	{
		0,
		0,
		0,
		0,
		50,
		0,
		0,
		0,
		0,
		0,
		0
	};
	// 最新のキーボード情報用
	char keys[256] = { 0 };

	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[256] = { 0 };

	// ゲームループ
	while (1)
	{
		// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
		for (int i = 0; i < 256; i++)
		{
			oldkeys[i] = keys[i];
		}
		// 最新のキーボード情報を取得
		GetHitKeyStateAll(keys);

		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		// 更新処理

		ChangeScene(chg,keys);

		if (chg.scene == 1)
		{
			player->oldMovePos = player->movePos;

			player->Move(keys);
			player->Jump(keys, oldkeys);
			player->Fall();

			playerMap.left = (player->movePos.transform.x - player->pos.transform.width / 2) / MAPCHIP_SIZE;
			playerMap.right = (player->movePos.transform.x + player->pos.transform.width / 2 - 1) / MAPCHIP_SIZE;
			playerMap.top = (player->movePos.transform.y - player->pos.transform.height / 2) / MAPCHIP_SIZE;
			playerMap.bottom = (player->movePos.transform.y + player->pos.transform.height / 2 - 1) / MAPCHIP_SIZE;

			jumpPlayerMap.bottom = (player->movePos.transform.y + player->pos.transform.height / 2) / MAPCHIP_SIZE;

			oldPlayerMap.top = (player->oldMovePos.transform.y - player->pos.transform.height / 2) / MAPCHIP_SIZE;
			oldPlayerMap.bottom = (player->oldMovePos.transform.y + player->pos.transform.height / 2 - 1) / MAPCHIP_SIZE;

			RightColision(player->pos, player->movePos, playerMap, oldPlayerMap);
			LeftColision(player->pos, player->movePos, playerMap, oldPlayerMap);


			playerMap.left = (player->movePos.transform.x - player->pos.transform.width / 2) / MAPCHIP_SIZE;
			playerMap.right = (player->movePos.transform.x + player->pos.transform.width / 2 - 1) / MAPCHIP_SIZE;

			TopColision(player->pos, player->movePos, playerMap, player->jump);
			BottomColision(player->pos, player->movePos, playerMap, jumpPlayerMap, player->jump);

			DoorOpen(player->pos, player->movePos, playerMap, oldPlayerMap);

			player->pos = player->movePos;
		}


		// 描画処理

		if (chg.scene == 1)
		{
			MapInf(mapChipHand);
			SetMap();
			player->Draw(playerImage);

			DrawFormatString(0, 0, GetColor(255, 255, 255), "%d", player->jump.f);

		}

		ChangeDraw(chg);
		//---------  ここまでにプログラムを記述  ---------//
		// (ダブルバッファ)裏面
		ScreenFlip();

		// 20ミリ秒待機(疑似60FPS)
		WaitTimer(20);

		// Windowsシステムからくる情報を処理する
		if (ProcessMessage() == -1)
		{
			break;
		}

		// ESCキーが押されたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			break;
		}
	}
	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	return 0;
}