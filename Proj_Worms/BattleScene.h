#pragma once
#include "gameNode.h"
#include "Map.h"
#include "Player.h"
#include "UI.h"
#include "Weapon.h"
#include "WeaponManager.h"
#include "PlayerManager.h"

class BattleScene : public gameNode
{
private:
	Map* _map;
	UI* _ui;
	WeaponManager* _wm;
	PlayerManager* _pm;

	float _turnTimer;
	float _bonusTimer;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void gameOverChk();
	void addImg();
	void addSound();


	BattleScene();
	~BattleScene();
};

