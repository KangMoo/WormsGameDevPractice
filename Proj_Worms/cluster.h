#pragma once
#include "Weapon.h"
class cluster : public Weapon
{
private:
	POINT * _camera;
public:
	cluster();
	~cluster();
};

