#pragma once

#include "GameInfo.h"
#include "SingletonMacro.h"

class CGameManager
{
private:
	HINSTANCE	m_hInst;
	HWND		m_hWnd;
	static bool m_Loop; // static 멤버변수인 이유는 
	// wndProc 스테틱함수에서 윈도우가 종료될때 이 변수를 false로 만들어주기위해서.
	HDC			m_hDC;
	HDC			m_hBackDC;
	HBITMAP		m_hBackBmp;
	HBITMAP		m_hBackPrevBmp;

	class CTimer*  m_Timer;
	float		  m_FrameLimitTime;
	float         m_DeltaTime;

	Resolution	m_RS;
	
	float	m_TimeScale; // 글로벌 타임 재생 배율.

public:
	Resolution GetResolution()	const
	{
		return m_RS;
	}

	float GetDeltaTime()	const
	{
		return m_DeltaTime;
	}

	HDC GetWindowDC()	const
	{
		return m_hDC;
	}

	HWND GetWindowHandle()	const
	{
		return m_hWnd;
	}

	HINSTANCE GetWindowInstance()	const
	{
		return m_hInst;
	}

	float GetTimeScale()	const
	{
		return m_TimeScale;
	}

public:
	void SetTimeScale(float Scale)
	{
		m_TimeScale = Scale;
	}

public:
	bool Init(HINSTANCE hInst);
	int Run();

private:
	void Logic();
	void Input(float DeltaTime);
	bool Update(float DeltaTime);
	void PostUpdate(float DeltaTime);
	void Collision(float DeltaTime);
	void Render(float DeltaTime);
		
private:
	void Register();
	bool Create();

private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	DECLARE_SINGLE(CGameManager)
};

