#pragma once

#include "GameInfo.h"

/* 
������� ���ػ� Ÿ�̸Ӹ� ������ �ְ� �� ���ػ� Ÿ�̸��� ���� ���� �� �ִ�.
�����Ӱ� ������ ������ �ð��� ���ϰ��� �Ѵٸ� ���ػ� Ÿ�̸��� ���� ���ͼ�
���� �� �ִ�.
*/
class CTimer
{
public:
	CTimer();
	~CTimer();

private:
	LARGE_INTEGER	m_Second;
	LARGE_INTEGER	m_Time;
	float			m_DeltaTime; // �����Ӱ� ������ ���� �帥 �ð�
	float			m_FPS;
	float			m_FPSTime;
	float			m_Tick;

public:
	float GetDeltaTime()	const
	{
		return m_DeltaTime;
	}

	float GetFPS()	const
	{
		return m_FPS;
	}

public:
	void Init();
	void Update();
};
 
