#pragma once
#include "singletonBase.h"
#include <vector>
#include <map>

enum CATEGORY_C
{
	ONE_HAND, CATEGORY_C_END
};
enum cKind
{
	FOOD,POTION,cKInd_END

};

struct cItem
{
	const char* name;
	CATEGORY_C category;
	cKind cItemKind;
	int HP_;
	int str_;
	int con_;
	int int_;
	int lck_;

	cItem(){}
	~cItem(){}
};



class ConsumableItemDatabase : public singletonBase<ConsumableItemDatabase>
{
private:

	typedef vector<string>	arrCitems;
	typedef vector<string>::iterator iterCitems;
	typedef map<string, cItem*> arrCitem;
	typedef map<string, cItem*>::iterator iterCitem;

private:

	arrCitem _mTotalCitem;


public:
	HRESULT init();
	void release();

	void loadDatabase(string name);

	cItem* getCitemData(string str) { return _mTotalCitem.find(str)->second; }


	
	void setCitemDataCateroty(string str, CATEGORY_C caterory);
	void setCitemDataCkind(string str, cKind cItemKind);
	void setCitemDataHP(string str, int HP_);
	void setCitemDataSTR(string str, int str_);
	void setCitemDataINT(string str, int int_);
	void setCitemDataCON(string str, int con_);
	void setCitemDatalck(string str, int lck_);



	ConsumableItemDatabase();
	~ConsumableItemDatabase();
};

