#pragma once
#include "gameNode.h"
#include "loading.h"


 
class loadingScene : public gameNode
{
private:
	loading* _loading;




public:
	HRESULT init();
	void release();
	void update();
	void render();


	void loadingImage();
	void loadingSound();

	void addItemImage();

	loadingScene();
	~loadingScene();
};
