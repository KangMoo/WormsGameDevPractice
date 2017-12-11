#include "stdafx.h"
#include "UI.h"
#include "Map.h"

UI::UI()
{
}


UI::~UI()
{
}

HRESULT UI::init()
{
	_camera = PointMake(0, 0);
	return S_OK;
}
void UI::release()
{

}
void UI::update()
{
	cameraCtrl();

}
void UI::render()
{

}

void UI::cameraCtrl()
{
	POINT temp;
	temp.x = WINSIZEX / 2 - _camera.x;
	temp.y = WINSIZEY / 2 - _camera.y;


	if (KEYMANAGER->isStayKeyDown(VK_CONTROL))
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			temp.x -= 5;
		}
		else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			temp.x += 5;
		}
		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			temp.y -= 5;
		}
		else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			temp.y += 5;
		}
	}
	else
	{

	}


	//카메라 위치 재조정 (화면 밖으로 카메라가 넘어갈 시)
	//if (_camera.x < WINSIZEX / 2)
	//{
	//	_camera.x = WINSIZEX / 2;
	//}
	//else if (_camera.x > _map->getMap()->getWidth() - WINSIZEX / 2)
	//{
	//	_camera.x = _map->getMap()->getWidth() - WINSIZEX / 2;
	//}
	//if (_camera.y < WINSIZEY / 2)
	//{
	//	_camera.y = WINSIZEY / 2;
	//}
	//
	//else if (_camera.y > _map->getMap()->getWidth() - WINSIZEY / 2)
	//{
	//	_camera.y = _map->getMap()->getWidth() - WINSIZEY / 2;
	//}


	_camera.x = WINSIZEX / 2 - temp.x;
	_camera.y = WINSIZEY / 2 - temp.y;
}