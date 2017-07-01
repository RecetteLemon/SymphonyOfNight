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


void ConsumableItemDatabase::loadDatabase(string name) //�ؽ�Ʈ���� �ҷ����� �Լ� 
{
	arrCitems vTemp;
	vTemp = TXTDATA->txtLoad(name.c_str());

	string str;
	int count = 0;




	//�ҷ��� �ؽ�Ʈ������ ���ͻ����ŭ��
	for (int i = 0; i < vTemp.size(); ++i)
	{	
		if (vTemp[i] == "Ǫ��" || vTemp[i] == "����")
		{
			count += 2;
			continue;
		}
		//|�� ���������ؼ� ���ڰ����� �о��
		if (vTemp[i] == "|" )
		{
			cItem* item = new cItem;
			str = vTemp[i + 1]; 

			_mTotalCitem.insert(pair<string, cItem*>(vTemp[i + 1], item));
			
			if (i != 2) count  += 10;
			continue;
		}
		
		
		

		iterCitem mCitem = _mTotalCitem.find(str);
		//�ؽ�Ʈ���� ������ ���ڰ��̴� atoi�� ���ڸ� ������ ��ȯ����
		//������� ī�װ�,����������,HP,str,con,int,luck
		if (i == count + 2) mCitem->second->category = (CATEGORY_C)atoi(vTemp[i].c_str());
		else if (i == count + 3) mCitem->second->cItemKind = (cKind)atoi(vTemp[i].c_str());
		else if (i == count + 4) mCitem->second->HP_ = (int)atoi(vTemp[i].c_str());
		else if (i == count + 5) mCitem->second->str_ = (int)atoi(vTemp[i].c_str());
		else if (i == count + 6) mCitem->second->con_ = (int)atoi(vTemp[i].c_str());
		else if (i == count + 7) mCitem->second->int_ = (int)atoi(vTemp[i].c_str());
		else if (i == count + 8) mCitem->second->lck_ = (int)atoi(vTemp[i].c_str());
	}

	vTemp.clear();
}


//�ҷ��� �ؽ�Ʈ ������ ������ ����ü������ ���� ��������
void ConsumableItemDatabase::setCitemDataCateroty(string str, CATEGORY_C caterory)
{
	iterCitem mCitem = _mTotalCitem.find(str);
	mCitem->second->category = caterory;
}

void ConsumableItemDatabase::setCitemDataCkind(string str, cKind cItemKind)
{
	iterCitem mCitem = _mTotalCitem.find(str);
	mCitem->second->cItemKind = cItemKind;
}

void ConsumableItemDatabase::setCitemDataHP(string str, int HP_)
{
	iterCitem mCitem = _mTotalCitem.find(str);
	mCitem->second->HP_ = HP_;
}

void ConsumableItemDatabase::setCitemDataSTR(string str, int str_)
{
	iterCitem mCitem = _mTotalCitem.find(str);
	mCitem->second->str_ = str_;
}

void ConsumableItemDatabase::setCitemDataINT(string str, int int_)
{
	iterCitem mCitem = _mTotalCitem.find(str);
	mCitem->second->int_ = int_;
}

void ConsumableItemDatabase::setCitemDataCON(string str, int con_)
{
	iterCitem mCitem = _mTotalCitem.find(str);
	mCitem->second->con_ = con_;
}

void ConsumableItemDatabase::setCitemDatalck(string str, int lck_)
{
	iterCitem mCitem = _mTotalCitem.find(str);
	mCitem->second->lck_ = lck_;

}