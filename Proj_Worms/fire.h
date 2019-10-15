#pragma once
#include "Weapon.h"

class fire : public Weapon
{
private:
	POINT * _camera;
	float _dmg;
public:
	HRESULT init(float power, float angle, POINT stPoint, POINT mousePoint, Map* map, UI* ui, PlayerManager* pm);
	void release();
	void update();
	void render();
	void draw();

	void isUnderwater();
	void imgCtrl();
	void frameCtrl();
	void move();
	
	fire();
	~fire();
};

