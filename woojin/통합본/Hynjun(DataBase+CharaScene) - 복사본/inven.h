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

	int			count_;

	tagINVENITEM():
		count_(0)
	{}
};

static bool _onDelete = false;

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

	void insertItem(string itemName);
	void deleteItem(string itemName);

	vector<tagINVENITEM> getVinven() { return vInven; }
	vector<tagINVENITEM>::iterator getVIinven() { return viInven; }
	
	inven();
	~inven();
};

class alucardHave : public singletonBase<alucardHave>
{
private:
	vector<tagINVENITEM> vAlucard;
	vector<tagINVENITEM>::iterator viAlucard;

public:
	void insertItem(string itemName, int inven);
	void deleteItem(string itemName);

	vector<tagINVENITEM> getValucard() { return vAlucard; }
	vector<tagINVENITEM>::iterator getVIalucard() { return viAlucard; }

	alucardHave();
	~alucardHave();
};

