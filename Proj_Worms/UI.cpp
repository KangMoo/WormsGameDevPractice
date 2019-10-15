#include "stdafx.h"
#include "UI.h"
#include "Map.h"
#include "PlayerManager.h"

UI::UI()
{
}

UI::~UI()
{
}

HRESULT UI::init()
{
	_camera = PointMake(0, 0);
	_cameraFocus = PointMake(0, 0);
	_weaponSelMode = false;
	_wind = 0; _showMarkPoint = false;
	_frameTimer = TIMEMANAGER->getWorldTime() + 0.3;

	_tMark.currnetFrameY = 0;
	_tMark.markImg = IMAGEMANAGER->findImage("mark");
	_tMark.markPoint = _ptMouse;

	iconinit();
	return S_OK;
}
void UI::release()
{

}
void UI::update()
{
	keymanager();

	cameraCtrl();

	iconManage();

}
void UI::render()
{
	frameUpdate();
	draw();
	drawMark();
}
void UI::draw()
{
	drawLeftLife();
	_icon.Img->render(getMemDC(), _icon.point.x, _icon.point.y);
	if (_pm->getTurnPhase() == TURNPHASE_PLAYERTURN)
	{
		drawLeftTime();
		drawWind();
	}
}
void UI::drawMark()
{
	if (_showMarkPoint)
	{
		_tMark.markImg->frameRender(getMemDC(), _tMark.markPoint.x - _tMark.markImg->getFrameHeight() / 2 + _camera.x,
			_tMark.markPoint.y - _tMark.markImg->getFrameHeight() / 2 + _camera.y, 0, _tMark.currnetFrameY);
	}

}
void UI::cameraCtrl()
{
	if (_camera.x > _cameraFocus.x)
	{
		int distance = _camera.x - _cameraFocus.x;
		_camera.x -= distance / 10;
	}
	else if (_camera.x < _cameraFocus.x)
	{
		int distance = _camera.x - _cameraFocus.x;
		_camera.x -= distance / 10;
	}
	if (_camera.y > _cameraFocus.y)
	{
		int distance = _camera.y - _cameraFocus.y;
		_camera.y -= distance / 10;
	}
	else if (_camera.y < _cameraFocus.y)
	{
		int distance = _camera.y - _cameraFocus.y;
		_camera.y -= distance / 10;
	}

}

void UI::setCameraFocus(POINT p)
{
	POINT temp;
	temp.x = p.x;
	temp.y = p.y;



	//카메라 위치 재조정 (화면 밖으로 카메라가 넘어갈 시)
	if (temp.x < WINSIZEX / 2)
	{
		temp.x = WINSIZEX / 2;
	}
	else if (temp.x > _map->getMap()->getWidth() - WINSIZEX / 2)
	{
		temp.x = _map->getMap()->getWidth() - WINSIZEX / 2;
	}
	if (temp.y < WINSIZEY / 2)
	{
		temp.y = WINSIZEY / 2;
	}

	else if (temp.y > _map->getMap()->getWidth() - WINSIZEY / 2)
	{
		temp.y = _map->getMap()->getWidth() - WINSIZEY / 2;
	}


	_cameraFocus.x = WINSIZEX / 2 - temp.x;
	_cameraFocus.y = WINSIZEY / 2 - temp.y;
}

void UI::keymanager()
{

	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		if (_weaponSelMode)
		{
			_weaponSelMode = false;
		}
		else
		{
			_weaponSelMode = true;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (_weaponSelMode)
		{
			for (auto i : _icon.weaponicon)
			{
				if (PtInRect(&i.rc, _ptMouse))
				{
					_pm->getPlayerInTurn()->selectWeapon(i.type);
				}
			}
		}
		else
		{
			switch (_pm->getPlayerInTurn()->getSelectedWeapon())
			{
			case WEAPON_HIMMING_MISSILE:
			case WEAPON_GIRDER:
			case WEAPON_TELEPORT:
				if (_pm->getPlayerInTurn()->getWormVector()[_pm->getPlayerInTurn()->getWormTurnNumber()]->getCanShoot())
				{
					_showMarkPoint = true;
					_tMark.markPoint.x = _ptMouse.x - _camera.x;
					_tMark.markPoint.y = _ptMouse.y - _camera.y;
				}
				break;
			case WEAPON_AIRSTRIKE:
			case WEAPON_NAPALMSTRIKE:
				if (_pm->getPlayerInTurn()->getWormVector()[_pm->getPlayerInTurn()->getWormTurnNumber()]->getCanShoot())
				{
					_showMarkPoint = true;
					_tMark.markPoint.x = _ptMouse.x - _camera.x;
					_tMark.markPoint.y = _ptMouse.y - _camera.y;
				}
				break;
			}
		}
	}


	if (KEYMANAGER->isStayKeyDown(VK_CONTROL))
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			_cameraFocus.x += 10;
		}
		else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			_cameraFocus.x -= 10;
		}
		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			_cameraFocus.y += 10;
		}
		else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			_cameraFocus.y -= 10;
		}
	}
}

void UI::iconManage()
{
	int a = 1;


	//활성화상태면?
	if (_weaponSelMode)
	{
		if (_icon.point.x > WINSIZEX - _icon.Img->getWidth() - 10)
		{
			_icon.point.x -= 5;
			for (int i = 0; i < _icon.weaponicon.size(); i++)
			{
				_icon.weaponicon[i].rc.left -= 5;
				_icon.weaponicon[i].rc.right -= 5;
			}
		}

	}
	else
	{
		if (_icon.point.x < WINSIZEX)
		{
			_icon.point.x += 5;
			for (int i = 0; i < _icon.weaponicon.size(); i++)
			{
				_icon.weaponicon[i].rc.left += 5;
				_icon.weaponicon[i].rc.right += 5;
			}
		}
	}
}

void UI::iconinit()
{
	_icon.Img = IMAGEMANAGER->findImage("icon");
	_icon.point.x = WINSIZEX;
	_icon.point.y = WINSIZEY - _icon.Img->getHeight() - 100;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			tagWeaponIcon tmp;
			tmp.rc = RectMake(_icon.point.x + i * 32 + 5, _icon.point.y + j * 32 + 5, 32, 32);
			switch (i)
			{
			case 0:
				switch (j)
				{
				case 0:
					tmp.type = WEAPON_BAZOOKA;
					break;
				case 1:
					tmp.type = WEAPON_GRENADE;
					break;
				case 2:
					tmp.type = WEAPON_FIREPUNCH;
					break;
				case 3:
					tmp.type = WEAPON_AIRSTRIKE;
					break;
				case 4:
					tmp.type = WEAPON_DYNAMITE;
					break;
				case 5:
					tmp.type = WEAPON_ROPE;
					break;
				case 6:
					tmp.type = WEAPON_SKIPGO;
					break;
				}
				break;
			case 1:
				switch (j)
				{
				case 0:
					tmp.type = WEAPON_HIMMING_MISSILE;
					break;
				case 1:
					tmp.type = WEAPON_HOLY;
					break;
				case 2:
					tmp.type = WEAPON_END;
					break;
				case 3:
					tmp.type = WEAPON_NAPALMSTRIKE;
					break;
				case 4:
					tmp.type = WEAPON_MINE;
					break;
				case 5:
					tmp.type = WEAPON_TELEPORT;
					break;
				case 6:
					tmp.type = WEAPON_SURRENDER;
					break;
				}
				break;
			case 2:
				switch (j)
				{
				case 0:
					tmp.type = WEAPON_END;
					break;
				case 1:
					tmp.type = WEAPON_BANANA;
					break;
				case 2:
					tmp.type = WEAPON_END;
					break;
				case 3:
					tmp.type = WEAPON_END;
					break;
				case 4:
					tmp.type = WEAPON_BASEBALLBAT;
					break;
				case 5:
					tmp.type = WEAPON_GIRDER;
					break;
				case 6:
					tmp.type = WEAPON_END;
					break;
				}
				break;
			case 3:
				switch (j)
				{
				case 0:
					tmp.type = WEAPON_END;
					break;
				case 1:
					tmp.type = WEAPON_END;
					break;
				case 2:
					tmp.type = WEAPON_END;
					break;
				case 3:
					tmp.type = WEAPON_END;
					break;
				case 4:
					tmp.type = WEAPON_END;
					break;
				case 5:
					tmp.type = WEAPON_END;
					break;
				case 6:
					tmp.type = WEAPON_END;
					break;
				}
				break;
			}

			_icon.weaponicon.push_back(tmp);
		}
	}
}

void UI::frameUpdate()
{
	if (_frameTimer - TIMEMANAGER->getWorldTime() < 0)
	{
		_frameTimer = TIMEMANAGER->getWorldTime() + 0.03;

		//마크 이미지~
		if (_tMark.currnetFrameY < _tMark.markImg->getMaxFrameY())
		{
			_tMark.currnetFrameY++;
		}
		else
		{
			_tMark.currnetFrameY = 0;
		}
		//~마크 이미지

		//바람 이미지~
		if (IMAGEMANAGER->findImage("windlf")->getFrameY() < IMAGEMANAGER->findImage("windlf")->getMaxFrameY())
		{
			IMAGEMANAGER->findImage("windlf")->setFrameY(IMAGEMANAGER->findImage("windlf")->getFrameY() + 1);
		}
		else
		{
			IMAGEMANAGER->findImage("windlf")->setFrameY(0);
		}
		if (IMAGEMANAGER->findImage("windrf")->getFrameY() < IMAGEMANAGER->findImage("windrf")->getMaxFrameY())
		{
			IMAGEMANAGER->findImage("windrf")->setFrameY(IMAGEMANAGER->findImage("windrf")->getFrameY() + 1);
		}
		else
		{
			IMAGEMANAGER->findImage("windrf")->setFrameY(0);
		}

		//~바람 이미지
	}
}

void UI::boomDmg(tagWeapon w)
{

	if (w.radius > 80)
	{
		EFFECTMANAGER->play("circl100", w.xPoint, w.yPoint);
		EFFECTMANAGER->play("elips100", w.xPoint, w.yPoint);
		EFFECTMANAGER->play("firehit", w.xPoint, w.yPoint);
		EFFECTMANAGER->play("exfoom", w.xPoint, w.yPoint - 60);
	}
	else if (w.radius > 50)
	{
		EFFECTMANAGER->play("circle75", w.xPoint, w.yPoint);
		EFFECTMANAGER->play("elipse75", w.xPoint, w.yPoint);
		EFFECTMANAGER->play("firehit", w.xPoint, w.yPoint);
		EFFECTMANAGER->play("expoot", w.xPoint, w.yPoint - 60);
	}
	else if (w.radius > 25)
	{
		EFFECTMANAGER->play("circle50", w.xPoint, w.yPoint);
		EFFECTMANAGER->play("elipse50", w.xPoint, w.yPoint);
		EFFECTMANAGER->play("firehit", w.xPoint, w.yPoint);
		EFFECTMANAGER->play("expow", w.xPoint, w.yPoint - 60);
	}
	else
	{
		EFFECTMANAGER->play("circle25", w.xPoint, w.yPoint);
		EFFECTMANAGER->play("elipse25", w.xPoint, w.yPoint);
		EFFECTMANAGER->play("firehit", w.xPoint, w.yPoint);
		EFFECTMANAGER->play("expow", w.xPoint, w.yPoint - 60);
	}

	_map->eraseMap(PointMake(w.xPoint, w.yPoint), w.radius);
}

void UI::drawLeftTime()
{
	//틀 그려주기
	IMAGEMANAGER->render("frame3636", getMemDC(), 16, WINSIZEY - 15 - IMAGEMANAGER->findImage("frame3636")->getHeight());

	//남은시간
	float lefttime = _pm->getPlayerInTurn()->getTurnTimer() - TIMEMANAGER->getWorldTime();

	if (lefttime >= 10)
	{
		IMAGEMANAGER->frameRender("num24", getMemDC(), 30 - 15, WINSIZEY - 45, 0, int((lefttime + 1) / 10));
		IMAGEMANAGER->frameRender("num24", getMemDC(), 30, WINSIZEY - 45, 0, int((lefttime + 1)) % 10);
	}
	else
	{
		IMAGEMANAGER->frameRender("num24", getMemDC(), 30, WINSIZEY - 45, 0, int((lefttime + 1)));
	}


}

void UI::drawLeftLife()
{

	for (auto i : _pm->getPlayerVector())
	{
		for (auto j : i->getWormVector())
		{
			if (j->getWorm().state != WORMSTATE_DEAD)
			{
				image* numImg = i->getNumImg();


				IMAGEMANAGER->render("frame4020", getMemDC(), j->getWorm().xPoint + _camera.x - 20, j->getWorm().yPoint - 50 + _camera.y - 5);
				if (j->getWorm().hp >= 100)
				{
					numImg->frameRender(getMemDC(), j->getWorm().xPoint + 10 + _camera.x - 4, j->getWorm().yPoint - 50 + _camera.y, 0, j->getWorm().hp % 10);
					numImg->frameRender(getMemDC(), j->getWorm().xPoint + _camera.x - 4, j->getWorm().yPoint - 50 + _camera.y, 0, (j->getWorm().hp / 10) % 10);
					numImg->frameRender(getMemDC(), j->getWorm().xPoint - 10 + _camera.x - 4, j->getWorm().yPoint - 50 + _camera.y, 0, j->getWorm().hp / 100);
				}
				else if (j->getWorm().hp > 0)
				{
					numImg->frameRender(getMemDC(), j->getWorm().xPoint + 5 + _camera.x - 4, j->getWorm().yPoint - 50 + _camera.y, 0, j->getWorm().hp % 10);
					numImg->frameRender(getMemDC(), j->getWorm().xPoint - 5 + _camera.x - 4, j->getWorm().yPoint - 50 + _camera.y, 0, j->getWorm().hp / 10);
				}
				else
				{
					numImg->frameRender(getMemDC(), j->getWorm().xPoint + _camera.x - 4, j->getWorm().yPoint - 50 + _camera.y, 0, 0);
				}
			}
		}
	}
}

void UI::windCtrl()
{
	_wind = RND->getFromFloatTo(-0.1, 0.1);
}

void UI::drawWind()
{
	IMAGEMANAGER->render("windframe", getMemDC(), WINSIZEX - 230, WINSIZEY - 50);
	HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
	HPEN pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); // 펜 색을 넣음
	HPEN oldPen = (HPEN)SelectObject(getMemDC(), pen);

	if (_wind < 0)
	{
		IMAGEMANAGER->frameRender("windlf", getMemDC(), WINSIZEX - 230 + 4, WINSIZEY - 50 + 4);
		RectangleMake(getMemDC(), WINSIZEX - 230 + 4, WINSIZEY - 50 + 4, 96 - (96 * -(_wind * 10)), 13);
	}
	else if (_wind > 0)
	{
		IMAGEMANAGER->frameRender("windrf", getMemDC(), WINSIZEX - 230 + 4 + 96, WINSIZEY - 50 + 4);
		RectangleMake(getMemDC(), WINSIZEX - 230 + 4 + 96 + 96, WINSIZEY - 50 + 4, -96 - (96 * -(_wind * 10)), 13);
	}
	DeleteObject(brush);
	DeleteObject(oldBrush);
	DeleteObject(pen);
	DeleteObject(oldPen);
}