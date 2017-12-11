#pragma once
#include "gameNode.h"

#define WORMXSIZE 10
#define WORMYSIZE 20

enum WEAPON
{
	WEAPON_BAZOOKA,
	WEAPON_HIMMING_MISSILE,
	WEAPON_GRENADE,
	WEAPON_CLUSTER,
	WEAPON_PETROL,
	WEAPON_BANANA,
	WEAPON_HOLY,
	WEAPON_SHOTGUN,
	WEAPON_DYNAMITE,
	WEAPON_MINE,
	WEAPON_FIREPUNCH,
	WEAPON_BASEBALLBAT,
	WEAPON_AIRSTRIKE,
	WEAPON_NAPALMSTRIKE,
	WEAPON_GIRDER,
	WEAPON_ROPE,
	WEAPON_TELEPORT,
	WEAPON_SKIPGO,
	WEAPON_SURRENDER,
};

typedef struct tagWeapon
{
	WEAPON weaponType;
	image* weaponImg;
	image* weaponIcon;
	int currenFrameX;
	int currenFrameY;
	float xPoint;
	float yPoint;
	float xSpeed;
	float ySpeed;
};

enum WORMSTATE {
	WORMSTATE_IDLE,
	WORMSTATE_FALLING,
	WORMSTATE_MOVING,
	WORMSTATE_WEAPONSTATE,
	WORMSTATE_DYING,
	WORMSTATE_DROWNING,
	WORMSTATE_DEAD,
	WORMSTATE_END
};

typedef struct tagWorm {
	image* img;
	RECT rc;
	int hp;
	int maxhp;
	float currentFrameX;
	float currentFrameY;
	float Pointx;
	float Pointy;
	int team;
}WORM;

