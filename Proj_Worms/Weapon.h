#pragma once
#include "gameNode.h"
class Map;
class UI;
class PlayerManager;
class Weapon : public gameNode
{
protected:
	Map * _map;
	UI* _ui;
	PlayerManager* _pm;
	POINT* _camera;
	image* _img;
	tagWeapon _weapon;
	POINT _mousePoint;
	bool _playedSoundBeforeExplode;
public:
	virtual HRESULT init(float power, float angle, POINT stPoint, POINT mousePoint);
	virtual HRESULT init(float power, float angle, POINT stPoint, POINT mousePoint, Map* map, UI* ui, PlayerManager* pm);
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void draw();
	
	virtual void frameCtrl();
	virtual void move();
	virtual bool mapPixColli();
	virtual void endTurn();
	//게터세터
	virtual tagWeapon gettagWeapon() { return _weapon; }

	tagWeapon getWeapon() { return _weapon; }
	image* getImg() { return _img; }

	//상호참조
	virtual void setMapAddressLink(Map* map) { _map = map; }
	virtual void setUIAddressLink(UI* ui) { _ui = ui; }
	virtual void setPMAddressLink(PlayerManager* pm) { _pm = pm; }
	Weapon();
	~Weapon();
};