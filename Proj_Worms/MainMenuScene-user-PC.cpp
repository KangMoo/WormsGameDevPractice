#include "stdafx.h"
#include "MainMenuScene.h"


MainMenuScene::MainMenuScene()
{
}


MainMenuScene::~MainMenuScene()
{

}

HRESULT MainMenuScene::init()
{
	battleSceneRC = RectMakeCenter(100,100,50,50);
	settingSceneRC = RectMakeCenter(300, 100, 50, 50);

	return S_OK;
}
void MainMenuScene::release()
{

}
void MainMenuScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&battleSceneRC, _ptMouse))
		{
			SCENEMANAGER->changeScene("ÀüÅõ¾À");
		}
		else if (PtInRect(&settingSceneRC, _ptMouse))
		{
			SCENEMANAGER->changeScene("¼³Á¤¾À");
		}
	}
}
void MainMenuScene::render()
{
	Rectangle(getMemDC(), battleSceneRC.left, battleSceneRC.top, battleSceneRC.right, battleSceneRC.bottom);
	Rectangle(getMemDC(), settingSceneRC.left, settingSceneRC.top, settingSceneRC.right, settingSceneRC.bottom);

}