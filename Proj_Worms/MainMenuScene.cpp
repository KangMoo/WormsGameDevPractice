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
	IMAGEMANAGER->addImage("title", "Img\\title.bmp", 800, 600, true, RGB(255, 0, 255));
	battleSceneRC = RectMakeCenter(WINSIZEX / 2, WINSIZEY - WINSIZEY/4, 250, 50);
	//settingSceneRC = RectMakeCenter();
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
		//else if (PtInRect(&settingSceneRC, _ptMouse))
		//{
		//	SCENEMANAGER->changeScene("¼³Á¤¾À");
		//}
	}
}
void MainMenuScene::render()
{
	IMAGEMANAGER->render("title", getMemDC(), 0, 0);
	//Rectangle(getMemDC(), battleSceneRC.left, battleSceneRC.top, battleSceneRC.right, battleSceneRC.bottom);
	//Rectangle(getMemDC(), settingSceneRC.left, settingSceneRC.top, settingSceneRC.right, settingSceneRC.bottom);

}