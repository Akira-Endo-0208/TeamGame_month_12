#include "Map.h"
#include "DxLib.h"
#include "Enum.h"
#include "Struct.h"

int map[MAPCOUNT_Y][MAPCOUNT_X];

int map1[MAPCOUNT_Y][MAPCOUNT_X] =
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
	{1,0,0,0,1,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1},
	{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1},
	{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,1,1,1,1},
	{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,1,1,1,1,1},
	{1,0,0,0,1,1,1,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,1,1,1,1,1},
	{1,0,0,0,1,1,1,1,1,1,1,1,1,2,0,0,0,0,0,2,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,2,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,2,3,0,3,0,0,2,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void MapInf(int mapHand[4])
{
	for (int y = 0; y < MAPCOUNT_Y; y++)
	{
		for (int x = 0; x < MAPCOUNT_X; x++)
		{
			if (map[y][x] == SPACE)
			{
				DrawGraph(x * MAPCHIP_SIZE,
					y * MAPCHIP_SIZE,
					mapHand[0], true);
			}
			if (map[y][x] == BLOCK)
			{
				DrawGraph(x * MAPCHIP_SIZE,
					y * MAPCHIP_SIZE,
					mapHand[1], true);
			}
			if (map[y][x] == DOOR)
			{
				DrawGraph(x * MAPCHIP_SIZE,
					y * MAPCHIP_SIZE,
					mapHand[2], true);
			}
			if (map[y][x] == SWITCH)
			{
				DrawGraph(x * MAPCHIP_SIZE,
					y * MAPCHIP_SIZE,
					mapHand[3], true);
			}
		}
	}
}

void SetMap()
{
	for (int y = 0; y < MAPCOUNT_Y; y++)
	{
		for (int x = 0; x < MAPCOUNT_X; x++)
		{
			map[y][x] = map1[y][x];
		}
	}
}

void RightColision(Object& objP, Object& objM, MapChipInf& mapP, MapChipInf& mapO)
{
	if (objM.transform.x - objP.transform.x > 0)
	{
		if (map[mapO.top][mapP.right] == BLOCK ||
			map[mapO.bottom][mapP.right] == BLOCK ||
			map[mapO.top][mapP.right] == DOOR ||
			map[mapO.bottom][mapP.right] == DOOR)
		{
			objM.transform.x = MAPCHIP_SIZE * (mapP.left) + objP.transform.width / 2;
		}

	}
}

void LeftColision(Object& objP, Object& objM, MapChipInf& mapP, MapChipInf& mapO)
{
	if (objM.transform.x - objP.transform.x < 0)
	{
		if (map[mapO.top][mapP.left] == BLOCK ||
			map[mapO.bottom][mapP.left] == BLOCK ||
			map[mapO.top][mapP.left] == DOOR ||
			map[mapO.bottom][mapP.left] == DOOR)
		{
			objM.transform.x = MAPCHIP_SIZE * (mapP.left + 1) + objP.transform.width / 2;
		}
	}
}

void TopColision(Object& objP, Object& objM, MapChipInf& mapP, Jump& jump)
{
	if (objM.transform.y - objP.transform.y < 0)
	{
		if (map[mapP.top][mapP.left] == BLOCK ||
			map[mapP.top][mapP.right] == BLOCK ||
			map[mapP.top][mapP.left] == DOOR ||
			map[mapP.top][mapP.right] == DOOR)
		{
			objM.transform.y = MAPCHIP_SIZE * (mapP.top + 1) + objP.transform.height / 2;
			if (jump.f == true)
			{
				jump.p = 0;
			}
		}
	}
}

void BottomColision(Object& objP, Object& objM, MapChipInf& mapP, MapChipInf& mapJ, Jump& jump)
{
	if (objM.transform.y - objP.transform.y > 0)
	{
		if (map[mapP.bottom][mapP.left] == BLOCK ||
			map[mapP.bottom][mapP.right] == BLOCK ||
			map[mapP.bottom][mapP.left] == DOOR ||
			map[mapP.bottom][mapP.right] == DOOR)
		{
			objM.transform.y = MAPCHIP_SIZE * (mapP.bottom) - objP.transform.height / 2;
			if (jump.f == true)
			{
				jump.f = false;
			}
		}
	}
	else if (map[mapJ.bottom][mapP.left] != BLOCK &&
		map[mapJ.bottom][mapP.right] != BLOCK &&
		jump.f == false)
	{
		jump.p = 0;
		jump.f = true;
	}
}

void DoorOpen(Object& objP, Object& objM, MapChipInf& mapP, MapChipInf& mapO)
{
	for (int y = 0; y < MAPCOUNT_Y; y++)
	{
		for (int x = 0; x < MAPCOUNT_X; x++)
		{
			if (map[mapP.bottom][mapP.left] == SWITCH ||
				map[mapP.bottom][mapP.right] == SWITCH)
			{
				if (map1[y][x] == DOOR)
				{
					map1[y][x] = NONE;
				}
				
			}
			else if (map[mapP.bottom][mapP.left] != SWITCH ||
				map[mapP.bottom][mapP.right] != SWITCH)
			{
				if (map1[y][x] == NONE)
				{
					map1[y][x] = DOOR;
				}
			}
		}
	}
}

