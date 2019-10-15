#include "stdafx.h"
#include "airstrike.h"
#include "UI.h"
#include "Map.h"
#include "PlayerManager.h"

airstrike::airstrike()
{
}


airstrike::~airstrike()
{
}


HRESULT airstrike::init(float power, float angle, POINT stPoint, POINT mousePoint, Map* map, UI* ui, PlayerManager* pm)
{
	_playedSoundBeforeExplode = false;
	setMapAddressLink(map);
	setUIAddressLink(ui);
	setPMAddressLink(pm);
	_plane.movingRight = false;
	_mousePoint = mousePoint;
	_weapon.currentFrameX = 0;
	_weapon.currentFrameY = 0;
	_plane.currentFrameX = 0;
	_plane.currentFrameY = 0;
	_weapon.isObject = false;
	_weapon.xPoint = ui->getMarkPoint().x;
	_weapon.yPoint = ui->getMarkPoint().y - 150;
	if (_plane.movingRight)
	{
		_plane.xPoint = ui->getMarkPoint().x + 300;
	}
	else
	{
		_plane.xPoint = ui->getMarkPoint().x + 300;
	}
	_plane.yPoint = 550;
	_plane.fire = false;
	_weapon.xSpeed = cosf(angle)*power;
	_weapon.ySpeed = -sinf(angle)*power;
	_weapon.maxKnockBackPower = 5;
	_weapon.maxDmg = 10;
	_weapon.radius = 50;
	_weapon.del = false;
	_camera = ui->getCameraPointer();
	_plane.img = IMAGEMANAGER->findImage("plane");
	_img = IMAGEMANAGER->findImage("plane");


	return S_OK;
}


void airstrike::release()
{

}
void airstrike::update()
{
	frameCtrl();
	planeMoveCtrl();
	planeFireCtrl();
	for (auto i : _vmisl)
	{
		i->update();
	}

	//미사일 delete
	for (int i = _vmisl.size() - 1; i >= 0; i--)
	{
		if (_vmisl[i]->gettagWeapon().del)
		{
			removeMisl(i);
			break;
		}
	}

	//weapon delete조건 처리
	if (_vmisl.size() == 0 && _plane.fire)
	{
		_weapon.del = true;
	}
}
void airstrike::render()
{
	for (auto i : _vmisl)
	{
		i->render();
	}

	draw();
}
void airstrike::draw()
{
	_plane.img->frameRender(getMemDC(), _plane.xPoint - _plane.img->getFrameWidth() / 2 + _camera->x, _plane.yPoint - _plane.img->getFrameHeight() / 2 + _camera->y, _plane.currentFrameX, _plane.currentFrameY);
}

void airstrike::move()
{

}
void airstrike::frameCtrl()
{
	if (_plane.movingRight)
	{
		_plane.currentFrameX = 1;
	}
	else
	{
		_plane.currentFrameX = 0;
	}
}

void airstrike::planeMoveCtrl()
{
	if (_plane.movingRight)
	{
		_plane.xPoint += 10;
	}
	else
	{
		_plane.xPoint -= 10;
	}
}
void airstrike::planeFireCtrl()
{
	if (_plane.fire) return;
	if (abs(_plane.xPoint - _ui->getMarkPoint().x) < 175)
	{
		_plane.fire = true;
		if (_plane.movingRight)
		{
			for (int i = 0; i < 5; i++)
			{
				airmisl* tmp = new airmisl;
				tmp->init(5, 0, PointMake(_plane.xPoint + (i - 2) * 30, _plane.yPoint), _mousePoint, _map, _ui, _pm);
				_vmisl.push_back(tmp);
			}
		}
		else
		{
			for (int i = 0; i < 5; i++)
			{
				airmisl* tmp = new airmisl;
				tmp->init(5, PI, PointMake(_plane.xPoint + (i-2) * 30,_plane.yPoint), _mousePoint, _map, _ui, _pm);
				_vmisl.push_back(tmp);
			}
		}
		_ui->setShowMarkPoint(false);
	}
}
void airstrike::removeMisl(int arrNum)
{
	SAFE_DELETE(_vmisl[arrNum]);
	_vmisl.erase(_vmisl.begin() + arrNum);
}

