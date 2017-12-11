#include "stdafx.h"
#include "Player.h"
#include "UI.h"
#include "Map.h"

Player::Player()
{
}


Player::~Player()
{
}


HRESULT Player::init()
{
	WORM temp;
	temp.currentFrameX = 0;
	temp.currentFrameY = 0;
	temp.hp = 100;
	temp.maxhp = 100;
	temp.Pointx = 100;
	temp.Pointy = 100;
	temp.rc = RectMakeCenter(temp.Pointx, temp.Pointy, 10, 20);

	_caemra = _ui->getCameraPointer();
	return S_OK;
}
void Player::release()
{
	frameUpdate();
	chkPixCol();


}
void Player::update()
{
	
}
void Player::render()
{

}
void Player::draw()
{

}

void Player::frameUpdate()
{

}

void Player::chkPixCol()
{

}

void Player::wormStateCtrl()
{
	for (auto i : _vWorms)
	{
		i.rc = RectMakeCenter(i.Pointx, i.Pointy, 10, 20);
	}
}