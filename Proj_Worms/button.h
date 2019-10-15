#pragma once
#include "gameNode.h"

//�ݹ��Լ� �Լ�������
typedef void(*CALLBACK_FUNCTION)(void);

//<Functional>
//�� ���̺귯��	std::Function
//				std::move
//				std::bind
//�Ϲ� �������, ������� ���� �����ϰ� ��
//����) �ǿܷ� ����� ����

//�ݹ��Լ��� �������Ѻ��ÿ� 

enum BUTTONDIRECTION
{
	BUTTONDIRECTION_NULL,
	BUTTONDIRECTION_UP,
	BUTTONDIRECTION_DOWN
};

class button : public gameNode
{
private:
	BUTTONDIRECTION _direction;		//��ư �̳�

	const char* _imageName;			//��ư �̹��� �̸�
	image* _image;					//��ư �̹���
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

