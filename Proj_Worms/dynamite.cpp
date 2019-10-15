#include "stdafx.h"
#include "dynamite.h"
#include "UI.h"
#include "Map.h"
#include "PlayerManager.h"

dynamite::dynamite()
{
}


dynamite::~dynamite()
{
}


HRESULT dynamite::init(float power, float angle, POINT stPoint, POINT mousePoint, Map* map, UI* ui, PlayerManager* pm)
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
	if (cosf(angle) > 0)
	{
		_weapon.xSpeed = 1;
	}
	else
	{
		_weapon.xSpeed = -1;
	}
	_weapon.ySpeed = -1;
	_weapon.maxKnockBackPower = 5;
	_weapon.maxDmg = 10;
	_weapon.radius = 100;
	_weapon.del = false;
	_camera = ui->getCameraPointer();
	_img = IMAGEMANAGER->findImage("WP_dyn");
	_timer = TIMEMANAGER->getWorldTime() + 5;
	_weaponXsize = WORMXSIZE - 6;
	_weaponYsize = WORMYSIZE - 16;
	_rc = RectMakeCenter(_weapon.xPoint, _weapon.yPoint, _weaponXsize, _weaponYsize);
	_keepMove = true;
	_soundtimer = TIMEMANAGER->getWorldTime();
	return S_OK;
}
void dynamite::release()
{

}
void dynamite::update()
{
	frameCtrl();
	colliChk();
	move();
	isUnderwater();
	if (_timer - TIMEMANAGER->getWorldTime() <= 0)
	{
		if (_img != IMAGEMANAGER->findImage("WP_dyn2"))
		{
			_img = IMAGEMANAGER->findImage("WP_dyn2");
			_weapon.currentFrameY = 0;
		}
		//boom();
	}

	//sound~
	if (_soundtimer - TIMEMANAGER->getWorldTime() < 0)
	{
		_soundtimer = TIMEMANAGER->getWorldTime()+0.1;
		SOUNDMANAGER->play("52_FUSE", VOLUME);
	}
	//~sound
}
void dynamite::render()
{
	draw();
}
void dynamite::draw()
{
	_img->frameRender(getMemDC(), _weapon.xPoint - _img->getFrameWidth() / 2 + _camera->x, _weapon.yPoint - _img->getFrameHeight() / 2 + _camera->y, _weapon.currentFrameX, _weapon.currentFrameY);
}
void dynamite::frameCtrl()
{
	if (_img == IMAGEMANAGER->findImage("WP_dyn"))
	{
		if (_weapon.currentFrameY < _img->getMaxFrameY())
		{
			_weapon.currentFrameY++;
		}
		else
		{
			_weapon.currentFrameY = 0;
		}
	}
	else if (_img == IMAGEMANAGER->findImage("WP_dyn2"))
	{
		if (_weapon.currentFrameY < _img->getMaxFrameY())
		{
			_weapon.currentFrameY++;
		}
		else
		{
			boom();
		}
	}
}
void dynamite::move()
{
	if (!_keepMove) return;

	//속력이 있다면
	if (_weapon.xSpeed != 0 || _weapon.ySpeed != 0)
	{

		//경로상에 픽셀 충돌 체크
		bool iscolli = false;
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
		}
	}

	//속도 조절
	_weapon.xSpeed += _ui->getWind();
	_weapon.ySpeed += 0.3;
	_rc = RectMakeCenter(_weapon.xPoint, _weapon.yPoint, _weaponXsize, _weaponYsize);
}
void dynamite::colliChk()
{
	if (!_keepMove) return;

	//rc.bottom & map 충돌
	if (GetPixel(_map->getMap()->getMemDC(), _weapon.xPoint, _rc.bottom) != RGB(255, 0, 255))
	{
		while (GetPixel(_map->getMap()->getMemDC(), _weapon.xPoint, _rc.bottom) != RGB(255, 0, 255))
		{
			_weapon.yPoint--;
			_rc = RectMakeCenter(_weapon.xPoint, _weapon.yPoint, _weaponXsize, _weaponYsize);
		}
		if (_weapon.ySpeed > 0)
		{
			_weapon.ySpeed = 0;
			_weapon.xSpeed = 0;
			if (abs(_weapon.ySpeed < 1) && abs(_weapon.xSpeed) < 1)
			{
				_keepMove = false;
			}
		}
	}

	else if (GetPixel(_map->getMap()->getMemDC(), _weapon.xPoint, _rc.top) != RGB(255, 0, 255))
	{
		while (GetPixel(_map->getMap()->getMemDC(), _weapon.xPoint, _rc.top) != RGB(255, 0, 255))
		{
			_weapon.yPoint++;
			_rc = RectMakeCenter(_weapon.xPoint, _weapon.yPoint, _weaponXsize, _weaponYsize);

		}
		if (_weapon.ySpeed < 0)
		{
			_weapon.ySpeed = -_weapon.ySpeed;
		}
	}
	//rc.left & map충돌
	if (GetPixel(_map->getMap()->getMemDC(), _rc.left, _weapon.yPoint) != RGB(255, 0, 255))
	{
		while (GetPixel(_map->getMap()->getMemDC(), _rc.left, _weapon.yPoint) != RGB(255, 0, 255))
		{
			_weapon.xPoint++;
			_rc = RectMakeCenter(_weapon.xPoint, _weapon.yPoint, _weaponXsize, _weaponYsize);

		}
		if (_weapon.xSpeed < 0)
		{
			_weapon.xSpeed += abs(_weapon.xSpeed) * (float(2) / float(10));
			_weapon.xSpeed = -_weapon.xSpeed;
		}
	}
	else if (GetPixel(_map->getMap()->getMemDC(), _rc.right, _weapon.yPoint) != RGB(255, 0, 255))
	{
		while (GetPixel(_map->getMap()->getMemDC(), _rc.right, _weapon.yPoint) != RGB(255, 0, 255))
		{
			_weapon.xPoint--;
			_rc = RectMakeCenter(_weapon.xPoint, _weapon.yPoint, _weaponXsize, _weaponYsize);

		}
		if (_weapon.xSpeed > 0)
		{
			_weapon.xSpeed -= abs(_weapon.xSpeed) * (float(2) / float(10));
			_weapon.xSpeed = -_weapon.xSpeed;
		}
	}
}
void dynamite::boom()
{
	SOUNDMANAGER->play("08_Explosion1", VOLUME);
	SOUNDMANAGER->stop("52_FUSE");
	_ui->boomDmg(_weapon);
	_pm->boomDmg(_weapon);
	_map->eraseMap(PointMake(_weapon.xPoint, _weapon.yPoint), _weapon.radius);
	_weapon.del = true;
}

void dynamite::timerCtrl()
{
	if (_timer - TIMEMANAGER->getWorldTime() <= 0)
	{
		boom();
	}
}

void dynamite::isUnderwater()
{
	if (_weapon.yPoint > _map->getWaterHeigt())
	{
		SOUNDMANAGER->play("14_Splash");
		_weapon.del = true;
	}
}