#include "stdafx.h"
#include "inven.h"


inven::inven()
{
}


inven::~inven()
{
}

HRESULT inven::init(void)		
{
	return S_OK;
}
void inven::release(void)		
{
}
void inven::update(void)		
{
}
void inven::render(void)		
{
}


void inven::insertItem(string itemName)
{
	tagINVENITEM item;
	item.name_ = ITEM->getData(itemName)->name_;
	item.category_ = ITEM->getData(itemName)->category_;
	item.cct_ = ITEM->getData(itemName)->cct_;
	item.atk_ = ITEM->getData(itemName)->atk_;
	item.atkSpd_ = ITEM->getData(itemName)->atkSpd_;
	item.def_ = ITEM->getData(itemName)->def_;
	item.str_ = ITEM->getData(itemName)->str_;
	item.con_ = ITEM->getData(itemName)->con_;
	item.int_ = ITEM->getData(itemName)->int_;
	item.lck_ = ITEM->getData(itemName)->lck_;
	item.HP_ = ITEM->getData(itemName)->HP_;
	item.description_ = ITEM->getData(itemName)->description_;

	item.img_ = ITEM->getData(itemName)->img_;
}