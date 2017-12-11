#pragma once
#include "gameNode.h"

class Weapon : public gameNode
{
private:

public:
	HRESULT init();
	void release();
	void update();
	void render();

	Weapon();
	~Weapon();
};

