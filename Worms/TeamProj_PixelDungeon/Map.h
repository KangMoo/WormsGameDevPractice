#pragma once
#include "gameNode.h"
class UI;
class Map : public gameNode
{
private:
	image* _map;
	UI* _ui;
	POINT* _camera;


public:
	HRESULT init();
	void release();
	void update();
	void render();
	void draw();

	image* getMap() { return _map; }

	void setUIAddressLink(UI* ui) { _ui = ui; }
	Map();
	~Map();
};

