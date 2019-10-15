#include "stdafx.h"
#include "WeaponManager.h"
#include "UI.h"
#include "PlayerManager.h"
#include "Map.h"


WeaponManager::WeaponManager()
{
}


WeaponManager::~WeaponManager()
{
}

HRESULT WeaponManager::init()
{
	_camera = _ui->getCameraPointer();
	_turn = false;
	return S_OK;
}
void WeaponManager::release()
{

}
void WeaponManager::update()
{

	for (int i = _vWeapon.size() - 1; i >= 0; i--)
	{
		if (_vWeapon[i]->gettagWeapon().del)
		{
			if (_vWeapon[i]->getImg() == IMAGEMANAGER->findImage("WP_ban"))
			{
				for (int i = 0; i < 5; i++)
				{
					banana2* tmp = new banana2;
					tmp->init(10, RND->getFromFloatTo(PI * 1 / 4, PI * 3 / 4), PointMake(_vWeapon[i]->getWeapon().xPoint, _vWeapon[i]->getWeapon().yPoint), _ptMouse, _map, _ui, _pm);
					_vWeapon.push_back(tmp);
				}
			}
			
			removeWeapon(i);
			break;
		}
	}
	for (auto i : _vWeapon)
	{
		i->update();
	}

	//test~
	if (KEYMANAGER->isStayKeyDown('T'))
	{
		//EFFECTMANAGER->play("smkdrk40", _ptMouse.x - _ui->getCamera().x, _ptMouse.y - _ui->getCamera().y);
		Weapon* tmp;
		tmp = new fire;
		tmp->init(10, PI, PointMake(_ptMouse.x - _ui->getCamera().x,_ptMouse.y - _ui->getCamera().y), _ptMouse, _map, _ui, _pm);
		_vWeapon.push_back(tmp);
		//_map->addgrave(PointMake(_ptMouse.x - _camera->x, _ptMouse.y - _camera->y),IMAGEMANAGER->findImage("grave_1"));
	}
	//~test
}
void WeaponManager::render()
{
	for (auto i : _vWeapon)
	{
		i->render();
	}
}
void WeaponManager::launchWeapon(WEAPON type, POINT sPoint, float power, float angle)
{
	Weapon* tmp;
	switch (type)
	{
	case WEAPON_BAZOOKA:
		tmp = new bazooka;
		tmp->init(power, angle, sPoint, _ptMouse, _map, _ui, _pm);
		SOUNDMANAGER->play("13_ROCKETRELEASE");
		break;
	case WEAPON_HIMMING_MISSILE:
		tmp = new homingbaz;
		tmp->init(power, angle, sPoint, _ptMouse, _map, _ui, _pm);
		SOUNDMANAGER->play("13_ROCKETRELEASE");
		break;
	case WEAPON_GRENADE:
		tmp = new grenade;
		tmp->init(power, angle, sPoint, _ptMouse, _map, _ui, _pm);
		SOUNDMANAGER->play("17_THROWRELEASE");
		break;
	case WEAPON_CLUSTER:
		break;
	case WEAPON_PETROL:
		break;
	case WEAPON_BANANA:
		tmp = new banana;
		tmp->init(power, angle, sPoint, _ptMouse, _map, _ui, _pm);
		SOUNDMANAGER->play("17_THROWRELEASE");
		break;
	case WEAPON_HOLY:
		tmp = new holy;
		tmp->init(power, angle, sPoint, _ptMouse, _map, _ui, _pm);
		SOUNDMANAGER->play("17_THROWRELEASE");
		break;
	case WEAPON_DYNAMITE:
		tmp = new dynamite;
		tmp->init(power, angle, sPoint, _ptMouse, _map, _ui, _pm);
		SOUNDMANAGER->play("30_LAUGH");
		break;
	case WEAPON_MINE:
		tmp = new mine;
		tmp->init(power, angle, sPoint, _ptMouse, _map, _ui, _pm);
		SOUNDMANAGER->play("30_LAUGH");
		break;
	case WEAPON_FIREPUNCH:
		break;
	case WEAPON_BASEBALLBAT:
		break;
	case WEAPON_AIRSTRIKE:
		tmp = new airstrike;
		tmp->init(power, angle, sPoint, _ptMouse, _map, _ui, _pm);
		SOUNDMANAGER->play("06_Airstrike");
		break;
	case WEAPON_NAPALMSTRIKE:
		tmp = new firestrike;
		tmp->init(power, angle, sPoint, _ptMouse, _map, _ui, _pm);
		SOUNDMANAGER->play("06_Airstrike");
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
	}

	
	_vWeapon.push_back(tmp);
}

void WeaponManager::removeWeapon(int arrNum)
{
	SAFE_DELETE(_vWeapon[arrNum]);
	_vWeapon.erase(_vWeapon.begin() + arrNum);
}
void WeaponManager::turnOn()
{
	_turnTimer = TIMEMANAGER->getWorldTime() + 2;
	_turn = true;
}
bool WeaponManager::isWeaponTurnEnd()
{

	int nojweaponsize = _vWeapon.size();
	for(auto i : _vWeapon)
	{
		if (i->getWeapon().isObject)
		{
			nojweaponsize--;
		}
	}

	if (nojweaponsize == 0)
	{
		_turn = false;
		if (_turnTimer  - TIMEMANAGER->getWorldTime() <= 0)
		{
			return true;
		}
		
	}
	else
	{
		_turnTimer = TIMEMANAGER->getWorldTime() + 2.5;
	}
	return false;
}

void WeaponManager::cameraFocusCtrl()
{
	//if (!_turn) return;
	bool cameraset = false;
	for (auto i : _vWeapon)
	{
		if (!i->getWeapon().isObject)
		{
 			_ui->setCameraFocus(PointMake(i->gettagWeapon().xPoint, i->gettagWeapon().yPoint));
			cameraset = true;
		}
		else
		{

		}
	}

	if (!cameraset)
	{
		//_pm->cameraCtrl();
	}
}

void WeaponManager::wormExplode(POINT p)
{
	SOUNDMANAGER->play("09_Explosion2");
	tagWeapon tmp;
	tmp.maxDmg = 40;
	tmp.minDmg = 5;
	tmp.maxKnockBackPower = 5;
	tmp.minKnockBackPower = 1;
	tmp.radius = 60;
	tmp.xPoint = p.x;
	tmp.yPoint = p.y;
	_pm->boomDmg(tmp);
	_ui->boomDmg(tmp);
}