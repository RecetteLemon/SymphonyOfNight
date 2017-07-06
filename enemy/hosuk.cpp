#include "stdafx.h"
#include "hosuk.h"


hosuk::hosuk()
{
}


hosuk::~hosuk()
{
}


HRESULT hosuk::init(const char* imageName, float x, float y, float moveRange)
{
	enemy::init(imageName, x, y, 0);
	imageInit();
	
	_enemyInfo.atk = 10;
	_enemyInfo.die = false;
	_enemyInfo.attack = false;
	_enemyInfo.hp = 30;
	_enemyInfo.speed = 1.0f;


	_enemyInfo.attackTime = _count = 0;

	//�����
	//playerX = WINSIZEX / 2;
	//playerY = WINSIZEY / 2;
	
	
	
	

	return S_OK;
}
void hosuk::imageInit()
{
	//���ִϸ��̼��� �ʱ�ȭ����
	for (int i = 0; i < ENEMY_ANI_END; ++i)
	{
		_enemyInfo.enemyAni[i] = new animation;
		_enemyInfo.enemyAni[i]->init(_enemyInfo.enemyImage->getWidth(), _enemyInfo.enemyImage->getHeight(),
			_enemyInfo.enemyImage->getFrameWidth(), _enemyInfo.enemyImage->getFrameHeight());
	}

	//�ִϸ��̼ǹ迭�� �������� ���������
	int arrLeftMove[] = { 1,2,3,4,5 };
	_enemyInfo.enemyAni[ENEMY_LEFT_MOVEANI]->setPlayFrame(arrLeftMove, 5, true);
	_enemyInfo.enemyAni[ENEMY_LEFT_MOVEANI]->setFPS(6);

	int arrLeftAttack[] = { 6,7,8 };
	_enemyInfo.enemyAni[ENEMY_LEFT_ATTACKANI]->setPlayFrame(arrLeftAttack, 3, false);
	_enemyInfo.enemyAni[ENEMY_LEFT_ATTACKANI]->setFPS(10);

	int arrLeftStay[] = { 1 };
	_enemyInfo.enemyAni[ENEMY_LEFT_STAYANI]->setPlayFrame(arrLeftStay, 1, false);


	int arrRightMove[] = { 16,15,14,13,12 };
	_enemyInfo.enemyAni[ENEMY_RIGHT_MOVEANI]->setPlayFrame(arrRightMove, 5, true);
	_enemyInfo.enemyAni[ENEMY_RIGHT_MOVEANI]->setFPS(6);
	
	int arrRightAttack[] = { 11,10,9 };
	_enemyInfo.enemyAni[ENEMY_RIGHT_ATTACKANI]->setPlayFrame(arrRightAttack, 3, false);
	_enemyInfo.enemyAni[ENEMY_RIGHT_ATTACKANI]->setFPS(10);

	int arrRightStay = { 17 };
	_enemyInfo.enemyAni[ENEMY_RIGHT_STAYANI]->setPlayFrame(arrRightStay, 1, false);

	//ó�� ȣ������ ����
	_enemyInfo.stat = ENEMY_LEFT_MOVE;
	//ȣ���� ���º� ȣ������ �¿� ����
	/*switch (_enemyInfo.stat)
	{
		case ENEMY_LEFT_STAY: case ENEMY_LEFT_MOVE: case ENEMY_LEFT_DIE: case ENEMY_LEFT_ATTACK:
			_direction = ENEMY_LEFT;
		break;
		case ENEMY_RIGHT_STAY: case ENEMY_RIGHT_MOVE: case ENEMY_RIGHT_DIE: case ENEMY_RIGHT_ATTACK:
			_direction = ENEMY_RIGHT;
		break;
	}*/


	//�����
	
}
void hosuk::release(void)
{
	enemy::release();

}
void hosuk::update(void)
{
	enemy::update();
	move();


	//ȣ������ ��Ʈ
	_enemyInfo.rc = RectMakeCenter(_enemyInfo.x, _enemyInfo.y,
		_enemyInfo.enemyImage->getFrameWidth(), _enemyInfo.enemyImage->getFrameHeight());
	
	

	
}
void hosuk::render(void)
{
	
	//����� ȣ���� �簢��
	Rectangle(getMemDC(), _enemyInfo.rc.left, _enemyInfo.rc.top, _enemyInfo.rc.right, _enemyInfo.rc.bottom);
	//Rectangle(getMemDC(), _enemyInfo.playerRc.left, _enemyInfo.playerRc.top, _enemyInfo.playerRc.right, _enemyInfo.playerRc.bottom);
	Rectangle(getMemDC(), _enemyInfo.damageRc.left, _enemyInfo.damageRc.top, _enemyInfo.damageRc.right, _enemyInfo.damageRc.bottom);

	//ȣ���� ���º� �ִϸ��̼��� �����Ŵ
	switch (_enemyInfo.stat)	
	{
		case ENEMY_LEFT_STAY :
			_enemyInfo.enemyImage->aniRender(getMemDC(), _enemyInfo.rc.left, _enemyInfo.rc.top
				, _enemyInfo.enemyAni[ENEMY_LEFT_STAYANI]);
		break;

		case ENEMY_RIGHT_STAY:
			_enemyInfo.enemyImage->aniRender(getMemDC(), _enemyInfo.rc.left, _enemyInfo.rc.top
				, _enemyInfo.enemyAni[ENEMY_RIGHT_STAYANI]);
		break;

		case ENEMY_LEFT_MOVE:
			_enemyInfo.enemyImage->aniRender(getMemDC(), _enemyInfo.rc.left, _enemyInfo.rc.top
				, _enemyInfo.enemyAni[ENEMY_LEFT_MOVEANI]);
		break;

		case ENEMY_RIGHT_MOVE:
			_enemyInfo.enemyImage->aniRender(getMemDC(), _enemyInfo.rc.left, _enemyInfo.rc.top
				, _enemyInfo.enemyAni[ENEMY_RIGHT_MOVEANI]);
		break;
		case ENEMY_LEFT_ATTACK:
			_enemyInfo.enemyImage->aniRender(getMemDC(), _enemyInfo.rc.left, _enemyInfo.rc.top
				, _enemyInfo.enemyAni[ENEMY_LEFT_ATTACKANI]);
		break;

		case ENEMY_RIGHT_ATTACK:
			_enemyInfo.enemyImage->aniRender(getMemDC(), _enemyInfo.rc.left, _enemyInfo.rc.top
				, _enemyInfo.enemyAni[ENEMY_RIGHT_ATTACKANI]);
		break;
	}
}


void hosuk::move()
{
	//�÷��̾� ��ġ�������� ���ϴ� ȣ������ ���°�
	if (_enemyInfo.x > playerX) _enemyInfo.stat = ENEMY_LEFT_MOVE; // ȣ���� ���ʿ� �÷��̾������ ȣ���̴� �������� �޷���
	else //ȣ���� �����ʿ� �÷��̾������ ȣ���̴� ���������� �޷���
	{
		_enemyInfo.stat = ENEMY_RIGHT_MOVE;	//ȣ���� ���°��� �ٲ���
		if (!_enemyInfo.enemyAni[ENEMY_RIGHT_MOVEANI]->isPlay())_enemyInfo.enemyAni[ENEMY_RIGHT_MOVEANI]->start();//ȣ���� ���ʹ���ִϰ� �������̾ƴϸ� �ִϸ��̼� ��ŸƮ!
	}

	float distance = getDistance(_enemyInfo.x, _enemyInfo.y, playerX, playerY); // ȣ������ �������� �÷��̾��� �������� ������
	
	//ȣ���� ���ʿ� ������ �Ÿ��� 50���������� ȣ������ ���´� ���ʰ������� �ٲ�
	
	if (!_enemyInfo.attack)
	{
		_count += TIMEMANAGER->getElapsedTime();

		if (_count >= 1.0f) _enemyInfo.attack = true;
	}

	if (_enemyInfo.x > playerX && distance <= 80)
	{
		_enemyInfo.attackTime += TIMEMANAGER->getElapsedTime();
		if (_enemyInfo.attackTime >= 2.0f && _enemyInfo.attack == true)
		{
			_enemyInfo.stat = ENEMY_LEFT_ATTACK;
			if (!_enemyInfo.enemyAni[ENEMY_LEFT_ATTACKANI]->isPlay())_enemyInfo.enemyAni[ENEMY_LEFT_ATTACKANI]->start();
		}
		else _enemyInfo.stat = ENEMY_LEFT_STAY;
	}
	else if (_enemyInfo.x > playerX&& distance >= 600)
	{
		_enemyInfo.stat = ENEMY_LEFT_STAY;
	}
	
	if (_enemyInfo.x < playerX && distance <= 40) // �÷��̾ ȣ���� �����ʿ��ְ� �Ÿ��� 40 �϶� 
	{
		_enemyInfo.attackTime += TIMEMANAGER->getElapsedTime();  //ȣ������ ���ݵ����̰� + ����
		if (_enemyInfo.attackTime >= 2.0f && _enemyInfo.attack == true) // ȣ������ ���ݵ����̰� 2���̻��̰� ȣ���� ������ Ʈ���϶�.
		{
			_enemyInfo.stat = ENEMY_RIGHT_ATTACK; //ȣ���� ���¸� ������ �������� �ٲ���
			if (!_enemyInfo.enemyAni[ENEMY_RIGHT_ATTACKANI]->isPlay())_enemyInfo.enemyAni[ENEMY_RIGHT_ATTACKANI]->start(); 
			// ȣ���� ���ݾִϰ� ������ �ƴҶ� �ִϸ��̼��� ���������
		}
		else _enemyInfo.stat = ENEMY_RIGHT_STAY; // ���ݵ����� ������ �������϶��� ȣ���̴� ���������ٶ󺸰� ������
	}
	else if (_enemyInfo.x < playerX && distance >= 600)
	{
		_enemyInfo.stat = ENEMY_RIGHT_STAY;
	}

	//ȣ���� ���º� ������,�ִϸ��̼� �÷���
	switch (_enemyInfo.stat)
	{
		case ENEMY_LEFT_MOVE://ȣ������ ���°��� ���ʿ����̸�.
			_enemyInfo.x -= _enemyInfo.speed; //ȣ���̴� �������� ������
			_enemyInfo.enemyAni[ENEMY_LEFT_MOVEANI]->frameUpdate(TIMEMANAGER->getElapsedTime()); //���ʿ����Ӿִϸ��̼� �����Ӿ�����Ʈ�� ����
			if (!_enemyInfo.enemyAni[ENEMY_LEFT_MOVEANI]->isPlay())	_enemyInfo.enemyAni[ENEMY_LEFT_MOVEANI]->start(); //���� �������̾ƴϸ� ���������

			_enemyInfo.damageRc = RectMake(0, 0, 0, 0); // ȣ���̰� �������� �ƴҋ��� ȣ�������ٴڷ�Ʈ�� ����
		break;
		case ENEMY_RIGHT_MOVE:
			_enemyInfo.x += _enemyInfo.speed;
			_enemyInfo.enemyAni[ENEMY_RIGHT_MOVEANI]->frameUpdate(TIMEMANAGER->getElapsedTime());
			if (!_enemyInfo.enemyAni[ENEMY_RIGHT_MOVEANI]->isPlay())_enemyInfo.enemyAni[ENEMY_RIGHT_MOVEANI]->start();

			_enemyInfo.damageRc = RectMake(0, 0, 0, 0);
		break;
		case ENEMY_LEFT_ATTACK:
			_enemyInfo.enemyAni[ENEMY_LEFT_ATTACKANI]->frameUpdate(TIMEMANAGER->getElapsedTime());
			if (!_enemyInfo.enemyAni[ENEMY_LEFT_ATTACKANI]->isPlay()) _enemyInfo.attackTime = _count = 0; 

		
			if (_enemyInfo.enemyAni[ENEMY_LEFT_ATTACKANI]->isPlay()) //ȣ���� ���ݾִϰ� �������ϋ� ���ٴ� ��Ʈ�� ����
			{
				_enemyInfo.damageRc = RectMake(_enemyInfo.x - _enemyInfo.enemyImage->getFrameWidth() / 2,
					_enemyInfo.y + 5, 30, 5);
			}
			else  _enemyInfo.damageRc = RectMake(0, 0, 0, 0); //ȣ���� ���ݾִϰ� ������ ���ٴڷ�Ʈ�� �����

		break;
		case ENEMY_RIGHT_ATTACK:
			_enemyInfo.enemyAni[ENEMY_RIGHT_ATTACKANI]->frameUpdate(TIMEMANAGER->getElapsedTime());
			if (!_enemyInfo.enemyAni[ENEMY_RIGHT_ATTACKANI]->isPlay()) _enemyInfo.attackTime = _count = 0;
			
			//ȣ���̰� �������϶� ȣ���� ���ٴڷ�Ʈ
			if (_enemyInfo.enemyAni[ENEMY_RIGHT_ATTACKANI]->isPlay())
			{
				_enemyInfo.damageRc = RectMake(_enemyInfo.x + _enemyInfo.enemyImage->getFrameWidth() / 2 - 30,
					_enemyInfo.y + 5, 30, 5);
			}
			else _enemyInfo.damageRc = RectMake(0, 0, 0, 0);
		break;
		default:

		break;
	}	
}

void hosuk::setHosukHP(int HP) 
{
	_enemyInfo.hp -= HP;
	
}