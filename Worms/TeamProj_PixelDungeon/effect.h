#pragma once
#include "gameNode.h"

class animation;

class effect : public gameNode
{
protected:
	int _x;
	int _y;

	image* _effectImage;
	animation* _effectAnimation;
	BOOL _isRunning;
	float _elapsedTime;

public:
	virtual HRESULT init(image* effectImage, int frameW, int frameH, int fps, float elapsedTime);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void startEffect(int x, int y);

	virtual void killEffect(void);

	BOOL getIsRunning(void) { return _isRunning; }
	

	effect();
	~effect();
};

