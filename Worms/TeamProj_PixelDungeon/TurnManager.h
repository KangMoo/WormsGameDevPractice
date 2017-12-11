#pragma once
#include "gameNode.h"

class TurnManager
{
private:

public:

	HRESULT init();
	void release();
	void update();
	void render();

	TurnManager();
	~TurnManager();
};

