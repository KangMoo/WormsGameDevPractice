#pragma once
#include "animation.h"

//==================================
// ## 2017.08.22 ## image Class ##
//==================================

class image
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE,		//리소스로부터
		LOAD_FILE,			//파일로부터
		LOAD_EMPTY,			//빈 비트맵 파일
		LOAD_END
	};

	typedef struct tagImageInfo
	{
		DWORD resID;		//리소스로부터 정보를 가져올땐 등록된 아이디로부터 가져오는데 그때 쓰임
		HDC hMemDC;			//메모리 DC (DC영역의 메모리(픽셀값등이 있음))
		HBITMAP hBit;		//비트맵
		HBITMAP hOBit;		//올드 비트맵(SelectObject)
		float	x;				//시작좌표 X
		float	y;				//시작좌표 Y
		int		width;			//가로 사이즈
		int		height;			//세로 사이즈
		int		currentFrameX;	//현재 프레임 번호 X
		int		currentFrameY;	//현재 프레임 번호 Y
		int		maxFrameX;		//맥스 프레임 X
		int		maxFrameY;		//맥스 프레임 Y
		int		frameWidth;		//프레임 한장 가로크기
		int		frameHeight;	//프레임 한장 세로크기
		BYTE	loadType;

		tagImageInfo()
		{
			resID			= 0;
			hMemDC			= NULL;
			hBit			= NULL;
			hOBit			= NULL;
			x				= 0;
			y				= 0;
			width			= 0;
			height			= 0;
			currentFrameX	= 0;
			currentFrameY	= 0;
			maxFrameX		= 0;
			maxFrameY		= 0;
			frameWidth		= 0;
			frameHeight		= 0;
			loadType		= LOAD_RESOURCE;
		}
	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO	_imageInfo;
	CHAR*			_fileName;
	BOOL			_trans;
	COLORREF		_transColor;
	
	BLENDFUNCTION	_blendFunc;
	LPIMAGE_INFO	_blendImage;

public:
	image();
	~image();

	//빈 비트맵 이미지 초기화
	HRESULT init(int width, int height, BOOL trans = FALSE, COLORREF transColor = FALSE);
	//파일로부터 이미지 초기화
	HRESULT init(const char* fileName, int width, int height,
		BOOL trans = FALSE, COLORREF transColor = FALSE);

	HRESULT init(const char* fileName, float x, float y, int width, int height,
		BOOL trans = FALSE, COLORREF transColor = FALSE);

	HRESULT init(const char* fileName, float x, float y, int width, int height,
		int frameX, int frameY, BOOL trans, COLORREF transColor);

	HRESULT init(const char* fileName, int width, int height,
		int frameX, int frameY, BOOL trans, COLORREF transColor);

	void release(void);

	void setTransColor(BOOL trans, COLORREF transColor);

	void render(HDC hdc);

	//이미지 렌더, DC영역, 뿌릴좌표X, 뿌릴좌표Y
	void render(HDC hdc, int destX, int destY);
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);
	
	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);
	void alphaFrameRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);

	void loopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY);

	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	void aniRender(HDC hdc, int destX, int destY, animation* ani);

	//메모리 디씨 접근자
	inline HDC getMemDC() { return _imageInfo->hMemDC; }

	//=============================================================
	// 이미지 조작을 쉽게하기 위한 getter, setter
	//=============================================================

	inline void setX(float x) { _imageInfo->x = x; }
	inline float getX() { return _imageInfo->x; }

	inline void setY(float y) { _imageInfo->y = y; }
	inline float getY() { return _imageInfo->y; }

	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	inline float getCenterX()
	{
		return _imageInfo->maxFrameX <= 0 ? _imageInfo->x + (_imageInfo->width / 2) :
			_imageInfo->x + (_imageInfo->frameWidth / 2);
	}

	inline float getCenterY()
	{
		return _imageInfo->maxFrameY <= 0 ? _imageInfo->y + (_imageInfo->height / 2) :
			_imageInfo->y + (_imageInfo->frameHeight / 2);
	}


	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (_imageInfo->maxFrameX < frameX) _imageInfo->maxFrameX = frameX;
	}

	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (_imageInfo->maxFrameY < frameY) _imageInfo->maxFrameY = frameY;
	}

	inline int getMaxFrameX(void) { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY(void) { return _imageInfo->maxFrameY; }

	inline int getFrameX(void) { return _imageInfo->currentFrameX; }
	inline int getFrameY(void) { return _imageInfo->currentFrameY; }

	inline int getFrameWidth(void) { return _imageInfo->frameWidth; }
	inline int getFrameHeight(void) { return _imageInfo->frameHeight; }

	inline int getWidth(void) {return _imageInfo->width; }
	inline int getHeight(void) {return _imageInfo->height; }
};

