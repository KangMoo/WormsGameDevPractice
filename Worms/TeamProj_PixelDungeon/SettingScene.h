#pragma once
#include "gameNode.h"

class SettingScene : public gameNode
{
private:

public:
	HRESULT init();
	void release();
	void update();
	void render();

	SettingScene();
	~SettingScene();
};

