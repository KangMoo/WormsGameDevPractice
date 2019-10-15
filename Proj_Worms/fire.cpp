#include "stdafx.h"
#include "fire.h"
#include "UI.h"
#include "Map.h"
#include "PlayerManager.h"


fire::fire()
{
}


fire::~fire()
{
}


HRESULT fire::init(float power, float angle, POINT stPoint, POINT mousePoint, Map* map, UI* ui, PlayerManager* pm)
{
	setMapAddressLink(map);
	setUIAddressLink(ui);
	setPMAddressLink(pm);
	_playedSoundBeforeExplode = false;
	_mousePoint = mousePoint;
	_weapon.currentFrameX = 0;
	_weapon.currentFrameY = 0;
	_weapon.isObject = false;
	_weapon.xPoint = stPoint.x;
	_weapon.yPoint = stPoint.y;
	_weapon.xSpeed = 0;
	_weapon.ySpeed = 0;
	//_weapon.xSpeed = cosf(angle)*power;
	//_weapon.ySpeed = -sinf(angle)*power;
	_weapon.maxKnockBackPower = 3.5;
	_weapon.maxDmg = 10;
	_weapon.radius = 3;
	_weapon.del = false;
	_dmg = 10;
	_camera = ui->getCameraPointer();
	_img = IMAGEMANAGER->findImage("fire1");

	setMapAddressLink(map);
	setUIAddressLink(ui);
	setPMAddressLink(pm);

	return S_OK;
}


void fire::release()
{

}
void fire::update()
{
	imgCtrl();
	frameCtrl();
	move();
	isUnderwater();
	if (_dmg <= 0)
	{
		_weapon.del = true;
	}

	tagWeapon tmp = _weapon;
	tmp.yPoint -= 2;
	_pm->fireDmg(tmp);
}
void fire::render()
{
	draw();
}
void fire::draw()
{
	_img->frameRender(getMemDC(), _weapon.xPoint - _img->getFrameWidth() / 2 + _camera->x, _weapon.yPoint - _img->getFrameHeight() / 2 + _camera->y, _weapon.currentFrameX, _weapon.currentFrameY);
}

void fire::move()
{

	bool iscolli = false;
	if (_weapon.xSpeed != 0 || _weapon.ySpeed != 0)
	{
		//경로상에 픽셀 충돌 체크

		for (int i = 1; i < abs(_weapon.xSpeed); i++)
		{
			if (_weapon.xSpeed > 0)
			{
				if (GetPixel(_map->getMap()->getMemDC(), _weapon.xPoint + i, _weapon.yPoint + _weapon.ySpeed / i) != RGB(255, 0, 255))
				{
					if (i == 1)
					{
						_weapon.xPoint += i;
						_weapon.yPoint += _weapon.ySpeed / float(i);
					}
					else
					{
						_weapon.xPoint += i - 1;
						_weapon.yPoint += _weapon.ySpeed / float(i - 1);
					}
					iscolli = true;
					break;
				}
			}
			else if (_weapon.xSpeed < 0)
			{
				if (GetPixel(_map->getMap()->getMemDC(), _weapon.xPoint - i, _weapon.yPoint + _weapon.ySpeed / i) != RGB(255, 0, 255))
				{
					if (i == 1)
					{
						_weapon.xPoint -= i;
						_weapon.yPoint += _weapon.ySpeed / float(i);
					}
					else
					{
						_weapon.xPoint -= i - 1;
						_weapon.yPoint += _weapon.ySpeed / float(i - 1);
					}
					iscolli = true;
					break;
				}
			}
		}
		if (!iscolli)
		{
			for (int i = 1; i < abs(_weapon.ySpeed); i++)
			{
				if (_weapon.ySpeed > 0)
				{
					if (GetPixel(_map->getMap()->getMemDC(), _weapon.xPoint + _weapon.xSpeed / i, _weapon.yPoint + i) != RGB(255, 0, 255))
					{
						if (i == 1)
						{
							_weapon.xPoint += _weapon.xSpeed / float(i);
							_weapon.yPoint += i;
						}
						else
						{
							_weapon.xPoint += _weapon.xSpeed / float(i - 1);
							_weapon.yPoint += i - 1;
						}
						iscolli = true;
						break;
					}
				}
				else if (_weapon.ySpeed < 0)
				{
					if (GetPixel(_map->getMap()->getMemDC(), _weapon.xPoint + _weapon.xSpeed / i, _weapon.yPoint - i) != RGB(255, 0, 255))
					{
						if (i == 1)
						{
							_weapon.xPoint += _weapon.xSpeed / float(i);
							_weapon.yPoint -= i;
						}
						else
						{
							_weapon.xPoint += _weapon.xSpeed / float(i);
							_weapon.yPoint -= i - 1;
						}
						iscolli = true;
						break;
					}
				}
			}
		}
		//경로상에 픽셀충돌이 없을 시 그냥 이동
		if (!iscolli)
		{
			_weapon.xPoint += _weapon.xSpeed;
			_weapon.yPoint += _weapon.ySpeed;
			_dmg -= 0.01;
		}
	}

	//맵 충돌 시!
	if (iscolli)
	{
		_weapon.xSpeed = 0;
		_weapon.ySpeed = 0;
		if (RND->getInt(10) == 0)
		{
			_map->eraseMap(PointMake(_weapon.xPoint, _weapon.yPoint), 5);
			//_map->getMap()->eraseEllipse(_map->getMap()->getMemDC(), PointMake(_weapon.xPoint, _weapon.yPoint), 5, 5);
		}

		switch (RND->getInt(5))
		{
		case 0:
			break;
		case 1:
			_weapon.xPoint++;
			break;
		case 2:
			_weapon.xPoint--;
			break;
		case 3:
			_weapon.yPoint++;
			break;
		case 4:
			_weapon.yPoint--;
		}


	}
	else
	{
		if (GetPixel(_map->getMap()->getMemDC(), _weapon.xPoint, _weapon.yPoint + 1) == RGB(255, 0, 255) &&
			GetPixel(_map->getMap()->getMemDC(), _weapon.xPoint, _weapon.yPoint) == RGB(255, 0, 255))
		{
			_weapon.xSpeed += _ui->getWind();
			_weapon.ySpeed += 0.05;
		}
		else
		{
			_map->eraseMap(PointMake(_weapon.xPoint, _weapon.yPoint), 2);
			//_map->getMap()->eraseEllipse(_map->getMap()->getMemDC(), PointMake(_weapon.xPoint, _weapon.yPoint), 2, 2);
			_weapon.xSpeed = 0;
			_weapon.ySpeed = 0;
			_dmg -= 0.05;
			if (RND->getInt(3) == 0)
			{
				switch (RND->getInt(5))
				{
				case 0:
					break;
				case 1:
					_weapon.xPoint++;
					break;
				case 2:
					_weapon.xPoint--;
					break;
				case 3:
					_weapon.yPoint++;
					break;
				case 4:
					_weapon.yPoint--;
				}
			}
			
		}
	}

}
void fire::frameCtrl()
{
	if (int(TIMEMANAGER->getWorldTime() * 1000) % 2 != 0) return;
	if (_weapon.currentFrameY < _img->getMaxFrameY())
	{
		_weapon.currentFrameY++;
	}
	else
	{
		_weapon.currentFrameY = 0;
	}
}


void fire::imgCtrl()
{
	if (_dmg >= 10)
	{
		_img = IMAGEMANAGER->findImage("fire1");
	}
	else if (_dmg >= 8)
	{
		_img = IMAGEMANAGER->findImage("fire2");
	}
	else if (_dmg >= 6)
	{
		_img = IMAGEMANAGER->findImage("fire3");
	}
	else if (_dmg >= 4)
	{
		_img = IMAGEMANAGER->findImage("fire4");
	}
	else if (_dmg >= 2)
	{
		_img = IMAGEMANAGER->findImage("fire5");
	}
	else
	{
		_img = IMAGEMANAGER->findImage("fire6");
	}
}
void fire::isUnderwater()
{
	if (_weapon.yPoint > _map->getWaterHeigt())
	{
		SOUNDMANAGER->play("55_MINEDUD",VOLUME);
		_weapon.del = true;
	}
}