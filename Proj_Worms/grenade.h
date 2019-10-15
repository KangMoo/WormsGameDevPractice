#pragma once
#include "Weapon.h"
class grenade : public Weapon
{
private:
	POINT * _camera;
	int _weaponXsize;
	int _weaponYsize;
	RECT _rc;
	bool _keepMove;
	float _timer;
public:
	HRESULT init(float power, float angle, POINT stPoint, POINT mousePoint, Map* map, UI* ui, PlayerManager* pm);
	void release();
	void update();
	void render();
	void draw();

	void isUnderwater();
	void colliChk();	//충돌체크
	void timerCtrl();	//타이머 설정
	void frameCtrl();	//프레임 설정
	void move();		//이동
	void boom();		//폭발
	grenade();
	~grenade();
};

