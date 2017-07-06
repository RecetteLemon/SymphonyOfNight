#include "stdafx.h"
#include "loading.h"

loadItem::loadItem(){}
loadItem::~loadItem(){}

HRESULT loadItem::initForImage(string keyName, int width, int height)
{
	_kind = LOAD_KIND_IMAGE_0;

	memset(&_imageResource, 0, sizeof(tagImageResource));

	_imageResource.keyName = keyName;
	_imageResource.width = width;
	_imageResource.height = height;

	return S_OK;
}

HRESULT loadItem::initForImage(string keyName, const char* fileName, int width, int height,
	BOOL trans, COLORREF transColor)
{
	_kind = LOAD_KIND_IMAGE_1;

	memset(&_imageResource, 0, sizeof(tagImageResource));

	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.trans = trans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::initForImage(string keyName, const char* fileName, float x, float y, int width, int height,
	BOOL trans, COLORREF transColor)
{
	_kind = LOAD_KIND_IMAGE_2;

	memset(&_imageResource, 0, sizeof(tagImageResource));

	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.trans = trans;
	_imageResource.transColor = transColor;

	return S_OK;
}


HRESULT loadItem::initForFrameImage(string keyName, const char* fileName, int width, int height,
	int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	_kind = LOAD_KIND_FRAMEIMAGE_0;

	memset(&_imageResource, 0, sizeof(tagImageResource));

	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	_imageResource.trans = trans;
	_imageResource.transColor = transColor;

	return S_OK;
}


HRESULT loadItem::initForFrameImage(string keyName, const char* fileName, float x, float y, int width, int height,
	int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	_kind = LOAD_KIND_FRAMEIMAGE_1;

	memset(&_imageResource, 0, sizeof(tagImageResource));

	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	_imageResource.trans = trans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::initForSound(string keyName, string fileName, BOOL bgm , BOOL loop )
{
	_kind = LOAD_KIND_SOUND;

	memset(&_soundResource, 0, sizeof(tagSoundResource));

	_soundResource.keyName = keyName;
	_soundResource.fileName = fileName;
	_soundResource.bgm = bgm;
	_soundResource.loop = loop;

	return S_OK;
}



loading::loading()
{
}


loading::~loading()
{

}

HRESULT loading::init()
{
	
	_background = IMAGEMANAGER->addFrameImage("LoadingBackground", "Image/Loading/LoadingBackground.bmp",23200, 600, 29, 1, true, RGB(255, 0, 255));
	

	_loadingbackground = new animation;
	_loadingbackground->init(_background->getWidth(), _background->getHeight(), _background->getFrameWidth(), _background->getFrameHeight());
	_loadingbackground->setDefPlayFrame(false, true);
	_loadingbackground->setFPS(1);
	_loadingbackground->start();

	
	_currentGauge = 0;
	
	return S_OK;
}

void loading::release()
{
	safeDelete(_loadingbackground);
	IMAGEMANAGER->deleteImage("LoadingBackground");
	_background = NULL;

	arrLoadItemIter iter = _vLoadItem.begin();

	for (; iter != _vLoadItem.end();)
	{
		safeDelete(*iter);
		iter = _vLoadItem.erase(iter);
	}

	_vLoadItem.clear();
}

void loading::update() 
{
	_loadingbackground->frameUpdate(TIMEMANAGER->getElapsedTime() * 20);
}

void loading::render() 
{
	_background->aniRender(getMemDC(), 0, 0, _loadingbackground);

}


void loading::loadImage(string keyName, int width, int height)
{
	loadItem* item = new loadItem;
	item->initForImage(keyName, width, height);

	_vLoadItem.push_back(item);
}

void loading::loadImage(string keyName, const char* fileName, int width, int height, BOOL trans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForImage(keyName, fileName, width, height, trans, transColor);

	_vLoadItem.push_back(item);
}

void loading::loadImage(string keyName, const char* fileName, float x, float y, int width, int height, BOOL trans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForImage(keyName, fileName, x, y, width, height, trans, transColor);

	_vLoadItem.push_back(item);
}

void loading::loadFrameImage(string keyName, const char* fileName, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForFrameImage(keyName, fileName, width, height, frameX, frameY, trans, transColor);

	_vLoadItem.push_back(item);
}

void loading::loadFrameImage(string keyName, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForFrameImage(keyName, fileName, x, y, width, height, frameX, frameY, trans, transColor);

	_vLoadItem.push_back(item);
}

void loading::loadsound(string keyName, string fileName, BOOL bgm, BOOL loop)
{
	loadItem* item = new loadItem;
	item->initForSound(keyName, fileName, bgm, loop);

	_vLoadItem.push_back(item);
}

//로딩하는 곳
BOOL loading::loadingDone()
{

	//로딩 게이지가 올라간다는 것은 메모리에 이미지, 사운드 등이 올라가고있고,
	//벡터사이즈보다 같거나 크다는 것은. 로딩이 끝났다는 걸 의미
	if (_currentGauge >= _vLoadItem.size())
	{
		return TRUE;
	}

	loadItem* item = _vLoadItem[_currentGauge];

	switch (item->getLoadingKind())
	{
		case LOAD_KIND_IMAGE_0:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addImage(img.keyName, img.width, img.height);
		}
		break;

		case LOAD_KIND_IMAGE_1:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addImage(img.keyName, img.fileName, img.width, img.height, img.trans, img.transColor);
		}
		break;

		case LOAD_KIND_IMAGE_2:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addImage(img.keyName, img.fileName, img.x, img.y, img.width, img.height, img.trans, img.transColor);
		}
		break;

		case LOAD_KIND_FRAMEIMAGE_0:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addFrameImage(img.keyName, img.fileName, img.width, img.height, img.frameX, img.frameY, img.trans, img.transColor);
		}
		break;

		case LOAD_KIND_FRAMEIMAGE_1:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addFrameImage(img.keyName, img.fileName, img.x, img.y, img.width, img.height, img.frameX, img.frameY, img.trans, img.transColor);
		}
		break;

		case LOAD_KIND_SOUND:
		{
			tagSoundResource sound = item->getSoundResource();
			SOUNDMANAGER->addSound(sound.keyName, sound.fileName, sound.bgm, sound.loop);
			
		}
		break;
	}


	_currentGauge++;


	return FALSE;
}
