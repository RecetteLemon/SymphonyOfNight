﻿#include "stdafx.h"
#include "animation.h"

//멤버 이니셜라이즈
animation::animation()
	: _frameNum(0),
	_frameWidth(0),
	_frameHeight(0),
	_loop(FALSE),
	_frameUpdateSec(0),
	_elapsedSec(0),
	_nowPlayIndex(0),
	_play(FALSE)
{
}


animation::~animation()
{

}

HRESULT animation::init(int totalW, int totalH, int frameW, int frameH)
{
	//가로 프레임 갯수
	_frameWidth = frameW;
	int _frameNumWidth = totalW / _frameWidth;

	//세로 프레임 갯수
	_frameHeight = frameH;
	int _frameNumHeight = totalH / _frameHeight;

	//총 프레임 갯수
	_frameNum = _frameNumWidth * _frameNumHeight;

	//해당 프레임 위치로 셋팅
	for (int i = 0; i < _frameNumHeight; i++)
	{
		for (int j = 0; j < _frameNumWidth; j++)
		{
			POINT framePos;

			framePos.x = j * _frameWidth;
			framePos.y = i * _frameHeight;

			_frameList.push_back(framePos);
		}
	}

	//기본은 디폴트로
	setDefPlayFrame();

	return S_OK;
}

void animation::release(void)
{

}


//디폴트 애니메이션
void animation::setDefPlayFrame(BOOL reverse, BOOL loop)
{
	_obj = NULL;
	_callbackFunction = NULL;
	_callbackFunctionParameter = NULL;

	//루프 여부 받자
	_loop = loop;

	//플레이 리스트 초기화
	_playList.clear();

	if (reverse)
	{
		if (_loop)
		{
			//0 1 2 3 4 5
			for (int i = 0; i < _frameNum; i++)
			{
				_playList.push_back(i);
			}
			//4 3 2 1 
			for (int i = _frameNum - 1; i > 0; i--)
			{
				_playList.push_back(i);
			}
		}
		else
		{
			//0 1 2 3 4 5
			for (int i = 0; i < _frameNum; i++)
			{
				_playList.push_back(i);
			}
			//4 3 2 1 
			for (int i = _frameNum - 1; i > 0; i--)
			{
				_playList.push_back(i);
			}
		}
	}
	else
	{
		if (_loop)
		{
			for (int i = 0; i < _frameNum; i++)
			{
				_playList.push_back(i);
			}
		}
		else
		{
			for (int i = 0; i < _frameNum; i++)
			{
				_playList.push_back(i);
			}
		}
	}
}

void animation::setDefPlayFrame(BOOL reverse, BOOL loop, CALLBACK_FUNCTION cbFunction)
{
	_obj = NULL;
	_callbackFunction = cbFunction;
	_callbackFunctionParameter = NULL;

	//루프 여부 받자
	_loop = loop;

	//플레이 리스트 초기화
	_playList.clear();

	if (reverse)
	{
		if (_loop)
		{
			//0 1 2 3 4 5
			for (int i = 0; i < _frameNum; i++)
			{
				_playList.push_back(i);
			}
			//4 3 2 1 
			for (int i = _frameNum - 1; i > 0; i--)
			{
				_playList.push_back(i);
			}
		}
		else
		{
			//0 1 2 3 4 5
			for (int i = 0; i < _frameNum; i++)
			{
				_playList.push_back(i);
			}
			//4 3 2 1 
			for (int i = _frameNum - 1; i > 0; i--)
			{
				_playList.push_back(i);
			}
		}
	}
	else
	{
		if (_loop)
		{
			for (int i = 0; i < _frameNum; i++)
			{
				_playList.push_back(i);
			}
		}
		else
		{
			for (int i = 0; i < _frameNum; i++)
			{
				_playList.push_back(i);
			}
		}
	}
}

void animation::setDefPlayFrame(BOOL reverse, BOOL loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj)
{
	_obj = obj;
	_callbackFunction = NULL;
	_callbackFunctionParameter = cbFunction;

	//루프 여부 받자
	_loop = loop;

	//플레이 리스트 초기화
	_playList.clear();

	if (reverse)
	{
		if (_loop)
		{
			//0 1 2 3 4 5
			for (int i = 0; i < _frameNum; i++)
			{
				_playList.push_back(i);
			}
			//4 3 2 1 
			for (int i = _frameNum - 1; i > 0; i--)
			{
				_playList.push_back(i);
			}
		}
		else
		{
			//0 1 2 3 4 5
			for (int i = 0; i < _frameNum; i++)
			{
				_playList.push_back(i);
			}
			//4 3 2 1 
			for (int i = _frameNum - 1; i > 0; i--)
			{
				_playList.push_back(i);
			}
		}
	}
	else
	{
		if (_loop)
		{
			for (int i = 0; i < _frameNum; i++)
			{
				_playList.push_back(i);
			}
		}
		else
		{
			for (int i = 0; i < _frameNum; i++)
			{
				_playList.push_back(i);
			}
		}
	}
}

//배열 애니메이션
void animation::setPlayFrame(int* playArr, int arrLen, BOOL loop)
{
	_obj = NULL;
	_callbackFunction = NULL;
	_callbackFunctionParameter = NULL;

	_loop = loop;

	_playList.clear();

	for (int i = 0; i < arrLen; i++)
	{
		_playList.push_back(playArr[i]);
	}
}

void animation::setPlayFrame(int* playArr, int arrLen, BOOL loop, CALLBACK_FUNCTION cbFunction)
{
	_obj = NULL;
	_callbackFunction = cbFunction;
	_callbackFunctionParameter = NULL;

	_loop = loop;

	_playList.clear();

	for (int i = 0; i < arrLen; i++)
	{
		_playList.push_back(playArr[i]);
	}
}

void animation::setPlayFrame(int* playArr, int arrLen, BOOL loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj)
{
	_obj = obj;
	_callbackFunction = NULL;
	_callbackFunctionParameter = cbFunction;

	_loop = loop;

	_playList.clear();

	for (int i = 0; i < arrLen; i++)
	{
		_playList.push_back(playArr[i]);
	}
}

//구간 애니메이션
void animation::setPlayFrame(int start, int end, BOOL reverse, BOOL loop)
{
	_obj = NULL;
	_callbackFunction = NULL;
	_callbackFunctionParameter = NULL;

	_loop = loop;

	_playList.clear();

	//첫장이랑 끝장이랑 같다? -> 1장
	if (start == end)
	{
		_playList.clear();
		stop();
		return;
	}

	//인덱스 번호가 앞이 클때
	if (start > end)
	{
		if (reverse)
		{
			if (_loop)
			{
				//7 6 5 4 3 2
				for (int i = start; i >= end; i--)
				{
					_playList.push_back(i);
				}
				//3 4 5 6 
				for (int i = end + 1; i < start; i++)
				{
					_playList.push_back(i);
				}
			}
			else
			{
				for (int i = start; i >= end; i--)
				{
					_playList.push_back(i);
				}
				//3 4 5 6 
				for (int i = end + 1; i < start; i++)
				{
					_playList.push_back(i);
				}
			}
		}
		else
		{
			if (_loop)
			{
				for (int i = start; i >= end; i--)
				{
					_playList.push_back(i);
				}
			}
			else
			{
				for (int i = start; i >= end; i--)
				{
					_playList.push_back(i);
				}
			}
		}
	}
	else
	{
		if (reverse)
		{
			if (_loop)
			{
				for (int i = start; i < end; i++)
				{
					_playList.push_back(i);
				}

				for (int i = end - 1; i > start; i--)
				{
					_playList.push_back(i);
				}
			}
			else
			{
				for (int i = start; i < end; i++)
				{
					_playList.push_back(i);
				}

				for (int i = end - 1; i > start; i--)
				{
					_playList.push_back(i);
				}
			}
		}
		else
		{
			if (_loop)
			{
				for (int i = start; i < end; i++)
				{
					_playList.push_back(i);
				}
			}
			else
			{
				for (int i = start; i < end; i++)
				{
					_playList.push_back(i);
				}
			}
		}
	}
}

void animation::setPlayFrame(int start, int end, BOOL reverse, BOOL loop, CALLBACK_FUNCTION cbFunction)
{
	_obj = NULL;
	_callbackFunction = cbFunction;
	_callbackFunctionParameter = NULL;

	_loop = loop;

	_playList.clear();

	//첫장이랑 끝장이랑 같다? -> 1장
	if (start == end)
	{
		_playList.clear();
		stop();
		return;
	}

	//인덱스 번호가 앞이 클때
	if (start > end)
	{
		if (reverse)
		{
			if (_loop)
			{
				//7 6 5 4 3 2
				for (int i = start; i >= end; i--)
				{
					_playList.push_back(i);
				}
				//3 4 5 6 
				for (int i = end + 1; i < start; i++)
				{
					_playList.push_back(i);
				}
			}
			else
			{
				for (int i = start; i >= end; i--)
				{
					_playList.push_back(i);
				}
				//3 4 5 6 
				for (int i = end + 1; i < start; i++)
				{
					_playList.push_back(i);
				}
			}
		}
		else
		{
			if (_loop)
			{
				for (int i = start; i >= end; i--)
				{
					_playList.push_back(i);
				}
			}
			else
			{
				for (int i = start; i >= end; i--)
				{
					_playList.push_back(i);
				}
			}
		}
	}
	else
	{
		if (reverse)
		{
			if (_loop)
			{
				for (int i = start; i < end; i++)
				{
					_playList.push_back(i);
				}

				for (int i = end - 1; i > start; i--)
				{
					_playList.push_back(i);
				}
			}
			else
			{
				for (int i = start; i < end; i++)
				{
					_playList.push_back(i);
				}

				for (int i = end - 1; i > start; i--)
				{
					_playList.push_back(i);
				}
			}
		}
		else
		{
			if (_loop)
			{
				for (int i = start; i < end; i++)
				{
					_playList.push_back(i);
				}
			}
			else
			{
				for (int i = start; i < end; i++)
				{
					_playList.push_back(i);
				}
			}
		}
	}
}

void animation::setPlayFrame(int start, int end, BOOL reverse, BOOL loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj)
{
	_obj = obj;
	_callbackFunction = NULL;
	_callbackFunctionParameter = cbFunction;

	_loop = loop;

	_playList.clear();

	//첫장이랑 끝장이랑 같다? -> 1장
	if (start == end)
	{
		_playList.clear();
		stop();
		return;
	}

	//인덱스 번호가 앞이 클때
	if (start > end)
	{
		if (reverse)
		{
			if (_loop)
			{
				//7 6 5 4 3 2
				for (int i = start; i >= end; i--)
				{
					_playList.push_back(i);
				}
				//3 4 5 6 
				for (int i = end + 1; i < start; i++)
				{
					_playList.push_back(i);
				}
			}
			else
			{
				for (int i = start; i >= end; i--)
				{
					_playList.push_back(i);
				}
				//3 4 5 6 
				for (int i = end + 1; i < start; i++)
				{
					_playList.push_back(i);
				}
			}
		}
		else
		{
			if (_loop)
			{
				for (int i = start; i >= end; i--)
				{
					_playList.push_back(i);
				}
			}
			else
			{
				for (int i = start; i >= end; i--)
				{
					_playList.push_back(i);
				}
			}
		}
	}
	else
	{
		if (reverse)
		{
			if (_loop)
			{
				for (int i = start; i < end; i++)
				{
					_playList.push_back(i);
				}

				for (int i = end - 1; i > start; i--)
				{
					_playList.push_back(i);
				}
			}
			else
			{
				for (int i = start; i < end; i++)
				{
					_playList.push_back(i);
				}

				for (int i = end - 1; i > start; i--)
				{
					_playList.push_back(i);
				}
			}
		}
		else
		{
			if (_loop)
			{
				for (int i = start; i < end; i++)
				{
					_playList.push_back(i);
				}
			}
			else
			{
				for (int i = start; i < end; i++)
				{
					_playList.push_back(i);
				}
			}
		}
	}
}

void animation::setFPS(int framePerSec)
{
	_frameUpdateSec = 1.0f / framePerSec;
}


void animation::frameUpdate(float elapsedTime)
{
	if (_play)
	{
		_elapsedSec += elapsedTime;

		//프레임을 업데이트 해야하면
		if (_elapsedSec >= _frameUpdateSec)
		{
			_elapsedSec -= _frameUpdateSec;

			_nowPlayIndex++;

			//끝까지 재생했다면
			if (_nowPlayIndex == _playList.size())
			{
				if (_loop) _nowPlayIndex = 0;
				else
				{
					if (_obj == NULL)
					{
						if (_callbackFunction != NULL) _callbackFunction();
					}
					else
					{
						_callbackFunctionParameter(_obj);
					}

					_nowPlayIndex--;
					_play = FALSE;
				}
			}
		}
	}
}


void animation::start(void)	
{
	_play = TRUE;
	_nowPlayIndex = 0;
}

void animation::stop(void)	
{
	_play = FALSE;
	_nowPlayIndex = 0;
}

void animation::pause(void)	
{
	_play = FALSE;
}

void animation::resume(void)
{
	_play = TRUE;
}
