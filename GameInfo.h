#pragma once

#include <Windows.h>
#include <list>
#include <vector>
#include <unordered_map>
#include <crtdbg.h>
#include <typeinfo>
#include <string>
#include <functional> // ����/��� �Լ��� ������� �Լ������� ������ְ� �����ִ� ���

#include "Vector2.h"
#include "SharedPtr.h"
#include "Flag.h"

// msing32�� �⺻������ ������. �̹����� ���� ���� �����۾�.
#pragma comment(lib, "msimg32.lib")

#define ROOT_PATH	"RootPath"
#define TEXTURE_PATH	"TexturePath"

#define SAFE_DELETE(p)	if(p)	{ delete p; p = nullptr; }
#define SAFE_DELETE_ARRAY(p)		if(p)	{ delete[] p; p = nullptr; }
#define	SAFE_RELEASE(p) if(p)	{ p->Release(); p = nullptr; }

float RadianToDegree(float Radian);
float DegreeToRadian(float Degree);

#define	DELTA_TIME	CGameManager::GetInst()->GetDeltaTime()

struct Resolution
{
	int Width;
	int Height;
};

struct AnimationFrameData // ��������Ʈ �̹����󿡼� ���� ������
{
	Vector2	Start;
	Vector2	End;
};