#include "stdafx.h"
#include "teleport.h"
#include "UI.h"
#include "Map.h"
#include "PlayerManager.h"

teleport::teleport()
{
}


teleport::~teleport()
{
}

HRESULT teleport::init(float power, float angle, POINT stPoint, POINT mousePoint, Map* map, UI* ui, PlayerManager* pm)
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
	_weapon.maxKnockBackPower = 5;
	_weapon.maxDmg = 10;
	_weapon.radius = 50;
	_weapon.del = false;
	_camera = ui->getCameraPointer();
	_img = IMAGEMANAGER->findImage("WP_grn");
	_timer = TIMEMANAGER->getWorldTime() + 5;
	_weaponXsize = WORMXSIZE - 6;
	_weaponYsize = WORMYSIZE - 16;
	_rc = RectMakeCenter(_weapon.xPoint, _weapon.yPoint, _weaponXsize, _weaponYsize);
	_keepMove = true;
	return S_OK;
}
void teleport::release()
{

}
void teleport::update()
{
	frameCtrl();
	move();
}
void teleport::render()
{
	draw();
}
void teleport::draw()
{
	_img->frameRender(getMemDC(), _weapon.xPoint - _img->getFrameWidth() / 2 + _camera->x, _weapon.yPoint - _img->getFrameHeight() / 2 + _camera->y, _weapon.currentFrameX, _weapon.currentFrameY);
}
