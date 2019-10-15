#pragma once
#include "Weapon.h"
class teleport : public Weapon
{
private:
	POINT * _camera;
	int _weaponXsize;
	int _weaponYsize;
	RECT _rc;
	bool _keepMove;
	float _timer;

	POINT _telePortPoint;
public:
	HRESULT init(float power, float angle, POINT stPoint, POINT mousePoint, Map* map, UI* ui, PlayerManager* pm);
	void release();
	void update();
	void render();
	void draw();


	teleport();
	~teleport();
};

