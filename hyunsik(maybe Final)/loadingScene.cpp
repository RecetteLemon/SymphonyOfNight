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
	this->addEffect();

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
		EFFECTMANAGER->addEffect("one_Hand_Effect", "one_hand", 1100, 100, 100, 100, 30, 1.0f / 60.0f, 5);
		EFFECTMANAGER->addEffect("dagger_Effect", "dagger", 200, 100, 100, 100, 30, 1.0f / 60.0f, 5);
		EFFECTMANAGER->addEffect("boss_Effect", "boss", 600, 600, 120, 600, 30, 1.0f / 60.0f, 5);
		EFFECTMANAGER->addEffect("die", "object_broken", 156, 42, 39, 42, 16, 1.0f / 60.0f, 5);

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
	_loading->loadImage("InventoryUI", "Image/Inventory/InventoryUI.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_loading->loadImage("PixelTest", "Image/pixelTest.bmp", 800, 800, false, RGB(255, 0, 255));
	_loading->loadImage("실험맵", "Image/Map3_C.bmp", 512, 1231, true, RGB(255, 0, 255));
	_loading->loadImage("characterBackground", "Image/character/CharacterUI.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("familiarBackground", "Image/character/familiarUI.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("character_select", "Image/character/Char_Select.bmp", 103, 48, true, RGB(255, 0, 255));
	_loading->loadImage("fmiliar_select", "Image/character/fmiliar_Selcect.bmp", 270, 80, true, RGB(255, 0, 255));
;	_loading->loadImage("invenfont", "image/character/CharacterUI_inven.bmp", 104, 44, true, RGB(255, 0, 255));
	_loading->loadImage("familiarfont", "image/character/CharacterUI_familiar.bmp", 102, 44, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Start", "Image/Loading/Start.bmp", 712, 21, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("호석", "Image/enemy/hosuk.bmp", 630, 129, 9, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("one_hand", "Image/effect/one_hand.bmp", 1100, 100, 11, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("dagger", "Image/effect/dagger.bmp", 200, 100, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("boss", "Image/effect/bossEffect.bmp", 600, 600, 5, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("object_broken", "Image/object/object_broken1.bmp", 156, 42, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("familiarDemon", "Image/familiar/familiar_demon.bmp", 640, 672, 5, 7, true, RGB(255, 0, 255));
	_loading->loadFrameImage("familiarFairy", "Image/familiar/familiar_fairy.bmp", 256, 512, 4, 8, true, RGB(255, 0, 255));
	_loading->loadFrameImage("familiarGhost", "Image/familiar/familiar_ghost.bmp", 256, 256, 4, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("familiarSceneDemon", "Image/familiar/familiarScene_demon.bmp", 256, 48, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("familiarSceneFairy", "Image/familiar/familiarScene_fairy.bmp", 128, 32, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("familiarSceneGhost", "Image/familiar/familiarScene_ghost.bmp", 128, 32, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("on_off", "Image/familiar/on_off.bmp", 400, 50, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("on_off1", "Image/familiar/on_off1.bmp", 400, 50, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("on_off2", "Image/familiar/on_off2.bmp", 400, 50, 2, 1, true, RGB(255, 0, 255));
	this->addItemImage();
	
	
}
void loadingScene::loadingSound()
{
	//사운드추가
	_loading->loadsound("TitleSound", "Sound/titleSound.mp3", true, true);
}

void loadingScene::addItemImage()
{
	

}
void loadingScene::addEffect()
{
	
		
}
