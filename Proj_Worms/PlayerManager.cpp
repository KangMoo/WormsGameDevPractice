#include "stdafx.h"
#include "PlayerManager.h"
#include "Map.h"
#include "UI.h"
#include "WeaponManager.h"

PlayerManager::PlayerManager()
{
}


PlayerManager::~PlayerManager()
{
}
HRESULT PlayerManager::init()
{
	Player* tmp = new Player;
	tmp->setMapAdressLink(_map);
	tmp->setUIAdressLink(_ui);
	tmp->setWMAddressLink(_wm);
	tmp->init(0);
	_vPlayer.push_back(tmp);
	tmp = new Player;
	tmp->setMapAdressLink(_map);
	tmp->setUIAdressLink(_ui);
	tmp->setWMAddressLink(_wm);
	tmp->init(1);
	_vPlayer.push_back(tmp);
	//tmp = new Player;
	//tmp->setMapAdressLink(_map);
	//tmp->setUIAdressLink(_ui);
	//tmp->setWMAddressLink(_wm);
	//tmp->init(2);
	//_vPlayer.push_back(tmp);
	//tmp = new Player;
	//tmp->setMapAdressLink(_map);
	//tmp->setUIAdressLink(_ui);
	//tmp->setWMAddressLink(_wm);
	//tmp->init(3);
	//_vPlayer.push_back(tmp);
	//tmp = new Player;
	//tmp->setMapAdressLink(_map);
	//tmp->setUIAdressLink(_ui);
	//tmp->setWMAddressLink(_wm);
	//tmp->init(4);
	//_vPlayer.push_back(tmp);
	//tmp = new Player;
	//tmp->setMapAdressLink(_map);
	//tmp->setUIAdressLink(_ui);
	//tmp->setWMAddressLink(_wm);
	//tmp->init(2);
	//_vPlayer.push_back(tmp);
	//tmp = new Player;
	//tmp->setMapAdressLink(_map);
	//tmp->setUIAdressLink(_ui);
	//tmp->setWMAddressLink(_wm);
	//tmp->init(5);

	_playerTurnNum = 0;
	//_vPlayer[_playerTurnNum]->turnOn();
	_playerturnTimer = 0;
	_weaponturnTimer = 0;
	_dmgTimer = 0;
	_delayTimer = 0;
	_howManyWormDmged = 0;
	_turnCount = 0;
	_turnphase = TURNPHASE_DELAY;
	_delayTimer = TIMEMANAGER->getWorldTime() + 3;
	_camera = _ui->getCameraPointer();
	_isGameOver = false;
	return S_OK;
}
void PlayerManager::release()
{

}
void PlayerManager::update()
{
	int a = 0;
	for (auto i : _vPlayer)
	{
		i->update();
	}

	if (!_isGameOver)
	{
		turnManage();
	}
	else
	{
		endgame();
	}
	playerStateChk();
	crhCtrl();
	gameOverChk();
}
void PlayerManager::render()
{
	for (auto i : _vPlayer)
	{
		i->render();
	}
	draw();
}
void PlayerManager::draw()
{
	//게이지
	drawGauge();
	//크로스헤어
	drawCRH();
	//화살표
	drawArrow();

	//test
	/*switch (_turnphase)
	{
	case TURNPHASE_PLAYERTURN:
		TextOut(getMemDC(), 10, 130, "PT", 2);
		break;
	case TURNPHASE_WEAPONTURN:
		TextOut(getMemDC(), 10, 130, "WT", 2);
		break;
	case TURNPHASE_DAMAGETURN:
		TextOut(getMemDC(), 10, 130, "DT", 2);
		break;
	case TURNPHASE_DELAY:
		TextOut(getMemDC(), 10, 130, "DL", 2);
		break;
	case TURNPHASE_SETTURN:
		TextOut(getMemDC(), 10, 130, "ST", 2);
		break;
	default:
		break;
	}*/
}

void PlayerManager::crhCtrl()
{
	for (auto i : _vPlayer)
	{
		if (i->getTurn())
		{
			_crhPoint = i->getCrhPoint();
			break;
		}
	}
}
void PlayerManager::drawCRH()
{
	int wormTurnNumber;
	for (auto i : _vPlayer)
	{
		if (i->getTurn())
		{
			if (i->getWormVector()[i->getWormTurnNumber()]->getWorm().wpholdtype != WEAPONHOLDTYPE_ANGLE) return;
			_crhPoint = i->getCrhPoint();
			POINT wormPoint = i->getWormPoint();
			////
			int maxFrame = IMAGEMANAGER->findImage("CRH")->getMaxFrameY();
			float angle;


			angle = getAngle(wormPoint.x, wormPoint.y, _crhPoint.x, _crhPoint.y);

			int yFrame = 0;
			while (!(PI - PI / maxFrame <= angle && angle <= PI + PI / maxFrame))
			{
				yFrame++;
				angle += PI / (maxFrame / 2);
				if (angle >= PI2) angle -= PI2;
				if (yFrame >= maxFrame / 2) yFrame -= maxFrame / 2;
			}

			IMAGEMANAGER->findImage("CRH")->setFrameY(int(yFrame));
			////
			wormTurnNumber = i->getWormTurnNumber();

			if (_vPlayer[_playerTurnNum]->getWormVector()[_vPlayer[_playerTurnNum]->getWormTurnNumber()]->getWorm().state == WORMSTATE_WEAPONSTATE)
			{
				IMAGEMANAGER->frameRender("CRH", getMemDC(), _crhPoint.x + _camera->x - IMAGEMANAGER->findImage("CRH")->getFrameWidth() / 2, _crhPoint.y + _camera->y - IMAGEMANAGER->findImage("CRH")->getFrameHeight() / 2);
			}
			break;
		}
	}
}
void PlayerManager::drawGauge()
{
	int wormTurnNumber;
	for (auto i : _vPlayer)
	{
		if (i->getTurn())
		{
			if (i->getWormVector()[i->getWormTurnNumber()]->getWorm().wpholdtype != WEAPONHOLDTYPE_ANGLE) return;
			POINT crhPoint = i->getCrhPoint();
			POINT wormPoint = i->getWormPoint();
			float angle = getAngle(wormPoint.x, wormPoint.y, crhPoint.x, crhPoint.y);
			float gauge = i->getGauge() / 2;

			for (float i = 0; i < gauge; i += 0.7)
			{
				HBRUSH brush = CreateSolidBrush(RGB(255, 220 - i * 22, 220 - i * 22));
				HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
				HPEN pen = CreatePen(PS_SOLID, 2, RGB(255, 220 - i * 22, 220 - i * 22)); // 펜 색을 넣음
				HPEN oldPen = (HPEN)SelectObject(getMemDC(), pen);
				float xPoint = wormPoint.x + cosf(angle)*i * 7 + cosf(angle) * 13;
				float yPoint = wormPoint.y - sinf(angle)*i * 7 - sinf(angle) * 13;
				EllipseMakeCenter(getMemDC(), xPoint + _camera->x, yPoint + _camera->y, i * 2 + 5, i * 2 + 5);
				DeleteObject(brush);
				DeleteObject(oldBrush);
				DeleteObject(pen);
				DeleteObject(oldPen);
			}
			break;
		}
	}
}
void PlayerManager::drawArrow()
{

}
void PlayerManager::boomDmg(tagWeapon w)
{
	for (auto i : _vPlayer)
	{
		i->boomDmg(w);
	}
}
void PlayerManager::fireDmg(tagWeapon w)
{
	for (auto i : _vPlayer)
	{
		i->fireDmg(w);
	}
}
void PlayerManager::turnManage()
{
	switch (_turnphase)
	{
	case TURNPHASE_PLAYERTURN:
	{
		_vPlayer[_playerTurnNum]->cameraFocusCtrl();
		if (_vPlayer[_playerTurnNum]->isPlayerTurnEnd())
		{
			_vPlayer[_playerTurnNum]->endTurn();
			_playerTurnNum++;
			if (_playerTurnNum >= _vPlayer.size())
			{
				_playerTurnNum = 0;
			}
			_turnphase = TURNPHASE_WEAPONTURN;
			_wm->turnOn();
		}
		break;
	}
	case TURNPHASE_WEAPONTURN:
	{
		_wm->cameraFocusCtrl();
		if (_wm->isWeaponTurnEnd())
		{
			_turnphase = TURNPHASE_DAMAGETURN;
			_dmgTimer = TIMEMANAGER->getWorldTime() + 2;

			//playNoWormDamaged()함수를 위한 확인용

			bool noWormDamaged = true;
			for (auto i : _vPlayer)
			{
				for (auto j : i->getWormVector())
				{
					if (j->getWorm().getDamagedInThisTurn)
					{
						noWormDamaged = false;
					}
				}
			}
			if (noWormDamaged)
			{
				playNoWormDamaged();
			}
		}
		break;
	}
	case TURNPHASE_DAMAGETURN:
	{
		damagePhase();
		break;
	}
	case TURNPHASE_DELAY:
	{
		if (_isGameOver)
		{
			if (_delayTimer - TIMEMANAGER->getWorldTime() <= 0)
			{
				//SCENEMANAGER->changeScene();
			}
		}
		else
		{
			if (_delayTimer - TIMEMANAGER->getWorldTime() <= 0)
			{
				_turnphase = TURNPHASE_SETTURN;

				for (auto i : _vPlayer)
				{
					vector<Worm*> vw = i->getWormVector();
					for (auto j : vw)
					{
						WORM tmp = j->getWorm();
						tmp.getDamagedInThisTurn = false;
						j->setWorm(tmp);
					}
				}
			}
		}
		break;
	}
	case TURNPHASE_SETTURN:
	{
		_playerturnTimer = TIMEMANAGER->getWorldTime() + 45;
		//살아있는 지렁이 있는지 여부 판단 bool

		if (_vPlayer[_playerTurnNum]->isThereAliveWorm())
		{
			_vPlayer[_playerTurnNum]->turnOn();
			_turnphase = TURNPHASE_PLAYERTURN;
			_ui->windCtrl();
		}
		else
		{
			_playerTurnNum++;
			if (_playerTurnNum >= _vPlayer.size())
			{
				_playerTurnNum = 0;
			}
		}
		break;
	}
	}
}

void PlayerManager::damagePhase()
{
	bool isDamagedWorm = false;
	for (auto i : _vPlayer)
	{
		for (int j = 0; j < i->getWormVector().size(); j++)
		{
			_vWormForDmgFunc.push_back(i->getWormVector()[j]);
		}
	}
	for (int i = 0; i < _vWormForDmgFunc.size(); i++)
	{
		if (_vWormForDmgFunc[i]->getWorm().getDamagedInThisTurn)
		{
			isDamagedWorm = true;
			WORM tmp = _vWormForDmgFunc[i]->getWorm();
			if (TIMEMANAGER->getWorldTime() - _dmgTimer <= 0)
			{
				//카메라 포커스 맞추기
				_ui->setCameraFocus(PointMake(tmp.xPoint, tmp.yPoint));
				//이미지 변환
				if (true)
				{
					if (tmp.hp > 30)
					{
						if (tmp.img != IMAGEMANAGER->findImage("W_Fist"))
						{
							playWormDamagedSound();
							tmp.img = IMAGEMANAGER->findImage("W_Fist");
							if (_vWormForDmgFunc[i]->getWorm().currentFrameY != 0) tmp.ImgUpdate();
							tmp.state = WORMSTATE_IDLE;
						}
					}
					else if (tmp.hp > 0)
					{
						if (tmp.img != IMAGEMANAGER->findImage("W_brth2"))
						{
							tmp.img = IMAGEMANAGER->findImage("W_brth2");
							if (_vWormForDmgFunc[i]->getWorm().currentFrameY != 0) tmp.ImgUpdate();
							tmp.state = WORMSTATE_IDLE;
						}
					}
					else
					{
						if (tmp.state != WORMSTATE_DROWNING)
						{
							if (tmp.img != IMAGEMANAGER->findImage("WORMSTATE_DYING"))
							{
								playWormDyingSound();
								tmp.img = IMAGEMANAGER->findImage("WORMSTATE_DYING");
								if (_vWormForDmgFunc[i]->getWorm().currentFrameY != 0) tmp.ImgUpdate();
								tmp.state = WORMSTATE_DYING;
							}
						}
					}
				}
				_vWormForDmgFunc[i]->setWorm(tmp);
				break;
			}
			else
			{
				_dmgTimer = TIMEMANAGER->getWorldTime() + 2;
				tmp.getDamagedInThisTurn = false;
				_vWormForDmgFunc[i]->setWorm(tmp);
				break;
			}
			//변경내용 저장
			_vWormForDmgFunc[i]->setWorm(tmp);

		}
	}
	if (isDamagedWorm == false)
	{
		_turnphase = TURNPHASE_DELAY;
		_delayTimer = TIMEMANAGER->getWorldTime() + 2;
		if (_isGameOver)
		{
			for (auto i : _vPlayer)
			{
				for (auto j : i->getWormVector())
				{
					WORM tmp = j->getWorm();
					tmp.state = WORMSTATE_IDLE;
					//tmp.img = 
					j->setWorm(tmp);
				}
			}
			_delayTimer = TIMEMANAGER->getWorldTime() + 5;
		}
	}
}

void PlayerManager::cameraCtrl()
{
	POINT tmp = _vPlayer[_playerTurnNum]->getWormPoint();
	_ui->setCameraFocus(PointMake(tmp.x, tmp.y));
}

int PlayerManager::gameOverChk()
{
	int zeroCount = 0;
	for (auto i : _vPlayer)
	{
		bool _isAllWormDead = true;
		for (auto j : i->getWormVector())
		{
			if (j->getWorm().state != WORMSTATE_DEAD)
			{
				_isAllWormDead = false;
				break;
			}
		}
		if (_isAllWormDead)
		{
			zeroCount++;
		}
	}

	if (zeroCount == _vPlayer.size() || zeroCount == _vPlayer.size() - 1)
	{
		_isGameOver = true;
	}
	return zeroCount;
}

void PlayerManager::playWormDamagedSound()
{
	switch (RND->getInt(4))
	{
	case 0:
		SOUNDMANAGER->play("25_ILLGETYOU", VOLUME);
		break;
	case 1:
		SOUNDMANAGER->play("29_JUSTYOUWAIT", VOLUME);
		break;
	case 2:
		SOUNDMANAGER->play("32_OINUTTER", VOLUME);
		break;
	case 3:
		SOUNDMANAGER->play("43_YOULLREGRETTHAT", VOLUME);
		break;
	}
}

void PlayerManager::playNoWormDamaged()
{
	switch (RND->getInt(4))
	{
	case 0:
		SOUNDMANAGER->play("20_BORING", VOLUME);
		break;
	case 1:
		SOUNDMANAGER->play("21_BUMMER", VOLUME);
		break;
	case 2:
		SOUNDMANAGER->play("31_MISSED", VOLUME);
		break;
	case 3:
		SOUNDMANAGER->play("40_STUPID", VOLUME);
		break;
	}
}

void PlayerManager::playWormDyingSound()
{
	switch (RND->getInt(2))
	{
	case 0:
		SOUNDMANAGER->play("45_BYEBYE", VOLUME);
		break;
	case 1:
		SOUNDMANAGER->play("51_OHDEAR", VOLUME);
		break;
	}
}

void PlayerManager::endgame()
{
	//_ui->setCameraFocus();
	for (auto i : _vPlayer)
	{
		for (auto j : i->getWormVector())
		{
			WORM tmp = j->getWorm();
			tmp.img = IMAGEMANAGER->findImage("W_Win");
			j->setWorm(tmp);
		}
	}
	for (auto i : _vPlayer)
	{
		for (auto j : i->getWormVector())
		{
			WORM tmp = j->getWorm();
			if (tmp.state != WORMSTATE_DEAD)
			{
				_ui->setCameraFocus(PointMake(tmp.xPoint, tmp.yPoint));
				break;
			}
		}
	}
	if (!SOUNDMANAGER->isPlaySound("53_CrowdPart1"))
	{
		SOUNDMANAGER->play("53_CrowdPart1", VOLUME);
	}
	if (!SOUNDMANAGER->isPlaySound("54_CrowdPart2"))
	{
		SOUNDMANAGER->play("54_CrowdPart2", VOLUME);
	}
	if (_gameOverTiemr - TIMEMANAGER->getWorldTime() < 0)
	{
		SOUNDMANAGER->stop("53_CrowdPart1");
		SOUNDMANAGER->stop("54_CrowdPart2");
		SOUNDMANAGER->stop("04_bgm_4");
		SCENEMANAGER->changeScene("메뉴씬");
	}
}

void PlayerManager::playerStateChk()
{
	bool leftOnlyOneTeam = true;
	int howManyTeamLeft = 0;
	for (auto i : _vPlayer)
	{
		for (auto j : i->getWormVector())
		{
			if (j->getWorm().state != WORMSTATE_DEAD)
			{
				howManyTeamLeft++;
				break;
			}
		}
	}

	if (howManyTeamLeft <= 1)
	{
		if (!_isGameOver)
		{
			SOUNDMANAGER->play("49_VICTORY", VOLUME);
			_gameOverTiemr = TIMEMANAGER->getWorldTime() + 3;
		}
		_isGameOver = true;
	}
}