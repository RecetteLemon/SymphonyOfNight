#include "stdafx.h"
#include "itemDataBase.h"


equipment::equipment()
{
}


equipment::~equipment()
{
}


HRESULT equipment::init()
{
	loadDatabase("category_e.txt");

	return S_OK;
}

//============================================================================�����Ҵ� ����ü ����Ʈ
void equipment::release()
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
void equipment::loadDatabase(string name)
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
		if (vTemp[i] == "�ܰ�" || vTemp[i] == "��" || vTemp[i] == "�μհ�")
		{
			count += 2;
			continue;
		}
		

		if (vTemp[i] == "|")
		{
			eItem* em = new eItem;
			str = vTemp[i + 1];

			_mTotalEitem.insert(pair<string, eItem*>(vTemp[i + 1], em));

			if (i != 2) count += 12;
			continue;
		}

		mIterEitem mIter = _mTotalEitem.find(str);

		if (i == count + 1) mIter->second->name_ = vTemp[i].c_str();
		else if (i == count + 2) mIter->second->category_ = (CATEGORY_E)atoi(vTemp[i].c_str());
		else if (i == count + 3) mIter->second->cct_ = (CCT)atoi(vTemp[i].c_str());
		else if (i == count + 4) mIter->second->atk_ = (int)atoi(vTemp[i].c_str());
		else if (i == count + 5) mIter->second->atkSpd_ = (int)atoi(vTemp[i].c_str());
		else if (i == count + 6) mIter->second->def_ = (int)atoi(vTemp[i].c_str());
		else if (i == count + 7) mIter->second->str_ = (int)atoi(vTemp[i].c_str());
		else if (i == count + 8) mIter->second->con_ = (int)atoi(vTemp[i].c_str());
		else if (i == count + 9) mIter->second->int_ = (int)atoi(vTemp[i].c_str());
		else if (i == count + 10) mIter->second->lck_ = (int)atoi(vTemp[i].c_str());


	}

	vTemp.clear();
}

