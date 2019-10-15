#pragma once
#include "gameNode.h"
#include "Weapon.h"
#include "airstrike.h"
#include "banana.h"
#include "banana2.h"
#include "bat.h"
#include "bazooka.h"
#include "cluster.h"
#include "dynamite.h"
#include "fire.h"
#include "firepunch.h"
#include "firestrike.h"
#include "girder.h"
#include "grenade.h"
#include "holy.h"
#include "homingbaz.h"
#include "mine.h"
#include "napalm.h"
#include "pertrol.h"
#include "rope.h"
#include "shotgun.h"
#include "skipgo.h"
#include "surrender.h"
#include "teleport.h"

class UI;
class PlayerManager;
class Map;
class WeaponManager :public gameNode
{
private:
	UI * _ui;
	PlayerManager* _pm;
	Map* _map;
	POINT* _camera;
	vector<Weapon*> _vWeapon;
	WEAPON _weaponType;
	float _turnTimer;
	bool _turn;
public:
	HRESULT init();
	void release();
	void update();
	void render();
	void launchWeapon(WEAPON type, POINT sPoint, float power, float angle);
	void removeWeapon(int arrNum);
	void turnOn();
	bool isWeaponTurnEnd();
	void cameraFocusCtrl();
	void wormExplode(POINT p);

	//게터세터
	float getTurnTimer() { return _turnTimer; }
	void setTurnTimer(float turnTimer) { _turnTimer = turnTimer; }

	void setUIAddressLink(UI* ui) { _ui = ui; }
	void setPMAddressLink(PlayerManager* pm) { _pm = pm; }
	void setMapAddressLink(Map* map) { _map = map; }
	WeaponManager();
	~WeaponManager();
};

