#pragma once
#include "Struct.h"

class Player
{
public:
	Transform tramsform;
	Object pos;
	Object movePos;
	Object oldMovePos;
	Jump jump;
public:
	Player();
	~Player();
	void Move(char* keys);
	void Jump(char* keys, char* oldkeys);
	void Fall();
	void Draw(int image);
};