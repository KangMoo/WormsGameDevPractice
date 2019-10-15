#pragma once
#include "gameNode.h"
#include "Player.h"

class Map;
class UI;
class WeaponManager;

class PlayerManager : public gameNode
{
private:
	Map* _map;
	UI* _ui;
	WeaponManager* _wm;
	POINT* _camera;
	vector<Player*> _vPlayer;
	bool _showCRH;
	POINT _crhPoint;
	vector<Worm*> _vWormForDmgFunc;
	TURNPHASE _turnphase;
	bool _isGameOver;
	float _gameOverTiemr;
	int _playerTurnNum;
	float _playerturnTimer;
	float _weaponturnTimer;
	float _dmgTimer;
	float _delayTimer;
	int _howManyWormDmged;
	int _turnCount;
	
public:
	HRESULT init();
	void release();
	void update();
	void render();
	void draw();
	void drawCRH();
	void drawGauge();
	void drawArrow();
	void crhCtrl();
	void endgame();
	void playerStateChk();

	int gameOverChk();
	void cameraCtrl();
	void boomDmg(tagWeapon w);
	void fireDmg(tagWeapon w);
	void turnManage();
	void damagePhase();
	void playWormDamagedSound();
	void playNoWormDamaged();
	void playWormDyingSound();
	Player* getPlayerInTurn() { return _vPlayer[_playerTurnNum]; }
	int getTurnPhase() { return _turnphase; }
	vector<Player*> getPlayerVector() { return _vPlayer; }
	bool getIsGameOver() { return _isGameOver; }
	//
	void setMapAdressLink(Map* map) { _map = map; }
	void setUIAdressLink(UI* ui) { _ui = ui; }
	void setWMAddressLing(WeaponManager* wm) { _wm = wm; }
	PlayerManager();
	~PlayerManager();
};