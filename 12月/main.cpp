#include "DxLib.h"
#include "main.h"
#include "Struct.h"
#include "Enum.h"
#include "Player.h"
#include "Map.h"
#include "Change.h"
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// �E�B���h�E���[�h�ɐݒ�
	ChangeWindowMode(TRUE);

	// �E�B���h�E�T�C�Y���蓮�ł͕ύX�������A
	// ���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// �^�C�g����ύX
	SetMainWindowText(TITLE);

	// ��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�(���j�^�[�̉𑜓x�ɍ��킹��)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// ��ʃT�C�Y��ݒ�(�𑜓x�Ƃ̔䗦�Őݒ�)
	SetWindowSizeExtendRate(1.0);

	// ��ʂ̔w�i�F��ݒ肷��
	SetBackgroundColor(0x00, 0x00, 0xFF);

	// DXlib�̏�����
	if (DxLib_Init() == -1) { return -1; }

	// (�_�u���o�b�t�@)�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���
	int mapChipHand[4];
	int mapChip = LoadDivGraph("unkoMapChip.png", 4, 4, 1, 32, 32, mapChipHand, true);
	int playerImage = LoadGraph("player.png");

	// �Q�[�����[�v�Ŏg���ϐ��̐錾
	// �v���C���[
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
	// �ŐV�̃L�[�{�[�h���p
	char keys[256] = { 0 };

	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
	char oldkeys[256] = { 0 };

	// �Q�[�����[�v
	while (1)
	{
		// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
		for (int i = 0; i < 256; i++)
		{
			oldkeys[i] = keys[i];
		}
		// �ŐV�̃L�[�{�[�h�����擾
		GetHitKeyStateAll(keys);

		// ��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		// �X�V����

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


		// �`�揈��

		if (chg.scene == 1)
		{
			MapInf(mapChipHand);
			SetMap();
			player->Draw(playerImage);

			DrawFormatString(0, 0, GetColor(255, 255, 255), "%d", player->jump.f);

		}

		ChangeDraw(chg);
		//---------  �����܂łɃv���O�������L�q  ---------//
		// (�_�u���o�b�t�@)����
		ScreenFlip();

		// 20�~���b�ҋ@(�^��60FPS)
		WaitTimer(20);

		// Windows�V�X�e�����炭�������������
		if (ProcessMessage() == -1)
		{
			break;
		}

		// ESC�L�[�������ꂽ�烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			break;
		}
	}
	// Dx���C�u�����I������
	DxLib_End();

	// ����I��
	return 0;
}