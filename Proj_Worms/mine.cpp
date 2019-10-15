#include "stdafx.h"
#include "mine.h"
#include "UI.h"
#include "Map.h"
#include "PlayerManager.h"

mine::mine()
{
}


mine::~mine()
{
}

HRESULT mine::init(float power, float angle, POINT stPoint, POINT mousePoint, Map* map, UI* ui, PlayerManager* pm)
{
	setMapAddressLink(map);
	setUIAddressLink(ui);
	setPMAddressLink(pm);
	_playedSoundBeforeExplode = false;
	_mousePoint = mousePoint;
	_weapon.currentFrameX = 0;
	_weapon.currentFrameY = 0;
	_weapon.isObject = true;
	_weapon.xPoint = stPoint.x;
	_weapon.yPoint = stPoint.y;
	_weapon.xSpeed = cosf(angle)*power;
	_weapon.ySpeed = -sinf(angle)*power;
	_weapon.maxKnockBackPower = 5;
	_weapon.maxDmg = 10;
	_weapon.radius = 50;
	_weapon.del = false;
	_camera = ui->getCameraPointer();
	_img = IMAGEMANAGER->findImage("WP_mine");
	_timer = TIMEMANAGER->getWorldTime() + 5;
	_weaponXsize = WORMXSIZE - 6;
	_weaponYsize = WORMYSIZE - 16;
	_rc = RectMakeCenter(_weapon.xPoint, _weapon.yPoint, _weaponXsize, _weaponYsize);
	_keepMove = true;
	_active = false;
	_tictokTimer = 0;
	_startTimer = TIMEMANAGER->getWorldTime() + 5;
	return S_OK;
}
void mine::release()
{

}
void mine::update()
{
	frameCtrl();
	colliChk();
	move();
	isUnderwater();
	timerCtrl();
	if (_startTimer - TIMEMANAGER->getWorldTime() < 0)
	{
		activeCtrl();
	}
	//if (_timer - TIMEMANAGER->getWorldTime() <= 0) boom();
}
void mine::render()
{
	draw();
}
void mine::draw()
{
	_img->frameRender(getMemDC(), _weapon.xPoint - _img->getFrameWidth() / 2 + _camera->x, _weapon.yPoint - _img->getFrameHeight() / 2 + _camera->y, _weapon.currentFrameX, _weapon.currentFrameY);
}
void mine::frameCtrl()
{
	int maxFrame = _img->getMaxFrameY();
	float angle;
	angle = getAngle(0, 0, _weapon.xSpeed, _weapon.ySpeed);
	int yFrame = 24;
	while (!(PI - PI / maxFrame <= angle && angle <= PI + PI / maxFrame))
	{
		yFrame++;
		angle += PI / (maxFrame / 2);
		if (angle >= PI2) angle -= PI2;
		if (yFrame >= maxFrame) yFrame -= maxFrame;
	}
	_weapon.currentFrameY = yFrame;
}
void mine::move()
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
void mine::colliChk()
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
			_weapon.ySpeed = -_weapon.ySpeed * (float(2) / float(10));
			_weapon.xSpeed = _weapon.xSpeed * (float(8) / float(10));
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
void mine::boom()
{
	SOUNDMANAGER->play("10_Explosion3", VOLUME);
	_ui->boomDmg(_weapon);
	_pm->boomDmg(_weapon);
	_map->eraseMap(PointMake(_weapon.xPoint, _weapon.yPoint), _weapon.radius);
	_weapon.del = true;
}

void mine::timerCtrl()
{
	if (!_active)
	{
		_timer = TIMEMANAGER->getWorldTime() + 2;
		return;
	}

	if (_timer - TIMEMANAGER->getWorldTime() <= 0)
	{
		boom();
	}
}
void mine::isUnderwater()
{
	if (_weapon.yPoint > _map->getWaterHeigt())
	{
		SOUNDMANAGER->play("14_Splash");
		_weapon.del = true;
	}
}
void mine::activeCtrl()
{
	if (!_active)
	{
		for (auto i : _pm->getPlayerVector())
		{
			for (auto j : i->getWormVector())
			{
				if (getDistance(j->getWorm().xPoint, j->getWorm().yPoint, _weapon.xPoint, _weapon.yPoint) < 100)
				{
					SOUNDMANAGER->play("57_MineArm");
					_tictokTimer = TIMEMANAGER->getWorldTime() + 0.2;
					_active = true;
				}
			}
		}
	}
	else
	{
		if (_tictokTimer - TIMEMANAGER->getWorldTime() < 0)
		{
			_tictokTimer = TIMEMANAGER->getWorldTime() + 0.2;
			SOUNDMANAGER->play("56_MINETICK");
		}
	}
}