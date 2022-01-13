#include "DxLib.h"
#include "Struct.h"
#include "Change.h"
#include "Easing.h"

void ChangeScene(Change& chg,char* keys)
{

		if (chg.scene == 0 && keys[KEY_INPUT_SPACE] == 1 && chg.isSpace == 0)
		{
			
			chg.isSpace = 1;
			chg.flameTime = 0;
			chg.flameTime2 = -7;
			chg.isdisplay = 0;
			chg.delay = 0;
			chg.isdisapper = 0;
		}

		if (chg.isSpace == 1 && chg.flameTime < 60)
		{
			chg.flameTime += 2.5;
		}
		else if (chg.flameTime >= 60 && chg.delay < 30)
		{
			chg.isdisplay = 1;
			chg.flameTime = 60;
			chg.flameTime2 += 2.5;
			chg.delay++;
		}
		else if (chg.delay >= 30)
		{
			chg.scene = 1;
			chg.flameTime2 -= 2.5;
		}

		if (chg.flameTime2 < 0 && chg.delay >= 30)
		{
			chg.isdisapper = 1;
		}
		if (chg.flameTime2 < -8)
		{
			chg.flameTime2 = 0;
			chg.isSpace = 0;
			chg.isdisplay = 0;
		}

	chg.quintX = easeOutQuint(200, 0, chg.flameTime2 / chg.maxTime);
	chg.quintY = easeOutQuint(200, 0, chg.flameTime2 / chg.maxTime);
	chg.outBackY = easeOutBack(0, 350, chg.flameTime / chg.maxTime);
}

void ChangeDraw(Change chg)
{
	if (chg.isdisplay == 1)
	{
		DrawBox(-chg.quintX , -chg.quintY, chg.quintX + 800, chg.quintY + 800, GetColor(226, 212, 192), true);

	}
	if (chg.isdisapper == 0)
	{
		DrawBox(330, chg.outBackY, 460, chg.outBackY + 50, GetColor(201, 149, 74), true);
		if (chg.delay >= 5)
		{

		}
		if (chg.delay >= 15)
		{

		}
		if (chg.delay >= 25)
		{

		}
	}
}