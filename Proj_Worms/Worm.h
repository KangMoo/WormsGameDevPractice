#pragma once
#include "gameNode.h"
class Map;
class UI;
struct tagTelInfo {
	bool rewind;
	bool teleported;
};
class Worm : public gameNode
{
private:
	Map* _map;
	UI* _ui;
	WORM _worm;
	POINT* _camera;
	POINT _markPoint;
	image* _crh;
	bool _canShoot;
	WEAPON _selectedWeapon;
	tagTelInfo _telInfo;
	bool _wormExplode;
public:
	HRESULT init();
	HRESULT init(POINT point);
	void release();
	void update();
	void render();
	void draw();

	void playWormSlideSound();
	void playWormWalkSound();
	void playWormFireDmgSound();
	void frameUpdate();
	void chkPixCol();
	void wormMove();
	void wormStateCtrl();
	void angleCtrl();
	void boomDmg(tagWeapon w);
	void fireDmg(tagWeapon w);
	void changeImg(WORMSTATE state);
	WORM changeImg(WORM worm, WORMSTATE state);
	void teleport();
	void fireWeapon();
	void wormDead();
	//세터 게터
	WORM getWorm() { return _worm; }
	void setWorm(WORM worm) { _worm = worm; }
	bool getCanShoot() { return _canShoot; }
	void setCanShoot(bool canShoot) { _canShoot = canShoot; }
	WEAPON getSelWeapon() { return _selectedWeapon; }
	void setSelWeapon(WEAPON weapon) { _selectedWeapon = weapon; }
	bool getWormExplode() {return _wormExplode; }
	void setWormExplode(bool explode) { _wormExplode = explode; }
	
	//주소 연결
	void setMapAdressLink(Map* map) { _map = map; }
	void setUIAdressLink(UI* ui) { _ui = ui; }

	Worm();
	~Worm();
};

