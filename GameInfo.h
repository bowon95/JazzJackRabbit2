#pragma once

#include <Windows.h>
#include <list>
#include <vector>
#include <unordered_map>
#include <crtdbg.h>
#include <typeinfo>
#include <string>
#include <functional> // 전역/멤버 함수건 상관없이 함수포인터 등록해주고 콜해주는 기능

#include "Vector2.h"
#include "SharedPtr.h"
#include "Flag.h"

// msing32는 기본적으로 제공됨. 이미지를 쓰기 위해 기초작업.
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

struct AnimationFrameData // 스프라이트 이미지상에서 뜯어올 프레임
{
	Vector2	Start;
	Vector2	End;
};