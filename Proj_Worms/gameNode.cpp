#include "stdafx.h"
#include "gameNode.h"


gameNode::gameNode()
{
}


gameNode::~gameNode()
{

}

HRESULT gameNode::init(void)
{
	_hdc = GetDC(_hWnd);
	_managerInit = false;

	return S_OK;
}

HRESULT gameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if (_managerInit)
	{
		//SetTimer(_hWnd, 1, 10, NULL);
		KEYMANAGER->init();
		IMAGEMANAGER->init();
		TXTDATA->init();
		TIMEMANAGER->init();
		SOUNDMANAGER->init();
		EFFECTMANAGER->init();
		SCENEMANAGER->init();
		KEYANIMANAGER->init();
		DATABASE->init();
	}

	return S_OK;
}

void gameNode::release(void)
{

	if (_managerInit)
	{
		//KillTimer(_hWnd, 1);
		KEYMANAGER->releaseSingleton();
		IMAGEMANAGER->releaseSingleton();
		TXTDATA->releaseSingleton();
		TIMEMANAGER->releaseSingleton();
		SOUNDMANAGER->releaseSingleton();
		EFFECTMANAGER->releaseSingleton();
		SCENEMANAGER->releaseSingleton();
		KEYANIMANAGER->releaseSingleton();
		DATABASE->releaseSingleton();
	}

	ReleaseDC(_hWnd, _hdc);

	
}

void gameNode::update(void)	
{
	//InvalidateRect(_hWnd, NULL, false);
}

void gameNode::render(void)
{

}


LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
		//윈도우 창이 켜질때만 실행이 되는 함수
		case WM_CREATE:

		break;
		//case WM_PAINT:
		//{
		//	hdc = BeginPaint(hWnd, &ps);
		//
		//	this->render();
		//
		//	EndPaint(hWnd, &ps);
		//}
		//break;
		//case WM_TIMER:
		//	this->update();
		//break;
		case WM_MBUTTONDOWN:
			
		break;
		case WM_LBUTTONDOWN:

		break;
		case WM_MOUSEMOVE:
			_ptMouse.x = static_cast<float>LOWORD(lParam);
			_ptMouse.y = static_cast<float>HIWORD(lParam);
		break;
		case WM_KEYDOWN:
			switch (wParam)
			{
				case VK_ESCAPE:
					PostMessage(hWnd, WM_DESTROY, 0, 0);
				break;
			}
		break;
		case WM_DESTROY:
		//윈도우 창 종료 함수
			PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
