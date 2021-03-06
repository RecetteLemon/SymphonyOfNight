#include "stdafx.h"
#include "loadingScene.h"


loadingScene::loadingScene()
{
}


loadingScene::~loadingScene()
{
}


HRESULT loadingScene::init()
{
	_loading = new loading;
	_loading->init();

	this->loadingImage();
	this->loadingSound();

	

	return S_OK;
}
void loadingScene::release()
{
	_loading->release();
	safeDelete(_loading);
}
void loadingScene::update()	
{
	_loading->update();

	if (_loading->loadingDone())
	{
		ITEM->init();
		EFFECTMANAGER->addEffect("ObjBroken", "ObjectBroken", 208, 56, 52, 56, 10, 1.0f / 60.0f, 10);
		SCENEMANAGER->changeScene("TitleScene");
	}
}
void loadingScene::render()	
{
	_loading->render();
	
}


void loadingScene::loadingImage()
{
	

	_loading->loadImage("TitleBackground", "Image/Loading/titleBackground.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Start", "Image/Loading/Start.bmp", 712, 21, 2, 1, true, RGB(255, 0, 255));
	_loading->loadImage("InventoryUI", "Image/Inventory/InventoryUI.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("ItemSelect", "Image/Inventory/ItemSelect.bmp", 300, 36, true, RGB(255, 0, 255));
	

	// 오브젝트

	_loading->loadFrameImage("Object1", "Image/Object/Object1.bmp", 32, 64, 1, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Object2", "Image/Object/Object2.bmp", 60, 28, 3, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Object3", "Image/Object/Object3.bmp", 140, 32, 5, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("ObjectBroken", "Image/Object/ObjectBroken.bmp", 208, 56, 4, 1, true, RGB(255, 0, 255));
	_loading->loadImage("PixelTest", "Image/pixelTest.bmp", 800, 800, false, RGB(255, 0, 255));
	this->addItemImage();
	
}
void loadingScene::loadingSound()
{
	//사운드추가
	
	_loading->loadsound("TitleSound", "Sound/titleSound.mp3", true, true);
}



void loadingScene::addItemImage()
{
	_loading->loadFrameImage("Heart","Image/Item/heart.bmp",			154, 12, 11, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Gold","Image/Item/gold.bmp",				20, 20, 1, 1, true, RGB(255, 0, 255));
	_loading->loadImage("바제랄드",	"Image/Item/dagger1.bmp",			25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("숏소드", "Image/Item/dagger2.bmp",				25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("레이피어", "Image/Item/dagger3.bmp",			25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("쥬엘소드", "Image/Item/dagger4.bmp",			25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("컴뱃나이프", "Image/Item/dagger5.bmp",			25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("틸핑", "Image/Item/OneHand_Sword1.bmp",			25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("그라디우스", "Image/Item/OneHand_Sword2.bmp",	25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("세이버", "Image/Item/OneHand_Sword3.bmp",		25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("하루파", "Image/Item/OneHand_Sword4.bmp",		25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("발만웨", "Image/Item/OneHand_Sword5.bmp",		25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("녹슨검", "Image/Item/TwoHand_Sword1.bmp",		25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("요도무라마사", "Image/Item/TwoHand_Sword2.bmp", 25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("타케미츠", "Image/Item/TwoHand_Sword3.bmp",		25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("야스츠나", "Image/Item/TwoHand_Sword4.bmp",		25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("마사무네", "Image/Item/TwoHand_Sword5.bmp",		25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("실버티아라", "Image/Item/helmet1.bmp",			25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("석가면", "Image/Item/helmet2.bmp",				25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("은빛서클렛", "Image/Item/helmet3.bmp",			25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("성스러운안경", "Image/Item/helmet4.bmp",			25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("펠트의모자", "Image/Item/helmet5.bmp",			25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("미러큐이러스", "Image/Item/armor1.bmp",			25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("실버체스트", "Image/Item/armor2.bmp",			25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("골드체스트", "Image/Item/armor3.bmp",			25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("다이아블래스트", "Image/Item/armor4.bmp",		25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("플레티넘체스트", "Image/Item/armor5.bmp",		25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("킹스톤", "Image/Item/accessory1.bmp",			25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("넥클레스", "Image/Item/accessory2.bmp",			25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("진주반지", "Image/Item/accessory3.bmp",			25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("마스터부츠", "Image/Item/accessory4.bmp",		25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("플레티넘부츠", "Image/Item/accessory5.bmp",		25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("리버서블망토", "Image/Item/accessory6.bmp",		25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("피로물든망토", "Image/Item/accessory7.bmp",		25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("엘프망토", "Image/Item/accessory8.bmp",			25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("블루망토", "Image/Item/accessory9.bmp",			25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("오더메이드", "Image/Item/accessory10.bmp",		25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("고기", "Image/Item/food1.bmp",					25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("버섯", "Image/Item/food2.bmp",					25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("소주", "Image/Item/food3.bmp",					25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("스파게티", "Image/Item/food4.bmp",				25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("바베큐", "Image/Item/food5.bmp",				25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("파란포션", "Image/Item/potion1.bmp",			25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("초록포션", "Image/Item/potion2.bmp",			25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("주황포션", "Image/Item/potion3.bmp",			25, 25, true, RGB(255, 0, 255));
}