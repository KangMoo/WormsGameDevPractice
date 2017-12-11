#include "stdafx.h"
#include "Map.h"
#include "UI.h"

Map::Map()
{
}


Map::~Map()
{
}

HRESULT Map::init()
{
	_map = IMAGEMANAGER->addImage("Map_1", "Img\\Map\\1.bmp", 1920, 696, true, RGB(255, 0, 255));
	_camera = _ui->getCameraPointer();
	return S_OK;
}
void Map::release()
{

}
void Map::update() 
{

}
void Map::render() 
{
	
	draw();
}
void Map::draw()
{
	IMAGEMANAGER->render("Map_1", getMemDC(), _camera->x, _camera->y);
}