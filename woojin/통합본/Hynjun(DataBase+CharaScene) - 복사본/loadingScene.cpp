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
		EFFECTMANAGER->addEffect("ObjBroken", "ObjectBroken", 208, 56, 52, 56, 12, 1.0f / 60.0f, 20);
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

	//character Scene
	_loading->loadImage("characterBackground", "Image/character/CharacterUI.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("character_select", "Image/character/Char_Select.bmp", 103, 48, true, RGB(255, 0, 255));
	_loading->loadImage("invenfont", "image/character/CharacterUI_inven.bmp", 104, 44, true, RGB(255, 0, 255));
	_loading->loadImage("familiarfont", "image/character/CharacterUI_familiar.bmp", 102, 44, true, RGB(255, 0, 255));

	//familiar Scene
	_loading->loadFrameImage("on_off", "Image/familiar/on_off.bmp", 400, 50, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("on_off1", "Image/familiar/on_off1.bmp", 400, 50, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("on_off2", "Image/familiar/on_off2.bmp", 400, 50, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("on_off3", "Image/familiar/on_off3.bmp", 400, 50, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("familiarSceneDemon", "Image/familiar/familiarScene_demon.bmp", 256, 48, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("familiarSceneFairy", "Image/familiar/familiarScene_fairy.bmp", 128, 32, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("familiarSceneGhost", "Image/familiar/familiarScene_ghost.bmp", 128, 32, 4, 1, true, RGB(255, 0, 255));
	_loading->loadImage("familiarBackground", "Image/character/familiarUI.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("fmiliar_select", "Image/character/fmiliar_Selcect.bmp", 270, 80, true, RGB(255, 0, 255));





	// ������Ʈ

	_loading->loadFrameImage("Object1", "Image/Object/Object1.bmp", 32, 64, 1, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Object2", "Image/Object/Object2.bmp", 60, 28, 3, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Object3", "Image/Object/Object3.bmp", 140, 32, 5, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("ObjectBroken", "Image/Object/ObjectBroken.bmp", 208, 56, 4, 1, true, RGB(255, 0, 255));
	_loading->loadImage("PixelTest", "Image/pixelTest.bmp", 800, 800, false, RGB(255, 0, 255));
	this->addItemImage();
	
}
void loadingScene::loadingSound()
{
	//�����߰�
	
	_loading->loadsound("TitleSound", "Sound/titleSound.mp3", true, true);
}



void loadingScene::addItemImage()
{
	_loading->loadFrameImage("Heart","Image/Item/heart.bmp",			154, 12, 11, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("Gold","Image/Item/gold.bmp",				20, 20, 1, 1, true, RGB(255, 0, 255));
	_loading->loadImage("��������",	"Image/Item/dagger1.bmp",			25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("���ҵ�", "Image/Item/dagger2.bmp",				25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("�����Ǿ�", "Image/Item/dagger3.bmp",			25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("�꿤�ҵ�", "Image/Item/dagger4.bmp",			25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("�Ĺ����", "Image/Item/dagger5.bmp",			25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("ƿ��", "Image/Item/OneHand_Sword1.bmp",			25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("�׶��콺", "Image/Item/OneHand_Sword2.bmp",	25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("���̹�", "Image/Item/OneHand_Sword3.bmp",		25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("�Ϸ���", "Image/Item/OneHand_Sword4.bmp",		25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("�߸���", "Image/Item/OneHand_Sword5.bmp",		25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("�콼��", "Image/Item/TwoHand_Sword1.bmp",		25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("�䵵���󸶻�", "Image/Item/TwoHand_Sword2.bmp", 25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("Ÿ�ɹ���", "Image/Item/TwoHand_Sword3.bmp",		25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("�߽�����", "Image/Item/TwoHand_Sword4.bmp",		25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("���繫��", "Image/Item/TwoHand_Sword5.bmp",		25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("�ǹ�Ƽ�ƶ�", "Image/Item/helmet1.bmp",			25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("������", "Image/Item/helmet2.bmp",				25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("������Ŭ��", "Image/Item/helmet3.bmp",			25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("��������Ȱ�", "Image/Item/helmet4.bmp",			25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("��Ʈ�Ǹ���", "Image/Item/helmet5.bmp",			25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("�̷�ť�̷���", "Image/Item/armor1.bmp",			25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("�ǹ�ü��Ʈ", "Image/Item/armor2.bmp",			25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("���ü��Ʈ", "Image/Item/armor3.bmp",			25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("���̾ƺ���Ʈ", "Image/Item/armor4.bmp",		25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("�÷�Ƽ��ü��Ʈ", "Image/Item/armor5.bmp",		25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("ŷ����", "Image/Item/accessory1.bmp",			25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("��Ŭ����", "Image/Item/accessory2.bmp",			25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("���ֹ���", "Image/Item/accessory3.bmp",			25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("�����ͺ���", "Image/Item/accessory4.bmp",		25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("�÷�Ƽ�Ѻ���", "Image/Item/accessory5.bmp",		25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("�����������", "Image/Item/accessory6.bmp",		25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("�Ƿι������", "Image/Item/accessory7.bmp",		25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("��������", "Image/Item/accessory8.bmp",			25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("������", "Image/Item/accessory9.bmp",			25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("�������̵�", "Image/Item/accessory10.bmp",		25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("���", "Image/Item/food1.bmp",					25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("����", "Image/Item/food2.bmp",					25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("����", "Image/Item/food3.bmp",					25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("���İ�Ƽ", "Image/Item/food4.bmp",				25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("�ٺ�ť", "Image/Item/food5.bmp",				25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("�Ķ�����", "Image/Item/potion1.bmp",			25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("�ʷ�����", "Image/Item/potion2.bmp",			25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("��Ȳ����", "Image/Item/potion3.bmp",			25, 25, true, RGB(255, 0, 255));
}