#pragma once
#include "gameNode.h"

typedef void(*CALLBACK_FUNCTION)(void);

class action : public gameNode
{
private:
	image* _image;
	float _startX, _startY;
	float _endX, _endY;

	float _angle;
	float _travelRange;
	float _worldTimeCount;
	float _time;

	bool _isMoving;

	CALLBACK_FUNCTION _callbackFunction;

public:
	action();
	~action();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void moveTo(image* image, float endX, float endY, float time);
	void moveTo(image* image, float endX, float endY, float time, CALLBACK_FUNCTION cbFunction);

	void moving(void);

	bool getIsMoving(void) { return _isMoving; }
};

