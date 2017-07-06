#pragma once
#include "animation.h"

//===================================================
// 17. 04. 21 ## image Class ##
//===================================================


class image
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE,			//리소스로 부터
		LOAD_FILE,				//파일로 부터
		LOAD_EMPTY,
		LOAD_END
	};

	typedef struct tagImageInfo
	{
		DWORD resID;
		HDC hMemDC;
		HBITMAP hBit;
		HBITMAP hOBit;
		float x;
		float y;
		int width;
		int height;
		int currentFrameX;	//프레임 이미지 번호(가로)
		int currentFrameY;	//프레임 이미지 번호(세로)
		int maxFrameX;		//프레임의 끝 번호(가로)
		int maxFrameY;		//프레임의 끝 번호(세로)
		int frameWidth;		//프레임 이미지 한장당 가로크기
		int frameHeight;	//프레임 이미지 한장당 세로크기
		BYTE loadType;

		tagImageInfo()
		{
			resID			= 0;
			hMemDC			= NULL;
			hBit			= NULL;
			hOBit			= NULL;
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
	LPIMAGE_INFO	_imageInfo;		//이미지 구조체
	CHAR*			_fileName;		//파일이름
	BOOL			_trans;			//특정 칼라 날릴꺼니?
	COLORREF		_transColor;	//날린다면 어떤 칼라를 날릴꺼니?(픽셀값)

	BLENDFUNCTION	_blendFunc;
	LPIMAGE_INFO	_blendImage;

public:
	image();
	~image();

	HRESULT init(int width, int height);
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

	//					뿌릴곳 X     뿌릴곳 Y
	void render(HDC hdc, int destX, int destY);

	//					   뿌릴 곳X  뿌릴 곳Y    뿌려올 곳X  뿌려올 곳Y   그지점에서 가로  세로
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	void loopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY);

	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	void aniRender(HDC hdc, int destX, int destY, animation* ani);
	
	inline HDC getMemDC(void) { return _imageInfo->hMemDC; }

	//=========================================================
	// 이미지 조작을 편하게 하기위한 접근,설정자
	//=========================================================

	inline void setX(float x) { _imageInfo->x = x; }
	inline float getX(void) { return _imageInfo->x; }

	inline void setY(float y) { _imageInfo->y = y; }
	inline float getY(void) { return _imageInfo->y; }

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
		if (frameX > _imageInfo->maxFrameX) _imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}

	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY) _imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	inline int getWidth(void) { return _imageInfo->width; }
	inline int getHeight(void) { return _imageInfo->height; }

	inline int getMaxFrameX(void) { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY(void) { return _imageInfo->maxFrameY; }

	inline int getFrameX(void) { return _imageInfo->currentFrameX; }
	inline int getFrameY(void) { return _imageInfo->currentFrameY; }

	inline int getFrameWidth(void) { return _imageInfo->frameWidth; }
	inline int getFrameHeight(void) { return _imageInfo->frameHeight; }

};

