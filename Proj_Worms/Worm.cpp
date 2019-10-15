#include "stdafx.h"
#include "Worm.h"
#include "UI.h"
#include "Map.h"

Worm::Worm()
{
}


Worm::~Worm()
{
}

HRESULT Worm::init()
{
	changeImg(WORMSTATE_IDLE);
	_worm.currentFrameX = 0;
	_worm.currentFrameY = 0;
	_worm.hp = 100;
	_worm.maxhp = 100;
	_worm.xPoint = 1200;
	_worm.yPoint = 50;
	_worm.xSpeed = 0;
	_worm.ySpeed = 0;
	_worm.rc = RectMakeCenter(_worm.xPoint, _worm.xPoint, WORMXSIZE, WORMYSIZE);
	_worm.frameUpdateTimer = 0;
	_worm.angle = 0;
	_worm.howmanyDmged = 0;
	_worm.getDamagedInThisTurn = false;
	_worm.wpholdtype = WEAPONHOLDTYPE_ANGLE;
	_canShoot = false;
	_camera = _ui->getCameraPointer();
	_wormExplode = false;
	return S_OK;
}
HRESULT Worm::init(POINT point)
{
	changeImg(WORMSTATE_IDLE);
	_worm.currentFrameX = 0;
	_worm.currentFrameY = 0;
	_worm.hp = 100;
	_worm.maxhp = 100;
	_worm.xPoint = point.x;
	_worm.yPoint = point.y;
	_worm.xSpeed = 0;
	_worm.ySpeed = 0;
	_worm.rc = RectMakeCenter(_worm.xPoint, _worm.xPoint, WORMXSIZE, WORMYSIZE);
	_worm.frameUpdateTimer = 0;
	_worm.angle = 0;
	_worm.howmanyDmged = 0;
	_worm.getDamagedInThisTurn = false;
	_worm.wpholdtype = WEAPONHOLDTYPE_ANGLE;
	_canShoot = false;
	_camera = _ui->getCameraPointer();
	return S_OK;
}
void Worm::release()
{

}
void Worm::update()
{
	wormStateCtrl();	//상태 컨트롤
	chkPixCol();		//픽셀 충돌 체크
	wormMove();			//움직임
	chkPixCol();		//픽셀 충돌 체크canShoot
	angleCtrl();		//각도 설정
	switch (_worm.state)
	{
	case WORMSTATE_IDLE:
	case WORMSTATE_FALLING:
	case WORMSTATE_SLIDING:
	case WORMSTATE_MOVING:
	case WORMSTATE_FLYING:
	case WORMSTATE_JUMPING:
	case WORMSTATE_BACKFLIP:
	case WORMSTATE_DYING:
	case WORMSTATE_DROWNING:
	case WORMSTATE_USINGWEAPON:
	case WORMSTATE_DEAD:

	case WORMSTATE_END:
	case WORMSTATE_WEAPONSTATE:
	{
		switch (_selectedWeapon)
		{
		case WEAPON_BAZOOKA:
			break;
		case WEAPON_HIMMING_MISSILE:
			break;
		case WEAPON_GRENADE:
			break;
		case WEAPON_CLUSTER:
			break;
		case WEAPON_PETROL:
			break;
		case WEAPON_BANANA:
			break;
		case WEAPON_HOLY:
			break;
		case WEAPON_DYNAMITE:
			break;
		case WEAPON_MINE:
			break;
		case WEAPON_FIREPUNCH:
			break;
		case WEAPON_BASEBALLBAT:
			break;
		case WEAPON_AIRSTRIKE:
			break;
		case WEAPON_NAPALMSTRIKE:
			break;
		case WEAPON_GIRDER:
			break;
		case WEAPON_ROPE:
			break;
		case WEAPON_TELEPORT:
			teleport();
			break;

		case WEAPON_SKIPGO:
			break;
		case WEAPON_SURRENDER:
			break;
		case WEAPON_END:
			break;
		}
	}
	}
}
void Worm::render()
{
	frameUpdate();
	draw();
}
void Worm::draw()
{
	if (_worm.state == WORMSTATE_DEAD)
	{

	}
	else
	{
		_worm.img->frameRender(getMemDC(), _worm.xPoint - _worm.img->getFrameWidth() / 2 + _camera->x, _worm.yPoint - _worm.img->getFrameHeight() / 2 + _camera->y, _worm.currentFrameX, _worm.currentFrameY);
	}

	/*switch (_worm.state)
	{
	case WORMSTATE_IDLE:
	{
		char str[64] = "WORMSTATE_IDLE";
		TextOut(getMemDC(), 100, 100, str, strlen(str));
		break;
	}
	case WORMSTATE_FALLING:
	{
		char str[64] = "WORMSTATE_FALLING";
		TextOut(getMemDC(), 100, 100, str, strlen(str));
		break;
	}
	case WORMSTATE_SLIDING:
	{
		char str[64] = "WORMSTATE_SLIDING";
		TextOut(getMemDC(), 100, 100, str, strlen(str));
		break;
	}
	case WORMSTATE_MOVING:
	{
		char str[64] = "WORMSTATE_MOVING";
		TextOut(getMemDC(), 100, 100, str, strlen(str));
		break;
	}
	case WORMSTATE_FLYING:
	{
		char str[64] = "WORMSTATE_FLYING";
		TextOut(getMemDC(), 100, 100, str, strlen(str));
		break;
	}
	case WORMSTATE_JUMPING:
	{
		char str[64] = "WORMSTATE_JUMPING";
		TextOut(getMemDC(), 100, 100, str, strlen(str));
		break;
	}
	case WORMSTATE_BACKFLIP:
	{
		char str[64] = "WORMSTATE_BACKFLIP";
		TextOut(getMemDC(), 100, 100, str, strlen(str));
		break;
	}
	case WORMSTATE_DYING:
	{
		char str[64] = "WORMSTATE_DYING";
		TextOut(getMemDC(), 100, 100, str, strlen(str));
		break;
	}
	case WORMSTATE_DROWNING:
	{
		char str[64] = "WORMSTATE_DROWNING";
		TextOut(getMemDC(), 100, 100, str, strlen(str));
		break;
	}
	case WORMSTATE_USINGWEAPON:
	{
		char str[64] = "WORMSTATE_USINGWEAPON";
		TextOut(getMemDC(), 100, 100, str, strlen(str));
		break;
	}
	case WORMSTATE_DEAD:
	{
		char str[64] = "WORMSTATE_IDLE";
		TextOut(getMemDC(), 100, 100, str, strlen(str));
		break;
	}
	case WORMSTATE_END:
	{
		char str[64] = "WORMSTATE_IDLE";
		TextOut(getMemDC(), 100, 100, str, strlen(str));
		break;
	}
	}*/
}

void Worm::frameUpdate()
{
	if (TIMEMANAGER->getWorldTime() - _worm.frameUpdateTimer > 0.03)
	{
		_worm.frameUpdateTimer = TIMEMANAGER->getWorldTime();
		//if (_worm.state == WORMSTATE_IDLE && _worm.canShoot)
		//{
		//	_worm.state == WORMSTATE_WEAPONSTATE;
		//	_worm.img = _worm.w_img1;
		//}
		switch (_worm.state)
		{
			//반복 아닌 프레임
		case WORMSTATE_BACKFLIP:
		case WORMSTATE_JUMPING:
		case WORMSTATE_USINGWEAPON:
		case WORMSTATE_FALLING:
		{
			if (_worm.currentFrameY < _worm.img->getMaxFrameY())
			{
				_worm.currentFrameY++;
			}
			else if (_worm.currentFrameY > _worm.img->getMaxFrameY())
			{
				_worm.currentFrameY = 0;
			}
			break;
		}
		case WORMSTATE_DYING:
		{
			if (_worm.currentFrameY < _worm.img->getMaxFrameY())
			{
				_worm.currentFrameY++;
			}
			else
			{
				wormDead();
				_worm.state = WORMSTATE_DEAD;
			}
			break;
		}
		case WORMSTATE_FLYING:
		{

			//각도에 따라 프레임 설정
			////
			int maxFrame = 32;
			float angle;
			angle = getAngle(0, 0, abs(_worm.xSpeed), _worm.ySpeed);
			int yFrame = 0;
			while (!(PI - PI / maxFrame <= angle && angle <= PI + PI / maxFrame))
			{
				yFrame++;
				angle += PI / (maxFrame / 2);
				if (angle >= PI2) angle -= PI2;
				if (yFrame >= maxFrame) yFrame -= maxFrame;
			}
			_worm.currentFrameY = yFrame;
			break;
		}
		case WORMSTATE_IDLE:
		{
			if (_worm.img == IMAGEMANAGER->findImage("WORMSTATE_IDLE") || _worm.img == IMAGEMANAGER->findImage("W_brth2"))
			{
				if (_worm.currentFrameY < _worm.img->getMaxFrameY())
				{
					_worm.currentFrameY++;
				}
				else
				{
					_worm.currentFrameY = 0;
					if (RND->getInt(5) == 0 && _worm.img == IMAGEMANAGER->findImage("WORMSTATE_IDLE"))
					{
						//string str;
						char str[64];
						wsprintf(str, "%s%d", "NI_", RND->getInt(12) + 1);
						_worm.img = IMAGEMANAGER->findImage(str);
					}
				}
			}
			else
			{
				if (_worm.currentFrameY < _worm.img->getMaxFrameY())
				{
					_worm.currentFrameY++;
				}
				else
				{

					if (_worm.hp > 30)
					{
						_worm.img = IMAGEMANAGER->findImage("WORMSTATE_IDLE");
					}
					else
					{
						_worm.img = IMAGEMANAGER->findImage("W_brth2");
					}
					_worm.currentFrameY = 0;
				}
			}

			break;
		}

		case WORMSTATE_WEAPONSTATE:
		{
			switch (_selectedWeapon)
			{
			case WEAPON_BAZOOKA:
			case WEAPON_HIMMING_MISSILE:
			case WEAPON_GRENADE:
			case WEAPON_CLUSTER:
			case WEAPON_PETROL:
			case WEAPON_BANANA:
			case WEAPON_HOLY:
			{
				if (_canShoot)
				{
					if (_worm.img == _worm.w_img1)
					{
						if (_worm.currentFrameY < _worm.img->getMaxFrameY())
						{
							_worm.currentFrameY++;
						}
						else
						{
							_worm.img = _worm.w_img2;
							//각도에 따라 프레임 설정
							int maxFrame = _worm.img->getMaxFrameY();
							float angle = _worm.angle;
							if (angle > PI / 2 && angle < PI + PI / 2) angle = -angle;
							int yFrame = maxFrame / 2 + 2;
							while (!(PI - PI / (maxFrame * 2) <= angle && angle <= PI + PI / (maxFrame * 2)))
							{
								yFrame++;
								angle += PI / (maxFrame);
								if (angle >= PI2) angle -= PI2;
								if (yFrame > maxFrame) yFrame = 0;
							}
							_worm.currentFrameY = maxFrame - yFrame;
						}
					}
					else if (_worm.img == _worm.w_img2)
					{
						//각도에 따라 프레임 설정
						int maxFrame = _worm.img->getMaxFrameY();
						float angle = _worm.angle;
						if (angle > PI / 2 && angle < PI + PI / 2) angle = -angle;
						int yFrame = maxFrame / 2 + 2;
						while (!(PI - PI / (maxFrame * 2) <= angle && angle <= PI + PI / (maxFrame * 2)))
						{
							yFrame++;
							angle += PI / (maxFrame);
							if (angle >= PI2) angle -= PI2;
							if (yFrame > maxFrame) yFrame = 0;
						}
						_worm.currentFrameY = maxFrame - yFrame;
					}
				}
				else
				{
					changeImg(WORMSTATE_IDLE);
				}
			}
			break;
			case WEAPON_DYNAMITE:
			case WEAPON_MINE:
				if (_worm.currentFrameY < _worm.img->getMaxFrameY())
				{
					_worm.currentFrameY++;
				}
				break;
			case WEAPON_FIREPUNCH:
				break;
			case WEAPON_BASEBALLBAT:
				break;
			case WEAPON_AIRSTRIKE:
			case WEAPON_NAPALMSTRIKE:
				if (_worm.currentFrameY < _worm.img->getMaxFrameY())
				{
					_worm.currentFrameY++;
				}
				break;
			case WEAPON_GIRDER:
				break;
			case WEAPON_ROPE:
				break;
			case WEAPON_TELEPORT:
			{
				if (_worm.img == _worm.w_img1)
				{
					if (_worm.currentFrameY < _worm.img->getMaxFrameY())
					{
						_worm.currentFrameY++;
					}
				}
				else if (_worm.img == _worm.w_img2)
				{
					if (!_telInfo.rewind)
					{
						if (_worm.currentFrameY < _worm.img->getMaxFrameY())
						{
							_worm.currentFrameY++;
						}
						else
						{
							_telInfo.rewind = true;
						}
					}
					else
					{
						if (_worm.currentFrameY > 0)
						{
							_worm.currentFrameY--;
						}
						else
						{
							changeImg(WORMSTATE_IDLE);
						}
					}
				}

				break;
			}
			case WEAPON_SKIPGO:
				break;
			case WEAPON_SURRENDER:
				break;
			case WEAPON_END:
				break;
			default:
				break;
			}

			//if (_canShoot)
			//{
			//	switch (_worm.wpholdtype)
			//	{
			//	case WEAPONHOLDTYPE_ANGLE:
			//	{
			//		if (_worm.img == _worm.w_img1)
			//		{
			//			if (_worm.currentFrameY < _worm.img->getMaxFrameY())
			//			{
			//				_worm.currentFrameY++;
			//			}
			//			else
			//			{
			//				_worm.img = _worm.w_img2;
			//				//각도에 따라 프레임 설정
			//				int maxFrame = _worm.img->getMaxFrameY();
			//				float angle = _worm.angle;
			//				if (angle > PI / 2 && angle < PI + PI / 2) angle = -angle;
			//				int yFrame = maxFrame / 2 + 2;
			//				while (!(PI - PI / (maxFrame * 2) <= angle && angle <= PI + PI / (maxFrame * 2)))
			//				{
			//					yFrame++;
			//					angle += PI / (maxFrame);
			//					if (angle >= PI2) angle -= PI2;
			//					if (yFrame > maxFrame) yFrame = 0;
			//				}
			//				_worm.currentFrameY = maxFrame - yFrame;
			//			}
			//		}
			//		else if (_worm.img == _worm.w_img2)
			//		{
			//			//각도에 따라 프레임 설정
			//			int maxFrame = _worm.img->getMaxFrameY();
			//			float angle = _worm.angle;
			//			if (angle > PI / 2 && angle < PI + PI / 2) angle = -angle;
			//			int yFrame = maxFrame / 2 + 2;
			//			while (!(PI - PI / (maxFrame * 2) <= angle && angle <= PI + PI / (maxFrame * 2)))
			//			{
			//				yFrame++;
			//				angle += PI / (maxFrame);
			//				if (angle >= PI2) angle -= PI2;
			//				if (yFrame > maxFrame) yFrame = 0;
			//			}
			//			_worm.currentFrameY = maxFrame - yFrame;
			//		}
			//		break;
			//	}
			//	case WEAPONHOLDTYPE_HOLD:
			//	{
			//		if (_worm.currentFrameY < _worm.img->getMaxFrameY())
			//		{
			//			_worm.currentFrameY++;
			//		}
			//		break;
			//	}
			//	case WEAPONHOLDTYPE_SPECIAL:
			//	{
			//		break;
			//	}
			//	}
			//}
			//else
			//{
			//	changeImg(WORMSTATE_IDLE);
			//}
			break;
		}

		//반복 프레임

		default:
			if (_worm.currentFrameY < _worm.img->getMaxFrameY())
			{
				_worm.currentFrameY++;
			}
			else
			{
				_worm.currentFrameY = 0;
			}
			break;
		}

	}
}
void Worm::chkPixCol()
{
	switch (_worm.state)
	{
	case WORMSTATE_FLYING:
	{
		//rc.bot & map충돌
		if (GetPixel(_map->getMap()->getMemDC(), _worm.xPoint, _worm.rc.bottom) != RGB(255, 0, 255))
		{
			while (GetPixel(_map->getMap()->getMemDC(), _worm.xPoint, _worm.rc.bottom) != RGB(255, 0, 255))
			{
				_worm.yPoint--;
				_worm.rc = RectMakeCenter(_worm.xPoint, _worm.yPoint, WORMXSIZE, WORMYSIZE);
			}
			if (_worm.ySpeed > 0)
			{
				_worm.ySpeed = 0;
				if (abs(_worm.xSpeed) > MAXXSLIDESPEED)
				{
					if (_worm.xSpeed > 0) _worm.xSpeed = MAXXSLIDESPEED;
					else if (_worm.xSpeed < 0) _worm.xSpeed = -MAXXSLIDESPEED;
				}
				if (abs(_worm.xSpeed) < 1)
				{
					changeImg(WORMSTATE_IDLE);
					_worm.ImgUpdate();
				}
				else
				{
					changeImg(WORMSTATE_SLIDING);
					playWormSlideSound();
					if (_worm.xSpeed > 0) _worm.xSpeed -= 0.02;
					else if (_worm.xSpeed < 0) _worm.xSpeed += 0.02;
					_worm.ImgUpdate();
				}
			}
		}

		else if (GetPixel(_map->getMap()->getMemDC(), _worm.xPoint, _worm.rc.top) != RGB(255, 0, 255))
		{
			while (GetPixel(_map->getMap()->getMemDC(), _worm.xPoint, _worm.rc.top) != RGB(255, 0, 255))
			{
				_worm.yPoint++;
				_worm.rc = RectMakeCenter(_worm.xPoint, _worm.yPoint, WORMXSIZE, WORMYSIZE);

			}
			if (_worm.ySpeed < 0)
			{
				_worm.ySpeed = -_worm.ySpeed;
			}
		}
		//rc.left & map충돌
		if (GetPixel(_map->getMap()->getMemDC(), _worm.rc.left, _worm.yPoint) != RGB(255, 0, 255))
		{
			while (GetPixel(_map->getMap()->getMemDC(), _worm.rc.left, _worm.yPoint) != RGB(255, 0, 255))
			{
				_worm.xPoint++;
				_worm.rc = RectMakeCenter(_worm.xPoint, _worm.yPoint, WORMXSIZE, WORMYSIZE);

			}
			if (_worm.xSpeed < 0)
			{
				_worm.xSpeed += abs(_worm.xSpeed) / 4;
				_worm.xSpeed = -_worm.xSpeed;
			}
		}
		else if (GetPixel(_map->getMap()->getMemDC(), _worm.rc.right, _worm.yPoint) != RGB(255, 0, 255))
		{
			while (GetPixel(_map->getMap()->getMemDC(), _worm.rc.right, _worm.yPoint) != RGB(255, 0, 255))
			{
				_worm.xPoint--;
				_worm.rc = RectMakeCenter(_worm.xPoint, _worm.yPoint, WORMXSIZE, WORMYSIZE);

			}
			if (_worm.xSpeed > 0)
			{
				_worm.xSpeed -= abs(_worm.xSpeed) / 4;
				_worm.xSpeed = -_worm.xSpeed;
			}
		}

		break;
	}
	case WORMSTATE_JUMPING:
	case WORMSTATE_BACKFLIP:
	{
		//rc.bot & map충돌
		if (GetPixel(_map->getMap()->getMemDC(), _worm.xPoint, _worm.rc.bottom) != RGB(255, 0, 255))
		{
			while (GetPixel(_map->getMap()->getMemDC(), _worm.xPoint, _worm.rc.bottom) != RGB(255, 0, 255))
			{
				_worm.yPoint--;
				_worm.rc = RectMakeCenter(_worm.xPoint, _worm.yPoint, WORMXSIZE, WORMYSIZE);


			}
			if (_worm.ySpeed > 0)
			{
				_worm.ySpeed = 0;
				_worm.xSpeed = 0;
				changeImg(WORMSTATE_IDLE);
				_worm.ImgUpdate();
			}
		}

		else if (GetPixel(_map->getMap()->getMemDC(), _worm.xPoint, _worm.rc.top) != RGB(255, 0, 255))
		{
			while (GetPixel(_map->getMap()->getMemDC(), _worm.xPoint, _worm.rc.top) != RGB(255, 0, 255))
			{
				_worm.yPoint++;
				_worm.rc = RectMakeCenter(_worm.xPoint, _worm.yPoint, WORMXSIZE, WORMYSIZE);

			}
			if (_worm.ySpeed < 0)
			{
				_worm.ySpeed = -_worm.ySpeed;
			}
		}
		//rc.left & map충돌
		if (GetPixel(_map->getMap()->getMemDC(), _worm.rc.left, _worm.yPoint) != RGB(255, 0, 255))
		{
			while (GetPixel(_map->getMap()->getMemDC(), _worm.rc.left, _worm.yPoint) != RGB(255, 0, 255))
			{
				_worm.xPoint++;
				_worm.rc = RectMakeCenter(_worm.xPoint, _worm.yPoint, WORMXSIZE, WORMYSIZE);

			}
			if (_worm.xSpeed < 0)
			{
				_worm.xSpeed = -_worm.xSpeed;
			}
		}
		else if (GetPixel(_map->getMap()->getMemDC(), _worm.rc.right, _worm.yPoint) != RGB(255, 0, 255))
		{
			while (GetPixel(_map->getMap()->getMemDC(), _worm.rc.right, _worm.yPoint) != RGB(255, 0, 255))
			{
				_worm.xPoint--;
				_worm.rc = RectMakeCenter(_worm.xPoint, _worm.yPoint, WORMXSIZE, WORMYSIZE);

			}
			if (_worm.xSpeed > 0)
			{
				_worm.xSpeed = -_worm.xSpeed;
			}
		}

		break;
	}
	case WORMSTATE_SLIDING:
	{
		//rc.bot & map충돌
		if (GetPixel(_map->getMap()->getMemDC(), _worm.xPoint, _worm.rc.bottom) != RGB(255, 0, 255))
		{
			while (GetPixel(_map->getMap()->getMemDC(), _worm.xPoint, _worm.rc.bottom) != RGB(255, 0, 255))
			{
				_worm.yPoint--;
				_worm.rc = RectMakeCenter(_worm.xPoint, _worm.yPoint, WORMXSIZE, WORMYSIZE);
			}
			if (_worm.ySpeed > 0)
			{
				_worm.ySpeed = 0;
				if (abs(_worm.xSpeed) < 0.3)
				{
					_worm.xSpeed = 0;
					changeImg(WORMSTATE_IDLE);
					_worm.ImgUpdate();
				}
				else
				{
					changeImg(WORMSTATE_SLIDING);
					_worm.ImgUpdate();
				}
			}
		}

		else if (GetPixel(_map->getMap()->getMemDC(), _worm.xPoint, _worm.rc.top) != RGB(255, 0, 255))
		{
			while (GetPixel(_map->getMap()->getMemDC(), _worm.xPoint, _worm.rc.top) != RGB(255, 0, 255))
			{
				_worm.yPoint++;
				_worm.rc = RectMakeCenter(_worm.xPoint, _worm.yPoint, WORMXSIZE, WORMYSIZE);

			}
			if (_worm.ySpeed < 0)
			{
				_worm.ySpeed = -_worm.ySpeed;
			}
		}
		//rc.left & map충돌
		if (GetPixel(_map->getMap()->getMemDC(), _worm.rc.left, _worm.yPoint) != RGB(255, 0, 255))
		{
			while (GetPixel(_map->getMap()->getMemDC(), _worm.rc.left, _worm.yPoint) != RGB(255, 0, 255))
			{
				_worm.xPoint++;
				_worm.rc = RectMakeCenter(_worm.xPoint, _worm.yPoint, WORMXSIZE, WORMYSIZE);

			}
			if (_worm.xSpeed < 0)
			{
				_worm.xSpeed += abs(_worm.xSpeed) / 2;
				_worm.xSpeed = -_worm.xSpeed;
			}
		}
		else if (GetPixel(_map->getMap()->getMemDC(), _worm.rc.right, _worm.yPoint) != RGB(255, 0, 255))
		{
			while (GetPixel(_map->getMap()->getMemDC(), _worm.rc.right, _worm.yPoint) != RGB(255, 0, 255))
			{
				_worm.xPoint--;
				_worm.rc = RectMakeCenter(_worm.xPoint, _worm.yPoint, WORMXSIZE, WORMYSIZE);

			}
			if (_worm.xSpeed > 0)
			{
				_worm.xSpeed -= abs(_worm.xSpeed) / 2;
				_worm.xSpeed = -_worm.xSpeed;
			}
		}

		break;
	}
	case WORMSTATE_MOVING:
	{
		//rc.bot & map충돌
		if (GetPixel(_map->getMap()->getMemDC(), _worm.xPoint, _worm.rc.bottom) != RGB(255, 0, 255))
		{
			while (GetPixel(_map->getMap()->getMemDC(), _worm.xPoint, _worm.rc.bottom) != RGB(255, 0, 255))
			{
				_worm.yPoint--;
				_worm.rc = RectMakeCenter(_worm.xPoint, _worm.yPoint, WORMXSIZE, WORMYSIZE);

			}
			_worm.ySpeed = 0;
		}

		else if (GetPixel(_map->getMap()->getMemDC(), _worm.xPoint, _worm.rc.top) != RGB(255, 0, 255))
		{
			while (GetPixel(_map->getMap()->getMemDC(), _worm.xPoint, _worm.rc.top) != RGB(255, 0, 255))
			{
				_worm.yPoint++;
				_worm.rc = RectMakeCenter(_worm.xPoint, _worm.yPoint, WORMXSIZE, WORMYSIZE);

			}
			if (_worm.ySpeed < 0)
			{
				_worm.ySpeed = -_worm.ySpeed;
			}
		}
		//rc.left & map충돌
		if (GetPixel(_map->getMap()->getMemDC(), _worm.xPoint - 1, _worm.yPoint) != RGB(255, 0, 255))
		{
			while (GetPixel(_map->getMap()->getMemDC(), _worm.xPoint - 1, _worm.yPoint) != RGB(255, 0, 255))
			{
				_worm.xPoint++;
				_worm.rc = RectMakeCenter(_worm.xPoint, _worm.yPoint, WORMXSIZE, WORMYSIZE);

			}
			if (_worm.xSpeed < 0)
			{
				_worm.xSpeed = 0;
			}
		}
		else if (GetPixel(_map->getMap()->getMemDC(), _worm.xPoint + 1, _worm.yPoint) != RGB(255, 0, 255))
		{
			while (GetPixel(_map->getMap()->getMemDC(), _worm.xPoint + 1, _worm.yPoint) != RGB(255, 0, 255))
			{
				_worm.xPoint--;
				_worm.rc = RectMakeCenter(_worm.xPoint, _worm.yPoint, WORMXSIZE, WORMYSIZE);

			}
			if (_worm.xSpeed > 0)
			{
				_worm.xSpeed = 0;
			}
		}

		break;
	}
	case WORMSTATE_DYING:
	case WORMSTATE_IDLE:
	case WORMSTATE_WEAPONSTATE:
	{
		//rc.bot & map충돌
		if (GetPixel(_map->getMap()->getMemDC(), _worm.xPoint, _worm.rc.bottom) != RGB(255, 0, 255))
		{
			while (GetPixel(_map->getMap()->getMemDC(), _worm.xPoint, _worm.rc.bottom) != RGB(255, 0, 255))
			{
				_worm.yPoint--;
				_worm.rc = RectMakeCenter(_worm.xPoint, _worm.yPoint, WORMXSIZE, WORMYSIZE);

			}
			_worm.ySpeed = 0;
		}

		else if (GetPixel(_map->getMap()->getMemDC(), _worm.xPoint, _worm.rc.top) != RGB(255, 0, 255))
		{
			while (GetPixel(_map->getMap()->getMemDC(), _worm.xPoint, _worm.rc.top) != RGB(255, 0, 255))
			{
				_worm.yPoint++;
				_worm.rc = RectMakeCenter(_worm.xPoint, _worm.yPoint, WORMXSIZE, WORMYSIZE);

			}
			if (_worm.ySpeed < 0)
			{
				_worm.ySpeed = -_worm.ySpeed;
			}
		}
		//rc.left & map충돌
		//rc.left & map충돌
		if (GetPixel(_map->getMap()->getMemDC(), _worm.xPoint - 1, _worm.yPoint) != RGB(255, 0, 255))
		{
			while (GetPixel(_map->getMap()->getMemDC(), _worm.xPoint - 1, _worm.yPoint) != RGB(255, 0, 255))
			{
				_worm.xPoint++;
				_worm.rc = RectMakeCenter(_worm.xPoint, _worm.yPoint, WORMXSIZE, WORMYSIZE);

			}
			if (_worm.xSpeed < 0)
			{
				_worm.xSpeed = 0;
			}
		}
		else if (GetPixel(_map->getMap()->getMemDC(), _worm.xPoint + 1, _worm.yPoint) != RGB(255, 0, 255))
		{
			while (GetPixel(_map->getMap()->getMemDC(), _worm.xPoint + 1, _worm.yPoint) != RGB(255, 0, 255))
			{
				_worm.xPoint--;
				_worm.rc = RectMakeCenter(_worm.xPoint, _worm.yPoint, WORMXSIZE, WORMYSIZE);

			}
			if (_worm.xSpeed > 0)
			{
				_worm.xSpeed = 0;
			}
		}

		break;
	}
	case WORMSTATE_DROWNING:
	{

		break;
	}
	}
	if (abs(_worm.xSpeed) < 0.5)
	{
		_worm.xSpeed = 0;
	}
}
void Worm::wormMove()
{
	_worm.rc = RectMakeCenter(_worm.xPoint, _worm.yPoint, WORMXSIZE, WORMYSIZE);
	if (_selectedWeapon == WEAPON_TELEPORT && _worm.state == WORMSTATE_WEAPONSTATE)
	{
		_worm.xSpeed = 0;
		_worm.ySpeed = 0;
		return;
	}
	//속력이 있다면
	if (_worm.xSpeed != 0 || _worm.ySpeed != 0)
	{

		//경로상에 픽셀 충돌 체크
		bool iscolli = false;
		for (int i = 1; i < abs(_worm.xSpeed); i++)
		{
			if (_worm.xSpeed > 0)
			{
				if (GetPixel(_map->getMap()->getMemDC(), _worm.xPoint + i, _worm.yPoint + _worm.ySpeed / i) != RGB(255, 0, 255))
				{
					if (i == 1)
					{
						_worm.xPoint += i;
						_worm.yPoint += _worm.ySpeed / float(i);
					}
					else
					{
						_worm.xPoint += i - 1;
						_worm.yPoint += _worm.ySpeed / float(i - 1);
					}
					iscolli = true;
					break;
				}
			}
			else if (_worm.xSpeed < 0)
			{
				if (GetPixel(_map->getMap()->getMemDC(), _worm.xPoint - i, _worm.yPoint + _worm.ySpeed / i) != RGB(255, 0, 255))
				{
					if (i == 1)
					{
						_worm.xPoint -= i;
						_worm.yPoint += _worm.ySpeed / float(i);
					}
					else
					{
						_worm.xPoint -= i - 1;
						_worm.yPoint += _worm.ySpeed / float(i - 1);
					}
					iscolli = true;
					break;
				}
			}
		}
		if (!iscolli)
		{
			for (int i = 1; i < abs(_worm.ySpeed); i++)
			{
				if (_worm.ySpeed > 0)
				{
					if (GetPixel(_map->getMap()->getMemDC(), _worm.xPoint + _worm.xSpeed / i, _worm.yPoint + i) != RGB(255, 0, 255))
					{
						if (i == 1)
						{
							_worm.xPoint += _worm.xSpeed / float(i);
							_worm.yPoint += i;
						}
						else
						{
							_worm.xPoint += _worm.xSpeed / float(i - 1);
							_worm.yPoint += i - 1;
						}
						iscolli = true;
						break;
					}
				}
				else if (_worm.ySpeed < 0)
				{
					if (GetPixel(_map->getMap()->getMemDC(), _worm.xPoint + _worm.xSpeed / i, _worm.yPoint - i) != RGB(255, 0, 255))
					{
						if (i == 1)
						{
							_worm.xPoint += _worm.xSpeed / float(i);
							_worm.yPoint -= i;
						}
						else
						{
							_worm.xPoint += _worm.xSpeed / float(i);
							_worm.yPoint -= i - 1;
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
			_worm.xPoint += _worm.xSpeed;
			_worm.yPoint += _worm.ySpeed;
		}

		//감속
		if (_worm.state == WORMSTATE_FLYING || _worm.state == WORMSTATE_JUMPING || _worm.state == WORMSTATE_BACKFLIP)
		{

		}
		else
		{
			if (_worm.xSpeed > 0)
			{
				_worm.xSpeed -= 0.05;
			}
			else if (_worm.xSpeed < 0)
			{
				_worm.xSpeed += 0.05;
			}
		}

		//감속
		if (_worm.ySpeed > 0)
		{
			_worm.ySpeed -= 0.05;
		}
		else if (_worm.ySpeed < 0)
		{
			_worm.ySpeed += 0.05;
		}
	}

	//속도 최대치 조절
	if (int(abs(_worm.xSpeed)) > MAXXSPEED)
	{
		if (_worm.xSpeed > 0) _worm.xSpeed = MAXXSPEED;
		else _worm.xSpeed = -MAXXSPEED;
	}
	if (int(abs(_worm.ySpeed)) > MAXYSPEED)
	{
		if (_worm.ySpeed > 0) _worm.ySpeed = MAXYSPEED;
		else _worm.ySpeed = -MAXYSPEED;
	}
	_worm.rc = RectMakeCenter(_worm.xPoint, _worm.yPoint, WORMXSIZE, WORMYSIZE);
}
void Worm::wormStateCtrl()
{
	//충돌 박스 업데이트
	_worm.rc = RectMakeCenter(_worm.xPoint, _worm.yPoint, WORMXSIZE, WORMYSIZE);
	//보는 방향 결정
	if (_worm.xSpeed > 0)
	{
		//예외처리
		if (_worm.state == WORMSTATE_JUMPING || _worm.state == WORMSTATE_BACKFLIP)
		{

		}
		else
		{
			//프레임 설정
			_worm.currentFrameX = 1;
		}

	}
	else if (_worm.xSpeed < 0)
	{
		//예외처리
		if (_worm.state == WORMSTATE_JUMPING || _worm.state == WORMSTATE_BACKFLIP)
		{

		}
		else
		{
			//프레임 설정
			_worm.currentFrameX = 0;
		}

	}

	//속도가 0값이라면 가만히 있는 상태로
	if (_worm.xSpeed == 0 && _worm.ySpeed == 0)
	{
	}

	//만약 발 아래가 허공이면
	if (GetPixel(_map->getMap()->getMemDC(), _worm.xPoint, _worm.rc.bottom) == RGB(255, 0, 255))
	{
		_worm.ySpeed += 0.5;
	}

	//물이라면?
	if (_worm.yPoint > _map->getWaterHeigt())
	{
		if (_worm.state != WORMSTATE_DEAD)
		{
			SOUNDMANAGER->play("14_Splash");
			_worm.state = WORMSTATE_DEAD;
			_worm.hp = 0;
			_canShoot = false;
			//if (_worm.img != IMAGEMANAGER->findImage("WORMSTATE_DROWNING"))
			//{
			//	changeImg(WORMSTATE_DROWNING);
			//	_worm.yPoint = _map->getWaterHeigt() + 30;
			//}

		//_worm.xSpeed = 0;
		//_worm.ySpeed = 1;
		}

	}

	//idle상태인데 아직 총을 쏠 수 있는 상태라면?
	if (_worm.state == WORMSTATE_IDLE && _canShoot)
	{
		//무기상태로 바꿈
		changeImg(WORMSTATE_WEAPONSTATE);
	}
	if (_worm.state == WORMSTATE_DROWNING || _worm.state == WORMSTATE_DEAD || _worm.state == WORMSTATE_DYING)
	{
		_canShoot = false;
	}
	if (_worm.state == WORMSTATE_WEAPONSTATE)
	{
		if (!_canShoot)
		{
			//예외
			if (_selectedWeapon == WEAPON_TELEPORT)
			{

			}
			else
			{
				changeImg(WORMSTATE_IDLE);
			}
		}

	}

	if (_worm.state == WORMSTATE_MOVING)
	{
		if (_worm.currentFrameY == 0 &&
			!SOUNDMANAGER->isPlaySound("41_walk-compress"))
		{
			playWormWalkSound();
		}
	}

	if (_worm.state == WORMSTATE_IDLE && _worm.img == IMAGEMANAGER->findImage("WORMSTATE_IDLE") && _worm.hp < 30)
	{
		_worm.img = IMAGEMANAGER->findImage("W_brth2");
		_worm.currentFrameY = 0;
	}
}

void Worm::angleCtrl()
{
	//바라보는 방향 : 좌
	if (_worm.currentFrameX == 0)
	{
		if (0 <= _worm.angle && _worm.angle < PI / 2)
		{
			_worm.angle = PI - _worm.angle;
		}
		else if (PI + PI / 2 < _worm.angle && _worm.angle < PI2)
		{
			_worm.angle = PI - _worm.angle;
		}
	}
	//바라보는 방향 : 우
	else
	{
		if (PI / 2 < _worm.angle && _worm.angle < PI + PI / 2)
		{
			_worm.angle = PI - _worm.angle;
		}
	}


	//범위 재조정
	if (_worm.angle >= PI2)
	{
		_worm.angle -= PI2;
	}
	if (_worm.angle < 0)
	{
		_worm.angle += PI2;
	}
}

void Worm::boomDmg(tagWeapon w)
{
	if (getDistance(_worm.xPoint, _worm.yPoint, w.xPoint, w.yPoint) < w.radius + 10)
	{
		_worm.getDamagedInThisTurn = true;
		_worm.howmanyDmged = w.maxDmg* (w.radius / (getDistance(_worm.xPoint, _worm.yPoint, w.xPoint, w.yPoint) + 1));
		_worm.hp -= _worm.howmanyDmged;
		_worm.xSpeed = cosf(getAngle(w.xPoint, w.yPoint, _worm.xPoint, _worm.yPoint))*w.maxKnockBackPower* (w.radius / (getDistance(_worm.xPoint, _worm.yPoint, w.xPoint, w.yPoint) + 1));
		_worm.ySpeed = -sinf(getAngle(w.xPoint, w.yPoint, _worm.xPoint, _worm.yPoint))*w.maxKnockBackPower* (w.radius / (getDistance(_worm.xPoint, _worm.yPoint, w.xPoint, w.yPoint) + 1));
		changeImg(WORMSTATE_FLYING);
		if (_canShoot) _canShoot = false;
		_worm.ImgUpdate();
	}
}
void Worm::fireDmg(tagWeapon w)
{
	if (getDistance(_worm.xPoint, _worm.yPoint, w.xPoint, w.yPoint) < w.radius + 10)
	{
		playWormFireDmgSound();
		_worm.getDamagedInThisTurn = true;
		_worm.howmanyDmged = 1;
		//_worm.howmanyDmged = w.maxDmg* (w.radius / (getDistance(_worm.xPoint, _worm.yPoint, w.xPoint, w.yPoint) + 1));
		_worm.hp -= _worm.howmanyDmged;
		_worm.xSpeed = cosf(getAngle(w.xPoint, w.yPoint, _worm.xPoint, _worm.yPoint))*w.maxKnockBackPower;
		_worm.ySpeed = -sinf(getAngle(w.xPoint, w.yPoint, _worm.xPoint, _worm.yPoint))*w.maxKnockBackPower;
		changeImg(WORMSTATE_SLIDING);
		if (_canShoot) _canShoot = false;
		_worm.ImgUpdate();
	}
}

void Worm::changeImg(WORMSTATE state)
{

	switch (state)
	{
	case WORMSTATE_IDLE:
	{

		switch (_worm.state)
		{
		case WORMSTATE_FLYING:
		case WORMSTATE_SLIDING:
		{
			_worm.img = IMAGEMANAGER->findImage("W_SlideToIdle");
			break;
		}
		default:
			if (_canShoot)
			{
				_worm.img = IMAGEMANAGER->findImage("WORMSTATE_IDLE");
			}
			if (_worm.hp < 30)
			{
				_worm.img = IMAGEMANAGER->findImage("WORMSTATE_IDLE");
			}
			else
			{
				_worm.img = IMAGEMANAGER->findImage("WORMSTATE_IDLE");
			}
			break;
		}
		break;
	}
	case WORMSTATE_WEAPONSTATE:

		if (_worm.img != _worm.w_img1 || _worm.img != _worm.w_img2)
		{
			_worm.img = _worm.w_img1;
		}
		else
		{
			if (_worm.wpholdtype == WEAPONHOLDTYPE_ANGLE)
			{
				_worm.img = _worm.w_img2;
			}
			else if (_worm.wpholdtype == WEAPONHOLDTYPE_HOLD)
			{
				_worm.img = _worm.w_img1;
			}
			else
			{

			}
		}

		break;
	case WORMSTATE_FALLING:
		_worm.img = IMAGEMANAGER->findImage("WORMSTATE_FALLING");
		break;
	case WORMSTATE_SLIDING:
		_worm.img = IMAGEMANAGER->findImage("WORMSTATE_SLIDING");
		break;
	case WORMSTATE_MOVING:
		_worm.img = IMAGEMANAGER->findImage("WORMSTATE_MOVING");
		break;
	case WORMSTATE_FLYING:
		_worm.img = IMAGEMANAGER->findImage("WORMSTATE_FLYING");
		break;
	case WORMSTATE_JUMPING:
		_worm.img = IMAGEMANAGER->findImage("WORMSTATE_JUMPING");
		break;
	case WORMSTATE_BACKFLIP:
		_worm.img = IMAGEMANAGER->findImage("WORMSTATE_BACKFLIP");
		break;
	case WORMSTATE_DYING:
		_worm.img = IMAGEMANAGER->findImage("WORMSTATE_DYING");
		break;
	case WORMSTATE_DROWNING:
		_worm.img = IMAGEMANAGER->findImage("WORMSTATE_DROWNING");
		break;
	case WORMSTATE_USINGWEAPON:
		_worm.img = IMAGEMANAGER->findImage("WORMSTATE_USINGWEAPON");
		break;
	case WORMSTATE_DEAD:
		_worm.img = IMAGEMANAGER->findImage("WORMSTATE_DEAD");
		break;
	case WORMSTATE_END:
		break;
	default:
		break;
	}
	_worm.state = state;
	_worm.ImgUpdate();
}

WORM Worm::changeImg(WORM worm, WORMSTATE state)
{
	worm.state = state;
	switch (worm.state)
	{
	case WORMSTATE_IDLE:
		if (worm.hp < 30)
		{
			worm.img = IMAGEMANAGER->findImage("WORMSTATE_IDLE");
		}
		else
		{
			worm.img = IMAGEMANAGER->findImage("WORMSTATE_IDLE");
		}
		break;
	case WORMSTATE_WEAPONSTATE:
	{
		worm.img = worm.w_img2;

	}
	break;
	case WORMSTATE_FALLING:
		worm.img = IMAGEMANAGER->findImage("WORMSTATE_FALLING");
		break;
	case WORMSTATE_SLIDING:
		worm.img = IMAGEMANAGER->findImage("WORMSTATE_SLIDING");
		break;
	case WORMSTATE_MOVING:
		worm.img = IMAGEMANAGER->findImage("WORMSTATE_MOVING");
		break;
	case WORMSTATE_FLYING:
		worm.img = IMAGEMANAGER->findImage("WORMSTATE_FLYING");
		break;
	case WORMSTATE_JUMPING:
		worm.img = IMAGEMANAGER->findImage("WORMSTATE_JUMPING");
		break;
	case WORMSTATE_BACKFLIP:
		worm.img = IMAGEMANAGER->findImage("WORMSTATE_BACKFLIP");
		break;
	case WORMSTATE_DYING:
		worm.img = IMAGEMANAGER->findImage("WORMSTATE_DYING");
		break;
	case WORMSTATE_DROWNING:
		worm.img = IMAGEMANAGER->findImage("WORMSTATE_DROWNING");
		break;
	case WORMSTATE_USINGWEAPON:
		worm.img = IMAGEMANAGER->findImage("WORMSTATE_USINGWEAPON");
		break;
	case WORMSTATE_DEAD:
		worm.img = IMAGEMANAGER->findImage("WORMSTATE_DEAD");
		break;
	case WORMSTATE_END:
		break;
	default:
		break;
	}
	worm.ImgUpdate();
	return worm;
}

void Worm::teleport()
{
	if (!_telInfo.teleported && _worm.currentFrameY == _worm.img->getMaxFrameY())
	{
		_telInfo.teleported = true;
		_worm.xPoint = _markPoint.x;
		_worm.yPoint = _markPoint.y;
		_ui->setShowMarkPoint(false);
	}
}

void Worm::fireWeapon()
{
	switch (_selectedWeapon)
	{
	case WEAPON_BAZOOKA:
		break;
	case WEAPON_HIMMING_MISSILE:
		break;
	case WEAPON_GRENADE:
		break;
	case WEAPON_CLUSTER:
		break;
	case WEAPON_PETROL:
		break;
	case WEAPON_BANANA:
		break;
	case WEAPON_HOLY:
		break;
	case WEAPON_DYNAMITE:
		break;
	case WEAPON_MINE:
		break;
	case WEAPON_FIREPUNCH:
		break;
	case WEAPON_BASEBALLBAT:
		break;
	case WEAPON_AIRSTRIKE:
		break;
	case WEAPON_NAPALMSTRIKE:
		break;
	case WEAPON_GIRDER:
		break;
	case WEAPON_ROPE:
		break;
	case WEAPON_TELEPORT:
	{
		_worm.img = _worm.w_img2;
		_markPoint = _ui->getMarkPoint();
		_telInfo.rewind = false;
		_telInfo.teleported = false;
		_worm.state = WORMSTATE_WEAPONSTATE;
		break;
	}
	case WEAPON_SKIPGO:
		break;
	case WEAPON_SURRENDER:
		break;
	case WEAPON_END:
		break;
	default:
		break;
	}
}
void Worm::wormDead()
{
	if (_worm.yPoint > _map->getWaterHeigt())
	{
		_wormExplode = false;
	}
	else
	{
		_wormExplode = true;
	}
}

void Worm::playWormSlideSound()
{
	switch (RND->getInt(3))
	{
	case 0:
		SOUNDMANAGER->play("33_OOFF1", VOLUME);
		break;
	case 1:
		SOUNDMANAGER->play("34_OOFF2", VOLUME);
		break;
	case 2:
		SOUNDMANAGER->play("35_OOFF3", VOLUME);
		break;
	}
}
void Worm::playWormWalkSound()
{
	SOUNDMANAGER->play("41_walk-compress", VOLUME);
}
void Worm::playWormFireDmgSound()
{
	if (!SOUNDMANAGER->isPlaySound("37_OW1") && !SOUNDMANAGER->isPlaySound("38_OW2") && !SOUNDMANAGER->isPlaySound("39_OW3"))
	{
		switch (RND->getInt(3))
		{
		case 0:
			SOUNDMANAGER->play("37_OW1", VOLUME);
			break;
		case 1:
			SOUNDMANAGER->play("38_OW2", VOLUME);
			break;
		case 2:
			SOUNDMANAGER->play("39_OW3", VOLUME);
			break;
		}
	}
}