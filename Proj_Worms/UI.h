#pragma once
#include "gameNode.h"
class Map;
class PlayerManager;

struct tagWeaponIcon
{
	RECT rc;
	WEAPON type;
};
struct tagIcon 
{
	image* Img;
	vector<tagWeaponIcon> weaponicon;
	POINT point;
};
struct tagWind
{
	image* windlImg;
	image* windrImg;
	int currnetFrameY;
};
struct tagMark
{
	POINT markPoint;
	image* markImg;
	int currnetFrameY;
};
struct tagTimer
{
	int num;

};
class UI : public gameNode
{
private:
	Map * _map;
	PlayerManager* _pm;
	POINT _camera;
	POINT _cameraFocus;
	bool _showMarkPoint;
	bool _weaponSelMode;
	float _wind;
	tagIcon _icon;
	tagMark _tMark;
	tagWind _tWind;
	bool _showTimer;
	float _frameTimer;

public:
	HRESULT init();
	void release();
	void update();
	void render();
	void draw();
	void drawMark();
	void drawLeftTime();
	void drawLeftLife();
	void drawWind();

	void frameUpdate();
	void keymanager();
	void cameraCtrl();
	void windCtrl();
	
	void setCameraFocus(POINT p);
	float getWind() { return _wind; }
	void iconManage();
	void iconinit();
	void boomDmg(tagWeapon w);

	bool getShowMarkPoint() { return _showMarkPoint; }
	void setShowMarkPoint(bool showMarkPoint) { _showMarkPoint = showMarkPoint; }
	POINT getMarkPoint() { return _tMark.markPoint; }
	void setMarkPoint(POINT markPoint) { _tMark.markPoint = markPoint; }
	bool getShowTimerBool() { return _showTimer; }
	void setShowTimerBool(bool showTimer) { _showTimer = showTimer; }

	void setMapAddressLink(Map* map) { _map = map; }
	void setPMAddressLink(PlayerManager* pm) { _pm = pm; }
	POINT getCamera() { return _camera; }
	POINT* getCameraPointer() { return &_camera; }

	UI();
	~UI();
};

