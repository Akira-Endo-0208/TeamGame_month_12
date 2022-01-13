#pragma once
#include "Struct.h"

const int MAPCOUNT_X = 25;
const int MAPCOUNT_Y = 25;
const int MAPCHIP_SIZE = 32;




void MapInf(int mapHand[4]);

void SetMap();

void RightColision(Object& objP, Object& objM, MapChipInf& mapP, MapChipInf& mapO);

void LeftColision(Object& objP, Object& objM, MapChipInf& mapP, MapChipInf& mapO);

void TopColision(Object& objP, Object& objM, MapChipInf& mapP, Jump& jump);

void BottomColision(Object& objP, Object& objM, MapChipInf& mapP, MapChipInf& mapJ, Jump& jump);

void DoorOpen(Object& objP, Object& objM, MapChipInf& mapP, MapChipInf& mapO);

void DoorColision(Object& objP, Object& objM, MapChipInf& mapP, MapChipInf& mapO);