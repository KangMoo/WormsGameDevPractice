#pragma once
#include "gameNode.h"
#include "Map.h"
#include "Player.h"
#include "UI.h"
#include "Weapon.h"

class BattleScene : public gameNode
{
private:
	Map* _map;
	Player* _player;
	UI* _ui;
	Weapon* _weapon;


	float _turnTimer;
	float _bonusTimer;

public:
	HRESULT init();
	void release();
	void update();
	void render();




	BattleScene();
	~BattleScene();
};

