#pragma once
#include "Weapon.h"
class banana2 : public Weapon
{
private:
	POINT * _camera;
public:
	HRESULT init(float power, float angle, POINT stPoint, POINT mousePoint, Map* map, UI* ui, PlayerManager* pm);
	void release();
	void update();
	void render();
	void draw();

	void isUnderwater();
	void frameCtrl();
	void move();
	void boom();
	banana2();
	~banana2();
};

