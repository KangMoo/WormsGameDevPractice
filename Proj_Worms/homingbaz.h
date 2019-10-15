#pragma once
#include "Weapon.h"
class homingbaz : public Weapon
{
private:
	POINT * _camera;
	POINT _markPoint;
	float _homingSttimer;
	float _homingEndtimer;
	float _angleUpdateTimer;
	bool _isHoming;
public:
	HRESULT init(float power, float angle, POINT stPoint, POINT mousePoint, Map* map, UI* ui, PlayerManager* pm);
	void release();
	void update();
	void render();
	void draw();

	void isUnderwater();
	void homing();
	void frameCtrl();
	void move();
	void boom();
	homingbaz();
	~homingbaz();
};

