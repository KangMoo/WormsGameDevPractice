#pragma once
#include "Weapon.h"
#include "airmisl.h"


class airstrike : public Weapon
{
private:
	POINT * _camera;
	tagPlane _plane;
	vector<airmisl*> _vmisl;
public:
	HRESULT init(float power, float angle, POINT stPoint, POINT mousePoint, Map* map, UI* ui, PlayerManager* pm);
	void release();
	void update();
	void render();
	void draw();
	void isUnderwater();
	void planeFireCtrl();
	void planeMoveCtrl();
	void frameCtrl();
	void removeMisl(int arrNum);
	void move();
	airstrike();
	~airstrike();
};

