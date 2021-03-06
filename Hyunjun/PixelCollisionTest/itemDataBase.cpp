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

//============================================================================동적할당 구조체 딜리트
void equipment::release()
{
	
	mIterEitem mIter;

	for (mIter = _mTotalEitem.begin(); mIter != _mTotalEitem.end();)
	{
		safeDelete(mIter->second);
		mIter = _mTotalEitem.erase(mIter);
	}	
}


//============================================================================데이터로딩
//= 만약 맵이 터진다면 txtData의 로드데이터의 버퍼량을 늘려주자 =
//============================================================================
void equipment::loadDatabase(string name)
{
	//데이터를 읽어오자
	arrEitem vTemp;
	vTemp = TXTDATA->txtLoad(name.c_str());

	string str;
	int count = 0;

	//칸막이 | 를 기점으로 속성들을 읽어오자!

	for (int i = 0; i < vTemp.size(); i++)
	{
	
		//텍스트파일의 목록 표시 라인 건너뛰기
		if (vTemp[i] == "단검" || vTemp[i] == "검" || vTemp[i] == "두손검")
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

