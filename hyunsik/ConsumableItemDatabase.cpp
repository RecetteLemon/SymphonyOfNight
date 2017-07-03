#include "stdafx.h"
#include "ConsumableItemDatabase.h"


ConsumableItemDatabase::ConsumableItemDatabase()
{
}


ConsumableItemDatabase::~ConsumableItemDatabase()
{
}


HRESULT ConsumableItemDatabase::init(void)
{

	loadDatabase("citemData.txt");
	return S_OK;
}
void ConsumableItemDatabase::release()
{
	iterCitem iterItem;

	for (iterItem = _mTotalCitem.begin(); iterItem != _mTotalCitem.end();)
	{
		safeDelete(iterItem->second);
		iterItem = _mTotalCitem.erase(iterItem);
	}
}
//TXT������ ������
void ConsumableItemDatabase::loadDatabase(string name)
{
	arrCitems vTemp;
	vTemp = TXTDATA->txtLoad(name.c_str());

	string str;
	int count = 0;

	for (int i = 0; i < vTemp.size(); ++i)
	{
		if (vTemp[i] == "Ǫ��" || vTemp[i] == "����")
		{
			count += 2;
			continue;
		}

		if (vTemp[i] == "|")
		{
			cItem* item = new cItem;

			str = vTemp[i + 1];

			_mTotalCitem.insert(pair<string, cItem*>(vTemp[i + 1], item));

			if (i != 2) count += 11;
			continue;
		}
		iterCitem mCitem = _mTotalCitem.find(str);
		

		//TXT ������ ������ ���ڷ� �Ǿ������� atoi�� ������ �ٲ���
		//������������ġ,����������,hp���Ȱ� ,str���Ȱ�,int���Ȱ�,con���Ȱ�,luck���Ȱ�
		if (i == count + 1) mCitem->second->name = vTemp[i];
		else if (i == count + 2) mCitem->second->category = (CATEGORY_C)atoi(vTemp[i].c_str());
		else if (i == count + 3) mCitem->second->cItemKind = (cKind)atoi(vTemp[i].c_str());
		else if (i == count + 4) mCitem->second->HP_ = (int)atoi(vTemp[i].c_str());
		else if (i == count + 5) mCitem->second->str_ = (int)atoi(vTemp[i].c_str());
		else if (i == count + 6) mCitem->second->con_ = (int)atoi(vTemp[i].c_str());
		else if (i == count + 7) mCitem->second->int_ = (int)atoi(vTemp[i].c_str());
		else if (i == count + 8) mCitem->second->lck_ = (int)atoi(vTemp[i].c_str());
		else if (i == count + 9) mCitem->second->explanation = vTemp[i];

		mCitem->second->img_ = IMAGEMANAGER->findImage(mCitem->second->name);
		
	}	

	vTemp.clear();
}
