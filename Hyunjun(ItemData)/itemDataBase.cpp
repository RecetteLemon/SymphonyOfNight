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
	IMAGEMANAGER->addImage("바제랄드", "Image/Item/dagger1.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("숏소드", "Image/Item/dagger2.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("레이피어", "Image/Item/dagger3.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("쥬엘소드", "Image/Item/dagger4.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("컴뱃나이프", "Image/Item/dagger5.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("틸핑", "Image/Item/OneHand_Sword1.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("그라디우스", "Image/Item/OneHand_Sword2.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("세이버", "Image/Item/OneHand_Sword3.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("하루파", "Image/Item/OneHand_Sword4.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("발만웨", "Image/Item/OneHand_Sword5.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("녹슨검", "Image/Item/TwoHand_Sword1.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("요도무라마사", "Image/Item/TwoHand_Sword2.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("타케미츠", "Image/Item/TwoHand_Sword3.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("야스츠나", "Image/Item/TwoHand_Sword4.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("마사무네", "Image/Item/TwoHand_Sword5.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("실버티아라", "Image/Item/helmet1.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("석가면", "Image/Item/helmet2.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("은빛서클렛", "Image/Item/helmet3.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("성스러운안경", "Image/Item/helmet4.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("펠트의모자", "Image/Item/helmet5.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("미러큐이러스", "Image/Item/armor1.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("실버체스트", "Image/Item/armor2.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("골드체스트", "Image/Item/armor3.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("다이아블래스트", "Image/Item/armor4.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("플레티넘체스트", "Image/Item/armor5.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("킹스톤", "Image/Item/accessory1.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("넥클레스", "Image/Item/accessory2.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("진주반지", "Image/Item/accessory3.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("마스터부츠", "Image/Item/accessory4.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("플레티넘부츠", "Image/Item/accessory5.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("리버서블망토", "Image/Item/accessory6.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("피로물든망토", "Image/Item/accessory7.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("엘프망토", "Image/Item/accessory8.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("블루망토", "Image/Item/accessory9.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("오더메이드", "Image/Item/accessory10.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("고기", "Image/Item/food1.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("버섯", "Image/Item/food2.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("소주", "Image/Item/food3.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("스파게티", "Image/Item/food4.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("바베큐", "Image/Item/food5.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("파란포션", "Image/Item/potion1.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("초록포션", "Image/Item/potion2.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("주황포션", "Image/Item/potion3.bmp", 20, 20, true, RGB(255, 0, 255));

	loadDatabase("All_item.txt");

	return S_OK;
}

//============================================================================동적할당 구조체 딜리트
void allItem::release()
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
void allItem::loadDatabase(string name)
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
		if (vTemp[i] == "단검" || vTemp[i] == "검" || vTemp[i] == "두손검" || vTemp[i] == "투구" || vTemp[i] == "갑옷" ||
			vTemp[i] == "악세서리" || vTemp[i] == "푸드" || vTemp[i] == "포션")
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

