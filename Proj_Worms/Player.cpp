#include "stdafx.h"
#include "Player.h"
#include "UI.h"
#include "Map.h"
#include "WeaponManager.h"


Player::Player()
{
}


Player::~Player()
{
}


HRESULT Player::init()
{
	//WORM temp;
	//temp.state = WORMSTATE_IDLE;
	//temp.img = IMAGEMANAGER->findImage("WORMSTATE_IDLE");
	//temp.currentFrameX = 0;
	//temp.currentFrameY = 0;
	//temp.hp = 100;
	//temp.maxhp = 100;
	//temp.xPoint = 1000;
	//temp.yPoint = 50;
	//temp.xSpeed = 0;
	//temp.ySpeed = 0;
	//temp.rc = RectMakeCenter(temp.xPoint, temp.xPoint, WORMXSIZE, WORMYSIZE);
	//temp.frameUpdateTimer = 0;
	//_vWorms.push_back(temp);

	//temp.state = WORMSTATE_IDLE;
	//temp.img = IMAGEMANAGER->findImage("WORMSTATE_IDLE");
	//temp.currentFrameX = 0;
	//temp.currentFrameY = 0;
	//temp.hp = 100;
	//temp.maxhp = 100;
	//temp.xPoint = 1200;
	//temp.yPoint = 50;
	//temp.xSpeed = 0;
	//temp.ySpeed = 0;
	//temp.rc = RectMakeCenter(temp.xPoint, temp.xPoint, WORMXSIZE, WORMYSIZE);
	//temp.frameUpdateTimer = 0;
	//_vWorms.push_back(temp);

	Worm* tmp = new Worm;
	for (int i = 0; i < 10; i++)
	{
		tmp = new Worm;
		tmp->setMapAdressLink(_map);
		tmp->setUIAdressLink(_ui);
		tmp->init(PointMake(RND->getFromIntTo(1000, 3400), 150));
		_vWorm.push_back(tmp);
	}



	_turn = false;
	_wormTurnNumber = 0;
	_camera = _ui->getCameraPointer();
	_backflipTimer = 0;
	_gauge = 0;
	return S_OK;
}
HRESULT Player::init(int teamNum)
{

	Worm* tmp = new Worm;
	//test~
	if (teamNum == 0)
	{
		tmp = new Worm;
		tmp->setMapAdressLink(_map);
		tmp->setUIAdressLink(_ui);
		tmp->init(PointMake(1600, 150));
		_vWorm.push_back(tmp);
		tmp = new Worm;
		tmp->setMapAdressLink(_map);
		tmp->setUIAdressLink(_ui);
		tmp->init(PointMake(1100, 150));
		_vWorm.push_back(tmp);
		//tmp = new Worm;
		//tmp->setMapAdressLink(_map);
		//tmp->setUIAdressLink(_ui);
		//tmp->init(PointMake(2800, 150));
		//_vWorm.push_back(tmp);

	}
	else if (teamNum == 1)
	{
		tmp = new Worm;
		tmp->setMapAdressLink(_map);
		tmp->setUIAdressLink(_ui);
		tmp->init(PointMake(1900, 150));
		_vWorm.push_back(tmp);
		tmp = new Worm;
		tmp->setMapAdressLink(_map);
		tmp->setUIAdressLink(_ui);
		tmp->init(PointMake(2800, 150));
		_vWorm.push_back(tmp);
		//tmp = new Worm;
		//tmp->setMapAdressLink(_map);
		//tmp->setUIAdressLink(_ui);
		//tmp->init(PointMake(1200, 150));
		//_vWorm.push_back(tmp);
	}
	//~test
	//for (int i = 0; i < 2; i++)
	//{
	//	tmp = new Worm;
	//	tmp->setMapAdressLink(_map);
	//	tmp->setUIAdressLink(_ui);
	//	tmp->init(PointMake(RND->getFromIntTo(2100, 3000), 150));
	//	_vWorm.push_back(tmp);
	//}
	



	_turn = false;
	_wormTurnNumber = 0;
	_camera = _ui->getCameraPointer();
	_backflipTimer = 0;
	_gauge = 0;
	_teamNum = teamNum;



	switch (_teamNum)
	{
	case 0:
	{
		_numImg = IMAGEMANAGER->findImage("num_0");
		_graveImg = IMAGEMANAGER->findImage("grave_0");
		_arrowImg = IMAGEMANAGER->findImage("arrow_0");
		break;
	}

	case 1:
	{
		_numImg = IMAGEMANAGER->findImage("num_1");
		_graveImg = IMAGEMANAGER->findImage("grave_1");
		_arrowImg = IMAGEMANAGER->findImage("arrow_1");
		break;
	}
	case 2:
	{
		_numImg = IMAGEMANAGER->findImage("num_2");
		_graveImg = IMAGEMANAGER->findImage("grave_2");
		_arrowImg = IMAGEMANAGER->findImage("arrow_2");
		break;
	}
	case 3:
	{
		_numImg = IMAGEMANAGER->findImage("num_3");
		_graveImg = IMAGEMANAGER->findImage("grave_3");
		_arrowImg = IMAGEMANAGER->findImage("arrow_3");
		break;
	}
	case 4:
	{
		_numImg = IMAGEMANAGER->findImage("num_4");
		_graveImg = IMAGEMANAGER->findImage("grave_4");
		_arrowImg = IMAGEMANAGER->findImage("arrow_4");
		break;
	}
	case 5:
	{
		_numImg = IMAGEMANAGER->findImage("num_5");
		_graveImg = IMAGEMANAGER->findImage("grave_5");
		_arrowImg = IMAGEMANAGER->findImage("arrow_5");
		break;
	}

	default:
		break;
	}
	return S_OK;
}
void Player::release()
{

}
void Player::update()
{
	for (auto i : _vWorm)
	{
		i->update();
	}
	////턴 받을 시 행동~
	if (_turnTimer - TIMEMANAGER->getWorldTime() > 0)
	{
		keyManager();
	}
	////~턴 받을 시 행동
	turnManager();
	wormStateChk();

	//

}
void Player::render()
{
	for (auto i : _vWorm)
	{
		i->render();
	}
	draw();
}
void Player::draw()
{
	//test~
	/*if (_turnTimer > TIMEMANAGER->getWorldTime())
	{
		char ttt[64];
		wsprintf(ttt, "%d", _vWorm[_wormTurnNumber]->getWorm().currentFrameY);
		TextOut(getMemDC(), 10, 100, ttt, strlen(ttt));

		switch (_vWorm[_wormTurnNumber]->getWorm().state)
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
		case WORMSTATE_WEAPONSTATE:
		{
			char str[64] = "WORMSTATE_WEAPONSTATE";
			TextOut(getMemDC(), 100, 100, str, strlen(str));
			break;
		}
		}
	}*/
	//~test
}


void Player::turnOn()
{
	bool turnend = true;
	for (auto i : _vWorm)
	{
		if (i->getWorm().hp > 0)
		{
			turnend = false;
		}
		WORM tmp = i->getWorm();
		tmp.getDamagedInThisTurn = false;
		i->setWorm(tmp);
	}

	if (turnend)
	{
		_turnTimer = TIMEMANAGER->getWorldTime();
		return;
	}
	SOUNDMANAGER->play("42_YESSIR", VOLUME);
	_turn = true;
	_turnTimer = TIMEMANAGER->getWorldTime() + 45;
	//움직일 지렁이 선별
	while (_vWorm[_wormTurnNumber]->getWorm().hp <= 0)
	{
		_wormTurnNumber++;
		if (_wormTurnNumber >= _vWorm.size())
		{
			_wormTurnNumber = 0;
		}
	}

	if (_vWorm[_wormTurnNumber]->getWorm().currentFrameX == 1)
	{
		WORM tmp = _vWorm[_wormTurnNumber]->getWorm();
		tmp.angle = 0;
		_vWorm[_wormTurnNumber]->setWorm(tmp);
	}
	else
	{
		WORM tmp = _vWorm[_wormTurnNumber]->getWorm();
		tmp.angle = PI;
		_vWorm[_wormTurnNumber]->setWorm(tmp);
	}
	selectWeapon(WEAPON_BAZOOKA);
	_vWorm[_wormTurnNumber]->changeImg(WORMSTATE_WEAPONSTATE);
	_vWorm[_wormTurnNumber]->setCanShoot(true);
	//
}
void Player::endTurn()
{
	for (auto i : _vWorm)
	{
		if (i->getWorm().state == WORMSTATE_DEAD) continue;

		if (i->getWorm().state == WORMSTATE_WEAPONSTATE || i->getCanShoot())
		{
			i->setCanShoot(false);
			i->changeImg(WORMSTATE_IDLE);
		}
		else
		{
			i->changeImg(WORMSTATE_IDLE);
		}
	}
	_turn = false;
	_wormTurnNumber++;
	if (_wormTurnNumber >= _vWorm.size())
	{
		_wormTurnNumber = 0;
	}
}
void Player::keyManager()
{

	//현재 차례 지렁이 설정
	int i = _wormTurnNumber;

	//카메라 중심을 현재 지렁이로 설정
	if (!KEYMANAGER->isStayKeyDown(VK_CONTROL))
	{

	}
	if (!KEYMANAGER->isStayKeyDown(VK_SPACE))
	{
		if (!KEYMANAGER->isStayKeyDown(VK_CONTROL) && (_vWorm[i]->getWorm().state == WORMSTATE_IDLE || _vWorm[i]->getWorm().state == WORMSTATE_MOVING || _vWorm[i]->getWorm().state == WORMSTATE_WEAPONSTATE))
		{
			if (KEYMANAGER->isStayKeyDown(VK_LEFT))
			{
				WORM tmp = _vWorm[i]->getWorm();
				if (_vWorm[i]->getWorm().state == WORMSTATE_IDLE || _vWorm[i]->getWorm().state == WORMSTATE_WEAPONSTATE)
				{
					_vWorm[i]->getWorm().ImgUpdate();
				}
				tmp.currentFrameX = 0;
				_vWorm[i]->setWorm(tmp);

				if (GetPixel(_map->getMap()->getMemDC(), _vWorm[i]->getWorm().xPoint - 4, _vWorm[i]->getWorm().yPoint) == RGB(255, 0, 255))
				{
					tmp = _vWorm[i]->getWorm();
					tmp.xSpeed = -WORMSMOVINGSPEED;
					_vWorm[i]->setWorm(tmp);
				}
				else
				{
					tmp = _vWorm[i]->getWorm();
					tmp.xSpeed = 0;
					_vWorm[i]->setWorm(tmp);
				}
				tmp = _vWorm[i]->getWorm();
				if (tmp.state != WORMSTATE_MOVING)
				{
					tmp.state = WORMSTATE_MOVING;
					tmp.img = IMAGEMANAGER->findImage("WORMSTATE_MOVING");
					tmp.ImgUpdate();
				}
				else
				{
					tmp.state = WORMSTATE_MOVING;
					tmp.img = IMAGEMANAGER->findImage("WORMSTATE_MOVING");
				}
				_vWorm[i]->setWorm(tmp);
			}
			else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
			{
				WORM tmp = _vWorm[i]->getWorm();
				if (_vWorm[i]->getWorm().state == WORMSTATE_IDLE || _vWorm[i]->getWorm().state == WORMSTATE_WEAPONSTATE)
				{
					_vWorm[i]->getWorm().ImgUpdate();
				}
				tmp.currentFrameX = 1;
				_vWorm[i]->setWorm(tmp);
				if (GetPixel(_map->getMap()->getMemDC(), _vWorm[i]->getWorm().xPoint + 4, _vWorm[i]->getWorm().yPoint) == RGB(255, 0, 255))
				{
					WORM tmp = _vWorm[i]->getWorm();
					tmp.xSpeed = WORMSMOVINGSPEED;
					_vWorm[i]->setWorm(tmp);

				}
				else
				{
					WORM tmp = _vWorm[i]->getWorm();
					tmp.xSpeed = 0;
					_vWorm[i]->setWorm(tmp);
				}
				tmp = _vWorm[i]->getWorm();
				tmp.state = WORMSTATE_MOVING;
				tmp.img = IMAGEMANAGER->findImage("WORMSTATE_MOVING");
				_vWorm[i]->setWorm(tmp);

			}
			else if (KEYMANAGER->isStayKeyDown(VK_UP))
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
				case WEAPON_NAPALMSTRIKE:
					break;
				case WEAPON_GIRDER:
					break;
				case WEAPON_ROPE:
					break;
				case WEAPON_TELEPORT:
					break;
				case WEAPON_SKIPGO:
					break;
				case WEAPON_SURRENDER:
					break;
				case WEAPON_END:
					break;
				default:
					break;
				}
				if (_vWorm[i]->getWorm().currentFrameX == 0)
				{
					WORM tmp = _vWorm[i]->getWorm();
					tmp.angle -= 0.05;
					//각도 오차 수정
					if (tmp.angle < PI / 2)
					{
						tmp.angle = PI / 2;
					}
					else if (tmp.angle > PI + PI / 2)
					{
						tmp.angle = PI + PI / 2;
					}
					_vWorm[i]->setWorm(tmp);

				}
				else
				{
					WORM tmp = _vWorm[i]->getWorm();
					tmp.angle += 0.05;
					//각도 오차 수정
					if (PI / 2 < tmp.angle && tmp.angle <= PI)
					{
						tmp.angle = PI / 2;
					}
					else if (PI < tmp.angle && tmp.angle < PI + PI / 2)
					{
						tmp.angle = PI + PI / 2;
					}
					_vWorm[i]->setWorm(tmp);
				}

			}
			else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
			{
				if (_vWorm[i]->getWorm().currentFrameX == 0)
				{
					WORM tmp = _vWorm[i]->getWorm();
					tmp.angle += 0.05;
					//각도 오차 수정
					if (tmp.angle < PI / 2)
					{
						tmp.angle = PI / 2;
					}
					else if (tmp.angle > PI + PI / 2)
					{
						tmp.angle = PI + PI / 2;
					}
					_vWorm[i]->setWorm(tmp);
				}
				else
				{
					WORM tmp = _vWorm[i]->getWorm();
					tmp.angle -= 0.05;
					//각도 오차 수정
					if (PI / 2 < tmp.angle && tmp.angle <= PI)
					{
						tmp.angle = PI / 2;
					}
					else if (PI < tmp.angle && tmp.angle < PI + PI / 2)
					{
						tmp.angle = PI + PI / 2;
					}
					_vWorm[i]->setWorm(tmp);
				}
			}
		}
		if (KEYMANAGER->isOnceKeyUp(VK_LEFT) || KEYMANAGER->isOnceKeyUp(VK_RIGHT))
		{
			if (_vWorm[i]->getWorm().state == WORMSTATE_MOVING)
			{
				WORM tmp = _vWorm[i]->getWorm();
				tmp.xSpeed = 0;
				//if(tmp.canShoot)
				//{
				//	_vWorm[i]->changeImg(WORMSTATE_WEAPONSTATE);
				//}
				//else
				//{
				tmp.state = WORMSTATE_IDLE;
				tmp.img = IMAGEMANAGER->findImage("WORMSTATE_IDLE");
				tmp.ImgUpdate();
				//}
				_vWorm[i]->setWorm(tmp);
			}
		}

		//test~

		/*if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			WORM tmp = _vWorm[i]->getWorm();
			tmp.xPoint = _ptMouse.x - _camera->x;
			tmp.yPoint = _ptMouse.y - _camera->y;
			_vWorm[i]->setWorm(tmp);
		}*/
		if (KEYMANAGER->isOnceKeyDown('T'))
		{
			//selectWeapon(WEAPON_DYNAMITE);

		}

		//~test


		//점프 테스트
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			if (_vWorm[i]->getWorm().state == WORMSTATE_IDLE || _vWorm[i]->getWorm().state == WORMSTATE_MOVING || _vWorm[i]->getWorm().state == WORMSTATE_WEAPONSTATE)
			{
				SOUNDMANAGER->play("27_JUMP1", VOLUME);
				if (_vWorm[i]->getWorm().currentFrameX == 1)
				{
					WORM tmp = _vWorm[i]->getWorm();
					tmp.xSpeed = WORMJUMPXSPEED;
					tmp.ySpeed = -WORMJUMPYSPEED;
					tmp.state = WORMSTATE_JUMPING;
					tmp.img = IMAGEMANAGER->findImage("WORMSTATE_JUMPING");
					tmp.ImgUpdate();
					_vWorm[i]->setWorm(tmp);

				}
				else if (_vWorm[i]->getWorm().currentFrameX == 0)
				{
					WORM tmp = _vWorm[i]->getWorm();
					tmp.xSpeed = -WORMJUMPXSPEED;
					tmp.ySpeed = -WORMJUMPYSPEED;
					tmp.state = WORMSTATE_JUMPING;
					tmp.img = IMAGEMANAGER->findImage("WORMSTATE_JUMPING");
					tmp.ImgUpdate();
					_vWorm[i]->setWorm(tmp);

				}
			}
		}
		//백플립 테스트
		if (KEYMANAGER->isOnceKeyDown(VK_BACK))
		{
			if (TIMEMANAGER->getWorldTime() - _backflipTimer < 0.5 && (_vWorm[i]->getWorm().state == WORMSTATE_IDLE || _vWorm[i]->getWorm().state == WORMSTATE_WEAPONSTATE))
			{
				SOUNDMANAGER->play("28_JUMP2", VOLUME);
				if (_vWorm[i]->getWorm().currentFrameX == 1)
				{
					WORM tmp = _vWorm[i]->getWorm();
					tmp.xSpeed = -WORMBACKFLIPXSPEED;
					tmp.ySpeed = -WORMBACKFLIPYSPEED;
					tmp.state = WORMSTATE_BACKFLIP;
					tmp.img = IMAGEMANAGER->findImage("WORMSTATE_BACKFLIP");
					tmp.ImgUpdate();
					_vWorm[i]->setWorm(tmp);

				}
				else if (_vWorm[i]->getWorm().currentFrameX == 0)
				{
					WORM tmp = _vWorm[i]->getWorm();
					tmp.xSpeed = WORMBACKFLIPXSPEED;
					tmp.ySpeed = -WORMBACKFLIPYSPEED;
					tmp.state = WORMSTATE_BACKFLIP;
					tmp.img = IMAGEMANAGER->findImage("WORMSTATE_BACKFLIP");
					tmp.ImgUpdate();
					_vWorm[i]->setWorm(tmp);
				}
			}
			else
			{

			}
			_backflipTimer = TIMEMANAGER->getWorldTime();
		}

	}

	if (KEYMANAGER->isStayKeyDown(VK_SPACE) && _vWorm[i]->getCanShoot())
	{
		WORM tmp = _vWorm[i]->getWorm();
		switch (_selectedWeapon)
		{
			//충전식
		case WEAPON_BAZOOKA:
		case WEAPON_HIMMING_MISSILE:
		case WEAPON_GRENADE:
		case WEAPON_CLUSTER:
		case WEAPON_PETROL:
		case WEAPON_BANANA:
		case WEAPON_HOLY:
			_gauge += 0.3;
			if (!SOUNDMANAGER->isPlaySound("16_THROWPOWERUP"))
			{
				SOUNDMANAGER->play("16_THROWPOWERUP");
			}
			if (_gauge > 20)
			{
				_wm->launchWeapon(_selectedWeapon, PointMake(tmp.xPoint, tmp.yPoint), _gauge, tmp.angle);
				_vWorm[i]->setCanShoot(false);
				_turnTimer = TIMEMANAGER->getWorldTime() + 1;
				_gauge = 0;
			}
			break;
			//즉발식
		case WEAPON_DYNAMITE:
		case WEAPON_MINE:
		case WEAPON_FIREPUNCH:
		{
			_wm->launchWeapon(_selectedWeapon, PointMake(tmp.xPoint, tmp.yPoint), 1, tmp.angle);
			_vWorm[i]->setCanShoot(false);
			_turnTimer = TIMEMANAGER->getWorldTime() + 5;
			_vWorm[i]->fireWeapon();
			break;
		}
		case WEAPON_BASEBALLBAT:
		{

			break;
		}
		//공중지원
		case WEAPON_AIRSTRIKE:
		case WEAPON_NAPALMSTRIKE:
		{
			playWormAirsupport();
			_wm->launchWeapon(_selectedWeapon, PointMake(tmp.xPoint, tmp.yPoint), _gauge, tmp.angle);
			_vWorm[i]->setCanShoot(false);
			_turn = false;
			_turnTimer = TIMEMANAGER->getWorldTime() + 0.3;
			_vWorm[i]->fireWeapon();
			break;
		}
		//특별아이템
		case WEAPON_GIRDER:
			break;
		case WEAPON_ROPE:
			break;
		case WEAPON_TELEPORT:
		{
			SOUNDMANAGER->play("15_TELEPORT", VOLUME);
			_vWorm[i]->setCanShoot(false);
			_vWorm[i]->fireWeapon();
			_turnTimer = TIMEMANAGER->getWorldTime() + 4;
		}
		break;
		case WEAPON_SKIPGO:
			break;
		case WEAPON_SURRENDER:
			break;
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_SPACE) && _vWorm[i]->getCanShoot() && _gauge != 0)
	{
		if (SOUNDMANAGER->isPlaySound("16_THROWPOWERUP"))
		{
			SOUNDMANAGER->stop("16_THROWPOWERUP");
		}
		WORM tmp = _vWorm[i]->getWorm();
		switch (_selectedWeapon)
		{
		case WEAPON_BAZOOKA:
		case WEAPON_HIMMING_MISSILE:
		case WEAPON_GRENADE:
		case WEAPON_CLUSTER:
		case WEAPON_PETROL:
		case WEAPON_BANANA:
		case WEAPON_HOLY:
		case WEAPON_DYNAMITE:
		case WEAPON_MINE:
			_wm->launchWeapon(_selectedWeapon, PointMake(tmp.xPoint, tmp.yPoint), _gauge, tmp.angle);
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
			break;
		case WEAPON_SKIPGO:
			break;
		case WEAPON_SURRENDER:
			break;
		case WEAPON_END:
			break;
		default:
			break;
		}

		_vWorm[i]->setCanShoot(false);
		_turn = false;
		_turnTimer = TIMEMANAGER->getWorldTime() + 1;
		_gauge = 0;
	}

	//fly Test
	if (KEYMANAGER->isOnceKeyDown('F'))
	{
		WORM tmp = _vWorm[i]->getWorm();
		int speed = int(getDistance(tmp.xPoint, tmp.yPoint, _ptMouse.x - _camera->x, _ptMouse.y - _camera->y) / 10);
		tmp.xSpeed = cosf(getAngle(tmp.xPoint, tmp.yPoint, _ptMouse.x - _camera->x, _ptMouse.y - _camera->y))*speed;
		tmp.ySpeed = -sinf(getAngle(tmp.xPoint, tmp.yPoint, _ptMouse.x - _camera->x, _ptMouse.y - _camera->y))*speed;
		tmp.state = WORMSTATE_FLYING;
		tmp.img = IMAGEMANAGER->findImage("WORMSTATE_FLYING");
		tmp.ImgUpdate();
		_vWorm[i]->setWorm(tmp);
	}
	//~test

}

void Player::selectWeapon(WEAPON w)
{
	_ui->setShowMarkPoint(false);
	if (w == WEAPON_END) return;
	_selectedWeapon = w;
	int i = _wormTurnNumber;
	_vWorm[i]->setSelWeapon(_selectedWeapon);
	WORM tmp = _vWorm[i]->getWorm();
	switch (_selectedWeapon)
	{
	case WEAPON_BAZOOKA:
		tmp.w_img1 = IMAGEMANAGER->findImage("baz_S");
		tmp.w_img2 = IMAGEMANAGER->findImage("baz_A");
		tmp.wpholdtype = WEAPONHOLDTYPE_ANGLE;
		tmp.state = WORMSTATE_WEAPONSTATE;
		break;
	case WEAPON_HIMMING_MISSILE:
		tmp.w_img1 = IMAGEMANAGER->findImage("baz2_S");
		tmp.w_img2 = IMAGEMANAGER->findImage("baz2_A");
		tmp.wpholdtype = WEAPONHOLDTYPE_ANGLE;
		tmp.state = WORMSTATE_WEAPONSTATE;
		break;
	case WEAPON_GRENADE:
		tmp.w_img1 = IMAGEMANAGER->findImage("grn_S");
		tmp.w_img2 = IMAGEMANAGER->findImage("grn_A");
		tmp.wpholdtype = WEAPONHOLDTYPE_ANGLE;
		tmp.state = WORMSTATE_WEAPONSTATE;
		break;
	case WEAPON_CLUSTER:
		tmp.w_img1 = IMAGEMANAGER->findImage("t");
		tmp.w_img2 = IMAGEMANAGER->findImage("t");
		tmp.w_img3 = IMAGEMANAGER->findImage("t");
		break;
	case WEAPON_PETROL:
		tmp.w_img1 = IMAGEMANAGER->findImage("t");
		tmp.w_img2 = IMAGEMANAGER->findImage("t");
		tmp.w_img3 = IMAGEMANAGER->findImage("t");
		break;
	case WEAPON_BANANA:
		tmp.w_img1 = IMAGEMANAGER->findImage("ban_S");
		tmp.w_img2 = IMAGEMANAGER->findImage("ban_A");
		tmp.wpholdtype = WEAPONHOLDTYPE_ANGLE;
		tmp.state = WORMSTATE_WEAPONSTATE;
		break;
	case WEAPON_HOLY:
		tmp.w_img1 = IMAGEMANAGER->findImage("holy_S");
		tmp.w_img2 = IMAGEMANAGER->findImage("holy_A");
		tmp.wpholdtype = WEAPONHOLDTYPE_ANGLE;
		tmp.state = WORMSTATE_WEAPONSTATE;
		break;
	case WEAPON_DYNAMITE:
		tmp.w_img1 = IMAGEMANAGER->findImage("dyn_S");
		tmp.w_img2 = IMAGEMANAGER->findImage("dyn_S");
		tmp.wpholdtype = WEAPONHOLDTYPE_HOLD;
		tmp.state = WORMSTATE_WEAPONSTATE;
		break;
	case WEAPON_MINE:
		tmp.w_img1 = IMAGEMANAGER->findImage("mine_S");
		tmp.w_img2 = IMAGEMANAGER->findImage("mine_S");
		tmp.wpholdtype = WEAPONHOLDTYPE_HOLD;
		tmp.state = WORMSTATE_WEAPONSTATE;
		break;
	case WEAPON_FIREPUNCH:
		tmp.w_img1 = IMAGEMANAGER->findImage("t");
		tmp.w_img2 = IMAGEMANAGER->findImage("t");
		tmp.w_img3 = IMAGEMANAGER->findImage("t");
		tmp.wpholdtype = WEAPONHOLDTYPE_SPECIAL;
		tmp.state = WORMSTATE_WEAPONSTATE;
		break;
	case WEAPON_BASEBALLBAT:
		tmp.w_img1 = IMAGEMANAGER->findImage("bat_S");
		tmp.w_img2 = IMAGEMANAGER->findImage("bat_A");
		tmp.w_img3 = IMAGEMANAGER->findImage("bat_A2");
		tmp.wpholdtype = WEAPONHOLDTYPE_ANGLE;
		tmp.state = WORMSTATE_WEAPONSTATE;
		break;
	case WEAPON_AIRSTRIKE:
		tmp.w_img1 = IMAGEMANAGER->findImage("aircall_S");
		tmp.w_img2 = IMAGEMANAGER->findImage("aircall_I");
		tmp.wpholdtype = WEAPONHOLDTYPE_HOLD;
		tmp.state = WORMSTATE_WEAPONSTATE;
		break;
	case WEAPON_NAPALMSTRIKE:
		tmp.w_img1 = IMAGEMANAGER->findImage("aircall_S");
		tmp.w_img2 = IMAGEMANAGER->findImage("aircall_I");
		tmp.wpholdtype = WEAPONHOLDTYPE_HOLD;
		tmp.state = WORMSTATE_WEAPONSTATE;
		break;
	case WEAPON_GIRDER:
		tmp.w_img1 = IMAGEMANAGER->findImage("t");
		tmp.w_img2 = IMAGEMANAGER->findImage("t");
		tmp.w_img3 = IMAGEMANAGER->findImage("t");
		tmp.wpholdtype = WEAPONHOLDTYPE_SPECIAL;
		tmp.state = WORMSTATE_WEAPONSTATE;
		break;
	case WEAPON_ROPE:
		tmp.w_img1 = IMAGEMANAGER->findImage("t");
		tmp.w_img2 = IMAGEMANAGER->findImage("t");
		tmp.w_img3 = IMAGEMANAGER->findImage("t");
		tmp.wpholdtype = WEAPONHOLDTYPE_SPECIAL;
		tmp.state = WORMSTATE_WEAPONSTATE;
		break;
	case WEAPON_TELEPORT:
		tmp.w_img1 = IMAGEMANAGER->findImage("tel_S");
		tmp.w_img2 = IMAGEMANAGER->findImage("tel_A");
		tmp.wpholdtype = WEAPONHOLDTYPE_HOLD;
		tmp.state = WORMSTATE_WEAPONSTATE;
		break;
	case WEAPON_SKIPGO:
		tmp.w_img1 = IMAGEMANAGER->findImage("skip_S");
		tmp.w_img2 = IMAGEMANAGER->findImage("skip_S");
		tmp.wpholdtype = WEAPONHOLDTYPE_SPECIAL;
		tmp.state = WORMSTATE_WEAPONSTATE;
		break;
	case WEAPON_SURRENDER:
		tmp.w_img1 = IMAGEMANAGER->findImage("t");
		tmp.w_img2 = IMAGEMANAGER->findImage("t");
		tmp.w_img3 = IMAGEMANAGER->findImage("t");
		tmp.wpholdtype = WEAPONHOLDTYPE_SPECIAL;
		tmp.state = WORMSTATE_WEAPONSTATE;
		break;
	}
	tmp.img = tmp.w_img1;
	tmp.currentFrameY = 0;
	if (tmp.currentFrameX == 0)
	{
		tmp.angle = PI;
	}
	else
	{
		tmp.angle = 0;
	}
	_vWorm[i]->setWorm(tmp);
	int a = 0;
}

POINT Player::getWormPoint()
{
	int i = _wormTurnNumber;
	return PointMake(_vWorm[i]->getWorm().xPoint, _vWorm[i]->getWorm().yPoint);
}

POINT Player::getCrhPoint()
{
	int i = _wormTurnNumber;
	POINT wormpoint = PointMake(_vWorm[i]->getWorm().xPoint, _vWorm[i]->getWorm().yPoint);
	wormpoint.x += cosf(_vWorm[i]->getWorm().angle) * 75;
	wormpoint.y -= sinf(_vWorm[i]->getWorm().angle) * 75;
	return wormpoint;
}

void Player::boomDmg(tagWeapon w)
{
	for (auto i : _vWorm)
	{
		if (getDistance(i->getWorm().xPoint, i->getWorm().yPoint, w.xPoint, w.yPoint) < w.radius + 10 &&
			!(i->getWorm().state == WORMSTATE_DEAD || i->getWorm().state == WORMSTATE_DYING || i->getWorm().state == WORMSTATE_DROWNING))
		{
			i->boomDmg(w);
			_turnTimer = TIMEMANAGER->getWorldTime();
		}
	}
	//for (int i = 0; i < _vWorm.size(); i++)
	//{
	//	if (getDistance(_vWorm[i]->getWorm().xPoint, _vWorm[i]->getWorm().yPoint, w.xPoint, w.yPoint) < w.radius + 10)
	//	{
	//		WORM tmp = _vWorm[i]->getWorm();
	//		tmp.xSpeed = cosf(getAngle(w.xPoint, w.yPoint, tmp.xPoint, tmp.yPoint))*w.maxKnockBackPower;
	//		tmp.ySpeed = -sinf(getAngle(w.xPoint, w.yPoint, tmp.xPoint, tmp.yPoint))*w.maxKnockBackPower;
	//		tmp.state = WORMSTATE_FLYING;
	//		tmp.img = IMAGEMANAGER->findImage("WORMSTATE_FLYING");
	//		tmp.ImgUpdate();
	//		_vWorm[i]->setWorm(tmp);
	//	}
	//	
	//}
}
void Player::fireDmg(tagWeapon w)
{
	for (auto i : _vWorm)
	{
		if (getDistance(i->getWorm().xPoint, i->getWorm().yPoint, w.xPoint, w.yPoint) < w.radius + 10 &&
			!(i->getWorm().state == WORMSTATE_DEAD || i->getWorm().state == WORMSTATE_DYING || i->getWorm().state == WORMSTATE_DROWNING))
		{
			i->fireDmg(w);
			_turnTimer = TIMEMANAGER->getWorldTime();
		}
	}
}
bool Player::isThereAliveWorm()
{
	bool alive = false;
	for (auto i : _vWorm)
	{
		if (i->getWorm().hp > 0)
		{
			alive = true;
			break;
		}
	}
	return alive;
}

bool Player::isPlayerTurnEnd()
{
	if (TIMEMANAGER->getWorldTime() - _turnTimer >= 0 || !_turn)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Player::cameraFocusCtrl()
{
	int i = _wormTurnNumber;
	if (!KEYMANAGER->isStayKeyDown(VK_CONTROL))
	{
		_ui->setCameraFocus(PointMake(_vWorm[i]->getWorm().xPoint, _vWorm[i]->getWorm().yPoint));
	}
}

void Player::turnManager()
{
	if (_turnTimer - TIMEMANAGER->getWorldTime() < 0)
	{
		if (_turn) _turn = false;
	}
}
void Player::wormStateChk()
{
	for (int i = 0; i < _vWorm.size(); i++)
	{
		if (_vWorm[i]->getWormExplode() == true)
		{
			_map->addgrave(PointMake(_vWorm[i]->getWorm().xPoint, _vWorm[i]->getWorm().yPoint), _graveImg);
			_wm->wormExplode(PointMake(_vWorm[i]->getWorm().xPoint, _vWorm[i]->getWorm().yPoint));
			_vWorm[i]->setWormExplode(false);
		}
	}

	if (_vWorm[_wormTurnNumber]->getWorm().state == WORMSTATE_DROWNING || _vWorm[_wormTurnNumber]->getWorm().state == WORMSTATE_DEAD)
	{
		_turnTimer = TIMEMANAGER->getWorldTime();
	}
}

void Player::playWormAirsupport()
{
	switch (RND->getInt(3))
	{
	case 0:
		SOUNDMANAGER->play("26_INCOMING", VOLUME);
		break;
	case 1:
		SOUNDMANAGER->play("36_ORDERS", VOLUME);
		break;
	case 2:
		SOUNDMANAGER->play("48_TAKECOVER", VOLUME);
		break;
	}
}