#include "stdafx.h"
#include "mainGame.h"

mainGame::mainGame()
{
}


mainGame::~mainGame()
{

}


HRESULT mainGame::init(void)
{
	gameNode::init(true);

	SCENEMANAGER->addScene("������", new BattleScene);
	SCENEMANAGER->addScene("������", new SettingScene);
	SCENEMANAGER->addScene("�޴���", new MainMenuScene);
	SCENEMANAGER->changeScene("�޴���");
	return S_OK;
}

void mainGame::release(void)
{

}


void mainGame::update(void)	
{
	gameNode::update();

	SCENEMANAGER->update();

}


void mainGame::render(void)	
{
	//��� ��ȭ�� �� �� �ʿ�
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==============================================================

	SCENEMANAGER->render();
	
	
	//========================================================================
	//����ۿ� �ִ°� HDC�� �׷��ִ� ����
	this->getBackBuffer()->render(getHDC(), 0, 0);

}