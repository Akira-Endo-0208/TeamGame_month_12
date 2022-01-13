#pragma once

typedef struct Transform
{
	float x;
	float y;
	int width;
	int height;
}Transform;

typedef struct Object
{
	Transform transform;
	int speed;
}Object;

typedef struct Jump
{
	bool f;
	int p;
	int max;
} Jump;

typedef struct MapChipInf
{
	int top;
	int left;
	int right;
	int bottom;
}MapChipInf;

typedef struct Change
{
	int scene;
	int isSpace;
	double flameTime;
	double flameTime2;
	double maxTime;
	int delay;
	int isdisplay;
	int isdisapper;
	double quintX;
	double quintY;
	double outBackY;

};