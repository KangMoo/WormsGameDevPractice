#include "stdafx.h"
#include "Weapon.h"
#include "UI.h"
#include "PlayerManager.h"
#include "Map.h"

Weapon::Weapon()
{
}


Weapon::~Weapon()
{

}

HRESULT Weapon::init(float power, float angle, POINT stPoint, POINT mousePoint)
{
	_mousePoint = mousePoint;
	_weapon.currentFrameX = 0;
	_weapon.currentFrameY = 0;
	_weapon.isObject = false;
	_weapon.xPoint = stPoint.x;
	_weapon.yPoint = stPoint.y;
	_weapon.xSpeed = cosf(angle)*power;
	_weapon.ySpeed = -sinf(angle)*power;
	_weapon.del = false;
	return S_OK;
}
HRESULT Weapon::init(float power, float angle, POINT stPoint, POINT mousePoint, Map* map, UI* ui, PlayerManager* pm)
{
	setMapAddressLink(map);
	setUIAddressLink(ui);
	setPMAddressLink(pm);

	_mousePoint = mousePoint;
	_weapon.currentFrameX = 0;
	_weapon.currentFrameY = 0;
	_weapon.isObject = false;
	_weapon.xPoint = stPoint.x;
	_weapon.yPoint = stPoint.y;
	_weapon.xSpeed = cosf(angle)*power;
	_weapon.ySpeed = -sinf(angle)*power;
	_weapon.del = false;
	_camera = _ui->getCameraPointer();

	return S_OK;
}
void Weapon::release()
{

}
void Weapon::update()
{
	frameCtrl();
	move();
	
}
void Weapon::render()
{
	draw();
}
void Weapon::draw()
{
	_img->frameRender(getMemDC(), _weapon.xPoint - _img->getFrameWidth() / 2, _weapon.yPoint - _img->getFrameHeight() / 2, _weapon.currentFrameX, _weapon.currentFrameY);
}
void Weapon::move()
{
	_weapon.xPoint += _weapon.xSpeed;
	_weapon.yPoint += _weapon.ySpeed;
	
	
	_weapon.xSpeed += _ui->getWind();
	_weapon.ySpeed += 0.1;
}
void Weapon::frameCtrl()
{
	int maxFrame = _weapon.weaponImg->getMaxFrameY();
	float angle;
	angle = getAngle(0, 0, _weapon.xSpeed, _weapon.ySpeed);
	angle = angle + PI / (maxFrame * 2);
	angle += PI / 2;
	if (angle >= PI2) angle -= PI2;

	_weapon.currentFrameY = int(angle / maxFrame);
}
bool Weapon::mapPixColli()
{
	if (GetPixel(_map->getMap()->getMemDC(), _weapon.xPoint, _weapon.yPoint) != RGB(255, 0, 255))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Weapon::endTurn()
{
	return;
}