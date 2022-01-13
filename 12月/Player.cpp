#include "DxLib.h"
#include "main.h"
#include "Player.h"
#include "Struct.h"

Player::Player()
{
	tramsform.x = WIN_WIDTH / 2;
	tramsform.y = WIN_HEIGHT / 2;
	tramsform.width = 32;
	tramsform.height = 32;
	pos.transform = tramsform;
	pos.speed = 6;
	movePos = pos;
	oldMovePos = movePos;
	jump.f = false;
	jump.p = 0;
	jump.max = 15;
}

Player::~Player()
{

}

void Player::Move(char* keys)
{
	if (keys[KEY_INPUT_LEFT] == 1)
	{
		movePos.transform.x -= movePos.speed;
	}

	if (keys[KEY_INPUT_RIGHT] == 1)
	{
		movePos.transform.x += movePos.speed;
	}
}

void Player::Jump(char* keys, char* oldkeys)
{
	if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0 && jump.f == false)
	{
		jump.f = true;
		jump.p = jump.max;
	}
}

void Player::Fall()
{
	if (jump.f == true)
	{
		movePos.transform.y -= jump.p;
		if (jump.p > -jump.max)
		{
			jump.p--;
		}
	}
}

void Player::Draw(int image)
{
	DrawExtendGraph(pos.transform.x - pos.transform.width / 2,
		pos.transform.y - pos.transform.height / 2,
		pos.transform.x + pos.transform.width / 2,
		pos.transform.y + pos.transform.height / 2,
		image, true);
}