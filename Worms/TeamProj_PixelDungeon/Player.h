#pragma once
#include "gameNode.h"
class Map;
class UI;

class Player : public gameNode
{
private:
	Map* _map;
	UI* _ui;
	POINT* _caemra;
	vector<WORM> _vWorms;
public:

	HRESULT init();
	void release();
	void update();
	void render();
	void draw();

	void frameUpdate();
	void chkPixCol();
	void wormStateCtrl();

	void setMapAdressLink(Map* map) { _map = map; }
	void setUIAdressLink(UI* ui) { _ui = ui; }

	Player();
	~Player();
};

