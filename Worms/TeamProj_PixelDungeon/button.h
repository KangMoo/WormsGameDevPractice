#pragma once
#include "gameNode.h"

//콜백함수 함수포인터
typedef void(*CALLBACK_FUNCTION)(void);

//<Functional>
//이 라이브러리	std::Function
//				std::move
//				std::bind
//일반 멤버변수, 멤버변수 참조 가능하게 됨
//함정) 의외로 쉬운게 함정

//콜백함수를 변형시켜보시요 

enum BUTTONDIRECTION
{
	BUTTONDIRECTION_NULL,
	BUTTONDIRECTION_UP,
	BUTTONDIRECTION_DOWN
};

class button : public gameNode
{
private:
	BUTTONDIRECTION _direction;		//버튼 이넘

	const char* _imageName;			//버튼 이미지 이름
	image* _image;					//버튼 이미지
	RECT _rc;
	float _x, _y;

	POINT _btnDownFramePoint;
	POINT _btnUpFramePoint;

	CALLBACK_FUNCTION _callbackFunction;

public:
	HRESULT init(const char* imageName, int x, int y,
		POINT btnDownFramePoint, POINT btnUpFramePoint,
		CALLBACK_FUNCTION cbFunction);
	void release(void);
	void update(void);
	void render(void);



	button();
	~button();
};

