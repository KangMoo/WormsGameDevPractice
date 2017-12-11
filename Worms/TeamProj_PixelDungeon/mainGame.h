#pragma once
#include "gameNode.h"
#include "BattleScene.h"
#include "MainMenuScene.h"
#include "SettingScene.h"

class mainGame : public gameNode
{
private:

public:
	virtual HRESULT init(void);	
	virtual void release(void);	
	virtual void update(void);	
	virtual void render(void);	

	
	mainGame();
	~mainGame();
};

