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
	void colliChk();	//�浹üũ
	void timerCtrl();	//Ÿ�̸� ����
	void frameCtrl();	//������ ����
	void move();		//�̵�
	void boom();		//����
	grenade();
	~grenade();
};

