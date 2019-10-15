#include "stdafx.h"
#include "mainGame.h"

//���������� �����Ѵٸ� ������ 
HINSTANCE _hInstance;		//���� ������ȣ
HWND _hWnd;					//������
POINT _ptMouse;

LPTSTR _lpszClass = TEXT("Iota Team");


mainGame _mg;


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void setWindowsSize(int x, int y, int width, int height);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int cmdShow)
{
	MSG message;			//�޼���
	WNDCLASS wndClass;		//������ ������ ���� ����ü

	//Salt Bae 
	_hInstance = hInstance;

	wndClass.cbClsExtra = 0;										//Ŭ���� ���� �޸�
	wndClass.cbWndExtra = 0;										//������ ���� �޸� 
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//������ ��׶��� 
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);					//������ Ŀ��
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);				//������ ������
	wndClass.hInstance = hInstance;									//������ �ν��Ͻ� ��ȣ
	wndClass.lpfnWndProc = (WNDPROC)WndProc;						//������ ���ν���
	wndClass.lpszClassName = _lpszClass;							//������ Ŭ���� �̸�
	wndClass.lpszMenuName = NULL;									//������ �޴� �̸�
	wndClass.style = CS_HREDRAW | CS_VREDRAW;						//������ â ��Ÿ��

	//������ ���� ���
	RegisterClass(&wndClass);

	//������ â ��������
	_hWnd = CreateWindow(
		WINNAME,
		WINNAME,
		WS_OVERLAPPEDWINDOW,		//������ â ��Ÿ��
		WINSTARTX,					//������ ���� ��ǥ X
		WINSTARTY,					//������ ���� ��ǥ Y
		WINSIZEX,					//������ â ����ũ��
		WINSIZEY,					//������ â ����ũ��
		NULL,						//�θ� ������ ��뿩��
		(HMENU)NULL,				//�޴� ��뿩��
		hInstance,					//�ν��Ͻ�
		NULL);						//�ڽ� ������ ��뿩��

	setWindowsSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);

	//������ â�� ����Ϳ� �����
	ShowWindow(_hWnd, cmdShow);

	if (FAILED(_mg.init()))
	{
		return 0;
	}

	//GetMessage : �޽��� ������ ������ �׶� ����
	//PeekMessage : �޽��� ������ ������ ���� ������ ����(��� ������������)

	while (true)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT) break;
			TranslateMessage(&message);	//�Է��� ������ ���� �� �޽��� ó�� ���
			DispatchMessage(&message);	//������ �����쿡 �� �޽��� ����
		}
		else
		{
			TIMEMANAGER->update(60.0f);
			_mg.update();
			_mg.render();
		}
	}

	/* �׵��� ��������� �������� ��������
	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);	//�Է��� ������ ���� �� �޽��� ó�� ���
		DispatchMessage(&message);	//������ �����쿡 �� �޽��� ����
	}
	*/
	_mg.release();

	return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return _mg.MainProc(hWnd, iMessage, wParam, lParam);
}

void setWindowsSize(int x, int y, int width, int height)
{
	RECT winRect;
	
	winRect.left = 0;
	winRect.top = 0;
	winRect.right = width;
	winRect.bottom = height;

	AdjustWindowRect(&winRect, WINSTYLE, false);

	SetWindowPos(_hWnd, NULL, x, y, (winRect.right - winRect.left),
		(winRect.bottom - winRect.top), SWP_NOZORDER | SWP_NOMOVE);

}
