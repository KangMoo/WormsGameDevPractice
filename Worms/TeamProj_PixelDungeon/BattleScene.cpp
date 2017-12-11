#include "stdafx.h"
#include "BattleScene.h"

BattleScene::BattleScene()
{
}


BattleScene::~BattleScene()
{

}

HRESULT BattleScene::init()
{
	_map = new Map;
	_player = new Player;
	_ui = new UI;
	_weapon = new Weapon;

	_player->setMapAdressLink(_map);
	_player->setUIAdressLink(_ui);

	_map->setUIAddressLink(_ui);

	_ui->getMapAddressLink(_map);

	_map->init();
	_player->init();
	_ui->init();
	_weapon->init();


	return S_OK;
}
void BattleScene::release()
{

}
void BattleScene::update() 
{
	_map->update();
	_player->update();
	_weapon->update();
	_ui->update();


}
void BattleScene::render() 
{
	_map->render();
	_player->render();
	_weapon->render();
	_ui->render();
}