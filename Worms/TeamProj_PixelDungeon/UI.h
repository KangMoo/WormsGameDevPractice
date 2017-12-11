#pragma once
#include "gameNode.h"
class Map;

class UI
{
private:
	Map* _map;
	POINT _camera;
public:
	HRESULT init();
	void release();
	void update();
	void render();

	void cameraCtrl();

	void getMapAddressLink(Map* map) { _map = map; }
	POINT getCamera() { return _camera; }
	POINT* getCameraPointer() { return &_camera; }

	UI();
	~UI();
};

