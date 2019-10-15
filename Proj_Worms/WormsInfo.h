#pragma once
#include "gameNode.h"

#define WORMXSIZE 10
#define WORMYSIZE 20
#define WORMSMOVINGSPEED 0.7
#define WORMJUMPXSPEED 2.5
#define WORMJUMPYSPEED 6
#define WORMBACKFLIPYSPEED 8
#define WORMBACKFLIPXSPEED 1.5
#define MAXXSPEED 15
#define MAXYSPEED 15
#define MAXXSLIDESPEED 4.9
#define VOLUME 0.6
struct tagGrave {
	image* img;
	RECT rc;
	float xPoint;
	float yPoint;
	int currentFrameX;
	int currentFrameY;
	float ySpeed;
};
enum TURNPHASE
{
	TURNPHASE_PLAYERTURN,
	TURNPHASE_WEAPONTURN,
	TURNPHASE_DAMAGETURN,
	TURNPHASE_DELAY,
	TURNPHASE_SETTURN,
};

enum WEAPON
{
	WEAPON_BAZOOKA,
	WEAPON_HIMMING_MISSILE,
	WEAPON_GRENADE,
	WEAPON_CLUSTER,
	WEAPON_PETROL,
	WEAPON_BANANA,
	WEAPON_HOLY,
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
	WEAPON_END
};

typedef struct tagWeapon
{
	WEAPON weaponType;
	image* weaponWormImg1;
	image* weaponWormImg2;
	image* weaponWormImg3;
	image* weaponImg;
	image* weaponIcon;
	int currentFrameX;
	int currentFrameY;
	float xPoint;
	float yPoint;
	float xSpeed;
	float ySpeed;
	bool isObject;
	bool del;

	float maxDmg;
	float minDmg;
	float maxKnockBackPower;
	float minKnockBackPower;
	float radius;
};


enum WORMSTATE {
	WORMSTATE_IDLE,
	WORMSTATE_FALLING,
	WORMSTATE_SLIDING,
	WORMSTATE_MOVING,
	WORMSTATE_FLYING,
	WORMSTATE_JUMPING,
	WORMSTATE_BACKFLIP,
	WORMSTATE_DYING,
	WORMSTATE_DROWNING,
	WORMSTATE_USINGWEAPON,
	WORMSTATE_DEAD,
	WORMSTATE_WEAPONSTATE,
	WORMSTATE_END
};
enum WEAPONHOLDTYPE
{
	WEAPONHOLDTYPE_ANGLE,		//각도에 따라 변함
	WEAPONHOLDTYPE_HOLD,		//들고만 있음
	WEAPONHOLDTYPE_SPECIAL		//기타 특수처리
};
typedef struct tagWorm {
	image* img;
	image* w_img1;
	image* w_img2;
	image* w_img3;
	RECT rc;
	WORMSTATE state;
	WEAPONHOLDTYPE wpholdtype;
	bool active;
	int hp;
	int maxhp;
	float angle;
	int currentFrameX;
	int currentFrameY;
	float xPoint;
	float yPoint;
	float xSpeed;
	float ySpeed;
	float frameUpdateTimer;
	bool getDamagedInThisTurn;
	int howmanyDmged;
	void ImgUpdate() { currentFrameY = 0; }
}WORM;

typedef struct tagPlayerItem {
	WEAPON type;
};

struct tagPlane {
	float xPoint;
	float yPoint;
	image* img;
	bool movingRight;
	int currentFrameX;
	int currentFrameY;
	bool fire;
};