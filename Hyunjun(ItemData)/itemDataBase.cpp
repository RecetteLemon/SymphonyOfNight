#include "stdafx.h"
#include "itemDataBase.h"


allItem::allItem()
{
}


allItem::~allItem()
{
}


HRESULT allItem::init()
{
	IMAGEMANAGER->addFrameImage("Heart", "Image/Item/heart.bmp", 154, 12, 11, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Gold", "Image/Item/gold.bmp", 20, 20, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��������", "Image/Item/dagger1.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���ҵ�", "Image/Item/dagger2.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�����Ǿ�", "Image/Item/dagger3.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�꿤�ҵ�", "Image/Item/dagger4.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�Ĺ����", "Image/Item/dagger5.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ƿ��", "Image/Item/OneHand_Sword1.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�׶��콺", "Image/Item/OneHand_Sword2.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���̹�", "Image/Item/OneHand_Sword3.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�Ϸ���", "Image/Item/OneHand_Sword4.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�߸���", "Image/Item/OneHand_Sword5.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�콼��", "Image/Item/TwoHand_Sword1.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�䵵���󸶻�", "Image/Item/TwoHand_Sword2.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Ÿ�ɹ���", "Image/Item/TwoHand_Sword3.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�߽�����", "Image/Item/TwoHand_Sword4.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���繫��", "Image/Item/TwoHand_Sword5.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ǹ�Ƽ�ƶ�", "Image/Item/helmet1.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������", "Image/Item/helmet2.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������Ŭ��", "Image/Item/helmet3.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��������Ȱ�", "Image/Item/helmet4.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��Ʈ�Ǹ���", "Image/Item/helmet5.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�̷�ť�̷���", "Image/Item/armor1.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ǹ�ü��Ʈ", "Image/Item/armor2.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���ü��Ʈ", "Image/Item/armor3.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���̾ƺ���Ʈ", "Image/Item/armor4.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�÷�Ƽ��ü��Ʈ", "Image/Item/armor5.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ŷ����", "Image/Item/accessory1.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��Ŭ����", "Image/Item/accessory2.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���ֹ���", "Image/Item/accessory3.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�����ͺ���", "Image/Item/accessory4.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�÷�Ƽ�Ѻ���", "Image/Item/accessory5.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�����������", "Image/Item/accessory6.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�Ƿι������", "Image/Item/accessory7.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��������", "Image/Item/accessory8.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������", "Image/Item/accessory9.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�������̵�", "Image/Item/accessory10.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���", "Image/Item/food1.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����", "Image/Item/food2.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����", "Image/Item/food3.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���İ�Ƽ", "Image/Item/food4.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ٺ�ť", "Image/Item/food5.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�Ķ�����", "Image/Item/potion1.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ʷ�����", "Image/Item/potion2.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��Ȳ����", "Image/Item/potion3.bmp", 20, 20, true, RGB(255, 0, 255));

	loadDatabase("All_item.txt");

	return S_OK;
}

//============================================================================�����Ҵ� ����ü ����Ʈ
void allItem::release()
{
	
	mIterEitem mIter;

	for (mIter = _mTotalEitem.begin(); mIter != _mTotalEitem.end();)
	{
		safeDelete(mIter->second);
		mIter = _mTotalEitem.erase(mIter);
	}	
}


//============================================================================�����ͷε�
//= ���� ���� �����ٸ� txtData�� �ε嵥������ ���۷��� �÷����� =
//============================================================================
void allItem::loadDatabase(string name)
{
	//�����͸� �о����
	arrEitem vTemp;
	vTemp = TXTDATA->txtLoad(name.c_str());

	string str;
	int count = 0;

	//ĭ���� | �� �������� �Ӽ����� �о����!

	for (int i = 0; i < vTemp.size(); i++)
	{

		//�ؽ�Ʈ������ ��� ǥ�� ���� �ǳʶٱ�
		if (vTemp[i] == "�ܰ�" || vTemp[i] == "��" || vTemp[i] == "�μհ�" || vTemp[i] == "����" || vTemp[i] == "����" ||
			vTemp[i] == "�Ǽ�����" || vTemp[i] == "Ǫ��" || vTemp[i] == "����")
		{
			count += 2;
			continue;
		}
		

		if (vTemp[i] == "|")
		{
			eItem* em = new eItem;
			str = vTemp[i + 1];

			_mTotalEitem.insert(pair<string, eItem*>(vTemp[i + 1], em));

			if (i != 2) count += 14;
			continue;
		}

		mIterEitem mIter = _mTotalEitem.find(str);

		if (i == count + 1) mIter->second->name_ = vTemp[i];
		else if (i == count + 2) mIter->second->category_ = (CATEGORY_E)atoi(vTemp[i].c_str());
		else if (i == count + 3) mIter->second->cct_ = (CCT)atoi(vTemp[i].c_str());
		else if (i == count + 4) mIter->second->atk_ = (int)atoi(vTemp[i].c_str());
		else if (i == count + 5) mIter->second->atkSpd_ = (int)atoi(vTemp[i].c_str());
		else if (i == count + 6) mIter->second->def_ = (int)atoi(vTemp[i].c_str());
		else if (i == count + 7) mIter->second->str_ = (int)atoi(vTemp[i].c_str());
		else if (i == count + 8) mIter->second->con_ = (int)atoi(vTemp[i].c_str());
		else if (i == count + 9) mIter->second->int_ = (int)atoi(vTemp[i].c_str());
		else if (i == count + 10) mIter->second->lck_ = (int)atoi(vTemp[i].c_str());
		else if (i == count + 11) mIter->second->HP_ = (int)atoi(vTemp[i].c_str());
		else if (i == count + 12)
		{
			mIter->second->description_ = vTemp[i];
			mIter->second->img_ = IMAGEMANAGER->findImage(mIter->second->name_);
		}
		
	
	}

	vTemp.clear();
}

