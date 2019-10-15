#pragma once
#include "gameNode.h"
class UI;
struct tagWaterwaveInfo
{
	int yFrame;
	int xPoint;
};
class Map : public gameNode
{
private:
	image* _map;
	image* _map2;
	image* _map3;
	image* _bg;
	UI* _ui;
	int _waterHeight;
	POINT* _camera;
	image* _blue;
	vector<tagWaterwaveInfo> _vWaterInfo;
	vector<tagGrave> _vGrave;
	float _frametimer;
public:
	HRESULT init();
	void release();
	void update();
	void render();
	void draw();
	void drawGrave();
	void graveCtrl();
	void addgrave(POINT p, image* graveImg);
	void waterHeightInit();
	void frameUpdate();
	image* getMap() { return _map; }
	void eraseMap(POINT p, float size);
	int getWaterHeigt() { return _waterHeight; }
	void setWaterHeight(int waterheight) { _waterHeight = _waterHeight; }
	void setUIAddressLink(UI* ui) { _ui = ui; }
	Map();
	~Map();
};

