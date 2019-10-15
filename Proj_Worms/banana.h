#pragma once
#include "Weapon.h"
#include "banana2.h"

class banana : public Weapon
{
private:
	POINT * _camera;
	int _weaponXsize;
	int _weaponYsize;
	RECT _rc;
	bool _keepMove;
	float _timer;

	vector<banana2*> _vban2;

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

	banana();
	~banana();
};

