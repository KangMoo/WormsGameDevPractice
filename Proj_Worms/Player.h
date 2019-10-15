#pragma once
#include "gameNode.h"
#include "Worm.h"
class Map;
class UI;
class WeaponManager;

class Player : public gameNode
{
private:
	Map * _map;
	UI* _ui;
	image* _graveImg;
	image* _numImg;
	image* _arrowImg;
	WeaponManager* _wm;
	POINT* _camera;
	WEAPON _selectedWeapon;
	vector<Worm*> _vWorm;
	float actionAngle;
	bool _turn;
	int _wormTurnNumber;
	float _turnTimer;
	float _backflipTimer;
	float _gauge;
	int _teamNum;
public:

	HRESULT init();
	HRESULT init(int teamNum);
	void release();
	void update();
	void render();
	void draw();

	void selectWeapon(WEAPON w);
	void turnOn();
	void endTurn();
	void keyManager();

	void playWormAirsupport();
	void deleteDeadWormFromVector();
	//현재 차례 지렁이 포인터 좌표 반환
	POINT getWormPoint();
	//크로스헤어 포인터 좌표 반환
	POINT getCrhPoint();
	bool isThereAliveWorm();
	bool isPlayerTurnEnd();
	void turnManager();
	void wormStateChk();
	void boomDmg(tagWeapon w);
	void fireDmg(tagWeapon w);
	void cameraFocusCtrl();

	//게터 세터
	bool getTurn() { return _turn; }
	void setTurn(bool turn) { _turn = turn; }
	int getWormTurnNumber() { return _wormTurnNumber; }
	vector<Worm*> getWormVector() { return _vWorm; }
	int getvWormsize() { return _vWorm.size(); }
	float getTurnTimer() { return _turnTimer; }
	void setTurnTimer(float turnTimer) { _turnTimer = turnTimer; }
	float getGauge() { return _gauge; }
	void setGauge(float gauge) { _gauge = gauge; }
	WEAPON getSelectedWeapon() { return _selectedWeapon; }
	int getTeamNum() { return _teamNum; }
	image* getGraveImg() { return _graveImg; }
	image* getNumImg() { return _numImg; }
	image* getArrowImg() { return _arrowImg; }
	//
	void setMapAdressLink(Map* map) { _map = map; }
	void setUIAdressLink(UI* ui) { _ui = ui; }
	void setWMAddressLink(WeaponManager* wm) { _wm = wm; }
	Player();
	~Player();
};

