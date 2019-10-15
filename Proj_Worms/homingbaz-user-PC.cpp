#include "stdafx.h"
#include "homingbaz.h"
#include "UI.h"
#include "Map.h"
#include "PlayerManager.h"

homingbaz::homingbaz()
{
}


homingbaz::~homingbaz()
{
}

HRESULT homingbaz::init(float power, float angle, POINT stPoint, POINT mousePoint, Map* map, UI* ui, PlayerManager* pm)
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
	_img = IMAGEMANAGER->findImage("WP_homing");
	_markPoint = _ui->getMarkPoint();
	_angleUpdateTimer = TIMEMANAGER->getWorldTime() + 0.5;
	_isHoming = false;
	_homingSttimer = TIMEMANAGER->getWorldTime() + 0.5;
	_homingEndtimer = TIMEMANAGER->getWorldTime() + 10;
	return S_OK;
}


void homingbaz::release()
{

}
void homingbaz::update()
{
	homing();
	frameCtrl();
	move();
	isUnderwater();
}
void homingbaz::render()
{
	draw();
}
void homingbaz::draw()
{
	_img->frameRender(getMemDC(), _weapon.xPoint - _img->getFrameWidth() / 2 + _camera->x, _weapon.yPoint - _img->getFrameHeight() / 2 + _camera->y, _weapon.currentFrameX, _weapon.currentFrameY);
}

void homingbaz::move()
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
	if (!_isHoming)
	{
		_weapon.xSpeed += _ui->getWind();
		_weapon.ySpeed += 0.3;
	}
	

}
void homingbaz::frameCtrl()
{
	if (_isHoming)
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
	
	else 
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
}

void homingbaz::boom()
{
	SOUNDMANAGER->play("09_Explosion2", VOLUME);
	_ui->boomDmg(_weapon);
	_pm->boomDmg(_weapon);
	_map->eraseMap(PointMake(_weapon.xPoint, _weapon.yPoint), _weapon.radius);
	_ui->setShowMarkPoint(false);
	_weapon.del = true;
}

void homingbaz::homing()
{
	if (_homingSttimer - TIMEMANAGER->getWorldTime() < 0 && _isHoming != true)
	{
		if (_homingEndtimer - TIMEMANAGER->getWorldTime() > 0)
		{
			_weapon.xSpeed = 0;
			_weapon.ySpeed = 0;
		}
		_isHoming = true;
	}
	if (_homingEndtimer - TIMEMANAGER->getWorldTime() < 0 && _isHoming == true)
	{
		_isHoming = false;
	}
	if (!_isHoming) return;


	if (_angleUpdateTimer - TIMEMANAGER->getWorldTime() <= 0)
	{
		_angleUpdateTimer = TIMEMANAGER->getWorldTime() + 0.03;
		
		if (_markPoint.x < _weapon.xPoint)
		{
			if (abs(_weapon.xPoint - _markPoint.x)/ float(100) > 2)
			{
				_weapon.xSpeed -= 2;
			}
			else
			{
				_weapon.xSpeed -= abs(_weapon.xPoint - _markPoint.x) / float(100);
			}
		}
		else if (_markPoint.x > _weapon.xPoint)
		{
			if (abs(_weapon.xPoint - _markPoint.x) / float(100) > 2)
			{
				_weapon.xSpeed += 2;
			}
			else
			{
				_weapon.xSpeed += abs(_weapon.xPoint - _markPoint.x) / float(100);
			}
		}

		if (_markPoint.y < _weapon.yPoint)
		{
			if (abs(_weapon.yPoint - _markPoint.y) / float(100) > 2)
			{
				_weapon.ySpeed -= 2;
			}
			else
			{
				_weapon.ySpeed -= abs(_weapon.yPoint - _markPoint.y) / float(100);
			}
		}
		else if (_markPoint.y > _weapon.yPoint)
		{
			if (abs(_weapon.yPoint - _markPoint.y) / float(100) > 2)
			{
				_weapon.ySpeed += 2;
			}
			else
			{
				_weapon.ySpeed += abs(_weapon.yPoint - _markPoint.y) / float(100);
			}
		}
	}

}
void homingbaz::isUnderwater()
{
	if (_weapon.yPoint > _map->getWaterHeigt())
	{
		SOUNDMANAGER->play("14_Splash");
		_weapon.del = true;
	}
}