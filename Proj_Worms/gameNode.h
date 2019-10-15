#pragma once
#include "image.h"
#include "WormsInfo.h"
//�� ��Ʈ�� ���� ����� ����
static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);

class gameNode
{
private:
	HDC _hdc;
	bool _managerInit;

public:
	virtual HRESULT init(void);	//�ʱ�ȭ
	virtual HRESULT init(bool managerInit);
	virtual void release(void);	//�޸� ����
	virtual void update(void);	//�������(Ÿ�̸�)
	virtual void render(void);	//�׷��ִ� �Լ�

	image* getBackBuffer(void) { return _backBuffer; }

	HDC getMemDC() { return _backBuffer->getMemDC(); }
	HDC getHDC() { return _hdc; }

	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);

	gameNode();
	virtual ~gameNode();
};

