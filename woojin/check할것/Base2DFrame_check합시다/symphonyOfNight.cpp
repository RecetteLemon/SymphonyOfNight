#include "stdafx.h"
#include "symphonyOfNight.h"


symphonyOfNight::symphonyOfNight()
{
}


symphonyOfNight::~symphonyOfNight()
{
}

//�ʱ�ȭ ���ִ� �Լ�
HRESULT symphonyOfNight::init(void)
{
	gameNode::init(true);

	//SCENEMANAGER->addScene("�׽�Ʈ��", new testScene);
	SCENEMANAGER->addScene("��Ʈ��", new openingScene);
	SCENEMANAGER->addScene("��1", new Scene_Map1);

	SCENEMANAGER->changeScene("��Ʈ��");

	return S_OK;
}

//�޸� ���� �Լ�
void symphonyOfNight::release(void)
{
	gameNode::release();

	

}

//�������ִ� ��
void symphonyOfNight::update(void)
{
	gameNode::update();

	SCENEMANAGER->update();

	
}

//���Ⱑ �׷��ִ� ��
void symphonyOfNight::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==============================================================================
	SetTextColor(getMemDC(), RGB(255, 255, 255));

	SCENEMANAGER->render();
	
	//================================================================================
	//�ǵ������� �̰ŵ�
	TIMEMANAGER->render(getMemDC());
	this->getBackBuffer()->render(getHDC(), 0, 0);

}
