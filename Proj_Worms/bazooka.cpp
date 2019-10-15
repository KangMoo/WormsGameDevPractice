#include "stdafx.h"
#include "bazooka.h"
#include "UI.h"
#include "Map.h"
#include "PlayerManager.h"

bazooka::bazooka()
{
}


bazooka::~bazooka()
{
}

HRESULT bazooka::init(float power, float angle, POINT stPoint, POINT mousePoint, Map* map, UI* ui, PlayerManager* pm)
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
	_weapon.radius = 50;
	_weapon.del = false;
	_camera = ui->getCameraPointer();
	_img = IMAGEMANAGER->findImage("WP_baz");
	return S_OK;
}


void bazooka::release()
{

}
void bazooka::update()
{
	frameCtrl();
	move();
	isUnderwater();
}
void bazooka::render()
{
	draw();
}
void bazooka::draw()
{
	_img->frameRender(getMemDC(), _weapon.xPoint - _img->getFrameWidth() / 2 + _camera->x, _weapon.yPoint - _img->getFrameHeight() / 2 + _camera->y, _weapon.currentFrameX, _weapon.currentFrameY);
}

void bazooka::move()
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
		}
	}
	//맵 충돌 시!
	if (iscolli)
	{
		boom();
	}

	_weapon.xSpeed += _ui->getWind();
	_weapon.ySpeed += 0.3;


}
void bazooka::frameCtrl()
{
	int maxFrame = _img->getMaxFrameY();
	float angle;
	angle = getAngle(0, 0, _weapon.xSpeed,_weapon.ySpeed);
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

void bazooka::boom()
{
	SOUNDMANAGER->play("09_Explosion2", VOLUME);
	_ui->boomDmg(_weapon);
	_pm->boomDmg(_weapon);
	_map->eraseMap(PointMake(_weapon.xPoint, _weapon.yPoint), _weapon.radius);
	//_map->getMap()->eraseEllipse(_map->getMap()->getMemDC(), PointMake(_weapon.xPoint, _weapon.yPoint), _weapon.radius, _weapon.radius);
	_weapon.del = true;
}
void bazooka::isUnderwater()
{
	if (_weapon.yPoint > _map->getWaterHeigt())
	{
		SOUNDMANAGER->play("14_Splash");
		_weapon.del = true;
	}
}