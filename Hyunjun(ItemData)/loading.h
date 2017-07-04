#pragma once
#include "gameNode.h"


enum LOAD_KIND
{ 
	LOAD_KIND_IMAGE_0,
	LOAD_KIND_IMAGE_1,
	LOAD_KIND_IMAGE_2,
	LOAD_KIND_FRAMEIMAGE_0,
	LOAD_KIND_FRAMEIMAGE_1,
	LOAD_KIND_SOUND,
	LOAD_KIND_END
};

struct tagImageResource
{
	string keyName;
	const char* fileName;
	float x, y;
	int width, height;
	int frameX, frameY;
	bool trans;
	COLORREF transColor;
};
struct tagSoundResource
{
	string keyName;
	string fileName;
	bool bgm, loop;


};

class loadItem
{
private:
	LOAD_KIND _kind;
	tagImageResource _imageResource;
	tagSoundResource _soundResource;


public:
	HRESULT initForImage(string keyName, int width, int height);
	HRESULT initForImage(string keyName, const char* fileName, int width, int height,
		BOOL trans = FALSE, COLORREF transColor = FALSE);
	HRESULT initForImage(string keyName, const char* fileName, float x, float y, int width, int height,
		BOOL trans = FALSE, COLORREF transColor = FALSE);

	HRESULT initForFrameImage(string keyName, const char* fileName, int width, int height,
		int frameX, int frameY, BOOL trans = FALSE, COLORREF transColor = FALSE);

	HRESULT initForFrameImage(string keyName, const char* fileName, float x, float y, int width, int height,
		int frameX, int frameY, BOOL trans = FALSE, COLORREF transColor = FALSE);

	HRESULT initForSound(string keyName, string fileName, BOOL bgm = FALSE, BOOL loop = FALSE);

	LOAD_KIND getLoadingKind(void) { return _kind; }

	tagImageResource getImageResource(void) { return _imageResource; }
	tagSoundResource getSoundResource(void) { return _soundResource; }

	loadItem();
	~loadItem();
};

class loading : public gameNode
{
private:
	typedef vector<loadItem*> arrLoadItem;
	typedef vector<loadItem*>::iterator arrLoadItemIter;

private:
	arrLoadItem		_vLoadItem;

	image*			_background;
	animation*		_loadingbackground;
	

	int				_currentGauge;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void loadImage(string keyName, int width, int height);
	void loadImage(string keyName, const char* fileName, int width, int height, BOOL trans = FALSE, COLORREF transColor = FALSE);
	void loadImage(string keyName, const char* fileName, float x, float y, int width, int height, BOOL trans = FALSE, COLORREF transColor = FALSE);
	void loadFrameImage(string keyName, const char* fileName, int width, int height, int frameX, int frameY, BOOL trans = FALSE, COLORREF transColor = FALSE);
	void loadFrameImage(string keyName, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans = FALSE, COLORREF transColor = FALSE);
	void loadsound(string keyName, string fileName, BOOL bgm = FALSE, BOOL loop = FALSE);

	BOOL loadingDone();

	vector<loadItem*> getLoadItem() { return _vLoadItem; }

	loading();
	~loading();
};

