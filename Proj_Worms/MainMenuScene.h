#pragma once
#include "gameNode.h"
class MainMenuScene : public gameNode
{
private:
	RECT battleSceneRC;
	RECT settingSceneRC;
public:
	HRESULT init();
	void release();
	void update();
	void render();
	MainMenuScene();
	~MainMenuScene();
};

