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
	_map = IMAGEMANAGER->findImage("Map_1");
	_map2 = IMAGEMANAGER->findImage("Map_2");
	_map3 = IMAGEMANAGER->findImage("Map_3");
	_bg = IMAGEMANAGER->findImage("bg");
	_camera = _ui->getCameraPointer();
	_blue = IMAGEMANAGER->findImage("blue");
	//_waterHeight = _map->getHeight() - 500;
	for (int i = 0; i < 6; i++)
	{
		tagWaterwaveInfo tmp;
		tmp.yFrame = RND->getInt(12);
		tmp.xPoint = RND->getInt(100) - 150;
		_vWaterInfo.push_back(tmp);
	}
	_waterHeight = 2000 - 360;
	//waterHeightInit();
	return S_OK;
}
void Map::release()
{

}
void Map::update()
{
	//test~
	frameUpdate();
	graveCtrl();
	//~test
}
void Map::render()
{
	draw();
	
}
void Map::draw()
{
	_bg->render(getMemDC(), 300 - _bg->getWidth() / 2 + int(_camera->x / 2), +int(_camera->y / 2));
	_blue->render(getMemDC(), 0, _waterHeight + _camera->y - IMAGEMANAGER->findImage("waterwave")->getFrameHeight() - 50);
	for (int i = 0; i < 2; i++)
	{
		IMAGEMANAGER->frameRender("waterwave", getMemDC(), _vWaterInfo[i].xPoint + _camera->x, _waterHeight + _camera->y - IMAGEMANAGER->findImage("waterwave")->getFrameHeight() + (i - 3) * 20, 0, _vWaterInfo[i].yFrame);
	}
	_map3->render(getMemDC(), _camera->x, _camera->y);
	drawGrave();
	_map->render(getMemDC(), _camera->x, _camera->y);
	_map2->render(getMemDC(), _camera->x, _camera->y);
	_blue->render(getMemDC(), 0, _waterHeight + _camera->y - IMAGEMANAGER->findImage("waterwave")->getFrameHeight());
	for (int i = 2; i < _vWaterInfo.size(); i++)
	{
		IMAGEMANAGER->frameRender("waterwave", getMemDC(), _vWaterInfo[i].xPoint + _camera->x, _waterHeight + _camera->y - IMAGEMANAGER->findImage("waterwave")->getFrameHeight() + (i - 3) * 20, 0, _vWaterInfo[i].yFrame);
	}
	//_waterwave->frameRender(getMemDC(), 0 + _camera->x, _waterHeight + _camera->y);
}

void Map::frameUpdate()
{
	if (TIMEMANAGER->getWorldTime() - _frametimer < 0.1) return;

	for (int i = 0; i < _vWaterInfo.size(); i++)
	{

		if (_vWaterInfo[i].yFrame < IMAGEMANAGER->findImage("waterwave")->getMaxFrameY())
		{
			_vWaterInfo[i].yFrame++;
		}
		else
		{
			_vWaterInfo[i].yFrame = RND->getInt(2);
		}


		if (-150 <= _vWaterInfo[i].xPoint && _vWaterInfo[i].xPoint < -10)
		{
			_vWaterInfo[i].xPoint += RND->getInt(3) - 1;
		}

	}

	for (int i = 0; i < _vGrave.size(); i++)
	{
		if (_vGrave[i].currentFrameY < _vGrave[i].img->getMaxFrameY())
		{
			_vGrave[i].currentFrameY++;
		}
		else
		{
			_vGrave[i].currentFrameY = 0;
		}
	}

	_frametimer = TIMEMANAGER->getWorldTime();
}
void Map::waterHeightInit()
{
	int width = _map->getWidth();
	int height = _map->getHeight();


	for (int i = 0; i < height; i += 100)
	{
		for (int j = 0; j < width; j++)
		{
			if (GetPixel(_map->getMemDC(), j, i) != RGB(255, 0, 255))
			{
				_waterHeight = i;
				break;
			}
		}
	}
}
void Map::eraseMap(POINT p, float size)
{
	_map->eraseEllipse(_map->getMemDC(), p, size, size);
	_map2->eraseEllipse(_map2->getMemDC(), p, size + 10, size + 10);
	_map3->eraseEllipse(_map3->getMemDC(), p, size - size / 3, size - size / 3);

}
void Map::drawGrave()
{
	for (auto i : _vGrave)
	{
		i.img->frameRender(getMemDC(), i.xPoint + _camera->x - i.img->getFrameWidth()/2, i.yPoint + _camera->y - i.img->getFrameHeight()/2 - 5, i.currentFrameX, i.currentFrameY);
	}
}
void Map::addgrave(POINT p, image* graveImg)
{
	tagGrave tmp;
	tmp.img = graveImg;
	tmp.xPoint = p.x;
	tmp.yPoint = p.y;
	tmp.ySpeed = -5;
	tmp.currentFrameX = 0;
	tmp.currentFrameY = 0;
	_vGrave.push_back(tmp);
}

void Map::graveCtrl()
{
	//面倒 魄沥 贸府
	for (int a = 0; a < _vGrave.size(); a++)
	{
		tagGrave i = _vGrave[a];
		i.rc = RectMakeCenter(i.xPoint, i.yPoint, 5, WORMYSIZE );
		//rc.bot & map面倒
		if (GetPixel(_map->getMemDC(), i.xPoint, i.rc.bottom) != RGB(255, 0, 255))
		{
			while (GetPixel(_map->getMemDC(), i.xPoint, i.rc.bottom) != RGB(255, 0, 255))
			{
				i.yPoint--;
				i.rc = RectMakeCenter(i.xPoint, i.yPoint, 5, WORMYSIZE );
			}
			i.ySpeed = 0;
			
		}

		else if (GetPixel(_map->getMemDC(), i.xPoint, i.rc.top) != RGB(255, 0, 255))
		{
			while (GetPixel(_map->getMemDC(), i.xPoint, i.rc.top) != RGB(255, 0, 255))
			{
				i.yPoint++;
				i.rc = RectMakeCenter(i.xPoint, i.yPoint, 5, WORMYSIZE );

			}
			if (i.ySpeed < 0)
			{
				i.ySpeed = -i.ySpeed;
			}
		}
		if (GetPixel(_map->getMemDC(), i.xPoint, i.rc.bottom+1) != RGB(255, 0, 255))
		{
			i.ySpeed = 0;
		}
		i.rc = RectMakeCenter(i.xPoint, i.yPoint, 5, WORMYSIZE);
		_vGrave[a] = i;
	}


	//框流烙 贸府
	for (int i = 0; i < _vGrave.size(); i++)
	{
		_vGrave[i].yPoint += _vGrave[i].ySpeed;
		_vGrave[i].ySpeed += 0.2;
	}

}