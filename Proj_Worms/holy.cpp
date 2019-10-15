#include "stdafx.h"
#include "holy.h"
#include "UI.h"
#include "Map.h"
#include "PlayerManager.h"

holy::holy()
{
}


holy::~holy()
{
}

HRESULT holy::init(float power, float angle, POINT stPoint, POINT mousePoint, Map* map, UI* ui, PlayerManager* pm)
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
	_weapon.xSpeed = cosf(angle)*power;
	_weapon.ySpeed = -sinf(angle)*power;
	_weapon.maxKnockBackPower = 5;
	_weapon.maxDmg = 10;
	_weapon.radius = 200;
	_weapon.del = false;
	_camera = ui->getCameraPointer();
	_img = IMAGEMANAGER->findImage("WP_holy");
	_timer = TIMEMANAGER->getWorldTime() + 5;
	_weaponXsize = WORMXSIZE - 6;
	_weaponYsize = WORMYSIZE - 16;
	_rc = RectMakeCenter(_weapon.xPoint, _weapon.yPoint, _weaponXsize, _weaponYsize);
	_keepMove = true;
	return S_OK;
}
void holy::release()
{

}
void holy::update()
{
	frameCtrl();
	colliChk();
	move();
	timerCtrl();
	isUnderwater();
	//if (_timer - TIMEMANAGER->getWorldTime() <= 0) boom();
}
void holy::render()
{
	draw();
}
void holy::draw()
{
	_img->frameRender(getMemDC(), _weapon.xPoint - _img->getFrameWidth() / 2 + _camera->x, _weapon.yPoint - _img->getFrameHeight() / 2 + _camera->y, _weapon.currentFrameX, _weapon.currentFrameY);
}
void holy::frameCtrl()
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
void holy::move()
{
	if (!_keepMove) return;

	//�ӷ��� �ִٸ�
	if (_weapon.xSpeed != 0 || _weapon.ySpeed != 0)
	{

		//��λ� �ȼ� �浹 üũ
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
		//��λ� �ȼ��浹�� ���� �� �׳� �̵�
		if (!iscolli)
		{
			_weapon.xPoint += _weapon.xSpeed;
			_weapon.yPoint += _weapon.ySpeed;
		}
	}

	//�ӵ� ����
	_weapon.xSpeed += _ui->getWind();
	_weapon.ySpeed += 0.3;
	_rc = RectMakeCenter(_weapon.xPoint, _weapon.yPoint, _weaponXsize, _weaponYsize);
}
void holy::colliChk()
{
	if (!_keepMove) return;

	//rc.bottom & map �浹
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
		SOUNDMANAGER->play("12_HOLYGRENADEIMP", VOLUME);
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
		SOUNDMANAGER->play("12_HOLYGRENADEIMP", VOLUME);
	}
	//rc.left & map�浹
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
		SOUNDMANAGER->play("12_HOLYGRENADEIMP", VOLUME);
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
		SOUNDMANAGER->play("12_HOLYGRENADEIMP", VOLUME);
	}
}
void holy::boom()
{
	SOUNDMANAGER->play("08_Explosion1", VOLUME);
	_ui->boomDmg(_weapon);
	_pm->boomDmg(_weapon);
	_map->eraseMap(PointMake(_weapon.xPoint, _weapon.yPoint), _weapon.radius);
	_weapon.del = true;
}

void holy::timerCtrl()
{
	if (_timer - TIMEMANAGER->getWorldTime() <= 0.5 && !_playedSoundBeforeExplode)
	{
		SOUNDMANAGER->play("11_HOLYGRENADE",1);
		_playedSoundBeforeExplode = true;
	}
	if (_timer - TIMEMANAGER->getWorldTime() <= 0)
	{
		if (!SOUNDMANAGER->isPlaySound("11_HOLYGRENADE"))
		{
			boom();
		}
	}
}

void holy::isUnderwater()
{
	if (_weapon.yPoint > _map->getWaterHeigt())
	{
		SOUNDMANAGER->play("14_Splash");
		_weapon.del = true;
	}
}