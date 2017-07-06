#pragma once
#include "singletonBase.h"

struct tagINVENITEM
{
	string		name_;
	CATEGORY_E	category_;
	CCT			cct_;
	int			atk_;
	int			atkSpd_;
	int			def_;
	int			str_;
	int			con_;
	int			int_;
	int			lck_;
	int			HP_;
	string		description_;

	image*		img_;
};

class inven : public singletonBase<inven>
{
private:

	vector<tagINVENITEM> vInven;
	vector<tagINVENITEM>::iterator viInven;


public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void insertItem(string itemName);
	inven();
	~inven();
};

