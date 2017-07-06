#include "stdafx.h"
#include "inven.h"


inven::inven()
{
}


inven::~inven()
{
}

alucardHave::alucardHave() {}
alucardHave::~alucardHave() {}

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
	viInven = vInven.begin();
	
	if (viInven == vInven.end())
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
		item.count_++;

		vInven.push_back(item);
	}

	for (viInven = vInven.begin(); viInven != vInven.end(); viInven++)
	{
		if (viInven->name_ == itemName)
		{
			viInven->count_++;
			break;
		}

		if (viInven == vInven.end() - 1)
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
			item.count_++;

			vInven.push_back(item);
			break;
		}
	}
}

void inven::deleteItem(string itemName)
{
	for (viInven = vInven.begin(); viInven != vInven.end();)
	{
		if (viInven->name_ == itemName)
		{
			if (viInven->count_ > 1)
			{
				viInven->count_--;
				if (_onDelete)
				{
					_onDelete = false;
					return;
				}
				break;
			}
			else
			{
				if (_onDelete)
				{
					_onDelete = false;
					viInven = vInven.erase(viInven);
					return;
				}
				viInven = vInven.erase(viInven);
				break;
			}
		}
		else
		{
			++viInven;
		}
	}
}


//============================================================================알카드 정보창

void alucardHave::insertItem(string itemName, int inven)
{
	viAlucard = vAlucard.begin();

	if (viAlucard == vAlucard.end())
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
		item.count_++;

		vAlucard.push_back(item);
	}

	for (viAlucard = vAlucard.begin(); viAlucard != vAlucard.end(); viAlucard++)
	{
		if (viAlucard->category_ == INVEN->getVinven()[inven].category_)
		{
			_onDelete = true;
			break;
		}
		
		if (viAlucard == vAlucard.end() - 1)
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
			item.count_++;

			vAlucard.push_back(item);
			break;
		}
	}
}

void alucardHave::deleteItem(string itemName)
{
	viAlucard = vAlucard.begin();

	for (; viAlucard != vAlucard.end();)
	{
		if (viAlucard->name_ == itemName)
		{
			viAlucard = vAlucard.erase(viAlucard);
			INVEN->insertItem(itemName);
			break;
		}
		else
		{
			++viAlucard;
		}
	}
}