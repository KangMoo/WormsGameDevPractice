#pragma once
#include "Weapon.h"
class mine : public Weapon
{
private:
	POINT * _camera;
	int _weaponXsize;
	int _weaponYsize;
	RECT _rc;
	float _startTimer;
	float _tictokTimer;
	bool _keepMove;
	bool _active;
	float _timer;
public:
	HRESULT init(float power, float angle, POINT stPoint, POINT mousePoint, Map* map, UI* ui, PlayerManager* pm);
	void release();
	void update();
	void render();
	void draw();
	void isUnderwater();
	void activeCtrl();
	void colliChk();	//�浹üũ
	void timerCtrl();	//Ÿ�̸� ����
	void frameCtrl();	//������ ����
	void move();		//�̵�
	void boom();		//����
	mine();
	~mine();
};

