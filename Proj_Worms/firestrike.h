#pragma once
#include "Weapon.h"
#include "fire.h"



class firestrike : public Weapon
{
private:
	POINT * _camera;
	tagPlane _plane;
	vector<fire*> _vfire;
public:
	HRESULT init(float power, float angle, POINT stPoint, POINT mousePoint, Map* map, UI* ui, PlayerManager* pm);
	void release();
	void update();
	void render();
	void draw();

	void planeFireCtrl();
	void planeMoveCtrl();
	void frameCtrl();
	void removeMisl(int arrNum);
	void move();
	firestrike();
	~firestrike();
};

