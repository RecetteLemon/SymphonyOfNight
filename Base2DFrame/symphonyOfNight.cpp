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



}

//���Ⱑ �׷��ִ� ��
void symphonyOfNight::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==============================================================================
	
	
	
	//================================================================================
	//�ǵ������� �̰ŵ�
	TIMEMANAGER->render(getMemDC());
	this->getBackBuffer()->render(getHDC(), 0, 0);

}
