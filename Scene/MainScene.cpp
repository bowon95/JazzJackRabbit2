#include "MainScene.h"
#include "../GameObject/Player.h" // MainScene�� �÷��̾ �ʿ��ϸ� ��Ŭ��� & Init�� CreateObject
#include "../GameObject/Turtle.h"
#include "../GameObject/Bird.h"
#include "../GameObject/Dragon.h"
#include "../GameObject/QueenEarlong.h"
#include "../GameObject/Bat.h"
#include"../GameObject/BackObj.h"
#include "SceneResource.h"
#include "Camera.h"


CMainScene::CMainScene()
{
}

CMainScene::~CMainScene()
{
}

bool CMainScene::Init()
{
	CreateAnimationSequence(); 

	GetCamera()->SetResolution(1280.f, 720.f);
	GetCamera()->SetWorldResolution(1500.f, 1200.f);
	GetCamera()->SetTargetPivot(0.5f, 0.5f); // Ÿ�� �Ǻ� 0.5 ��ġ���� ��´�. 

	CreateObject<CBackObj>("BackObj"); // �÷��̾�� ���� ����ؾ��Ѵ�.

	CPlayer* Player = CreateObject<CPlayer>("Jazz"); // �÷��̾ MainScene�� �߰���.
	
	SetPlayer(Player);

	GetCamera()->SetTarget(Player); // ī�޶� Ÿ���� �÷��̾�. 

	CreateObject<CTurtle>("Turtle");
	CreateObject<CBird>("Bird");
	CreateObject<CDragon>("Dragon");
	CreateObject<CQueenEarlong>("QueenEarlong");
	CreateObject<CBat>("Bat");

	return true;
}

void CMainScene::CreateAnimationSequence()
{
	// ============================ Jazz ============================ 
	// Walk
	GetSceneResource()->CreateAnimationSequence("JazzWalkingLeft",
		"JazzWalkingRight", TEXT("Player/JazzWalkingLeft.bmp"), TEXTURE_PATH);

	for (int i = 0; i < 24; ++i)
	{
		//AddAnimationFrame (������ �� ����*i)
		GetSceneResource()->AddAnimationFrame("JazzWalkingLeft", 60.9f * i, 0.f,
			60.9f, 58.5);
	}

	GetSceneResource()->SetColorKey("JazzWalkingLeft", 44, 102, 150);


	GetSceneResource()->CreateAnimationSequence("JazzWalkingRight",
		"JazzWalkingRight", TEXT("Player/JazzWalkingRight.bmp"), TEXTURE_PATH);

	for (int i = 0; i < 24; ++i)
	{
		GetSceneResource()->AddAnimationFrame("JazzWalkingRight", 60.9f * i, 0.f,
			60.9f, 58.5);
	}

	GetSceneResource()->SetColorKey("JazzWalkingRight", 44, 102, 150);


	// Fire
	GetSceneResource()->CreateAnimationSequence("JazzWalkingLeft",
		"JazzWalkingRight", TEXT("Player/JazzWalkingLeft.bmp"), TEXTURE_PATH);

	for (int i = 0; i < 24; ++i)
	{
		//AddAnimationFrame (������ �� ����*i)
		GetSceneResource()->AddAnimationFrame("JazzWalkingLeft", 60.9f * i, 0.f,
			60.9f, 58.5);
	}

	GetSceneResource()->SetColorKey("JazzWalkingLeft", 44, 102, 150);


	GetSceneResource()->CreateAnimationSequence("JazzWalkingRight",
		"JazzWalkingRight", TEXT("Player/JazzWalkingRight.bmp"), TEXTURE_PATH);

	for (int i = 0; i < 24; ++i)
	{
		GetSceneResource()->AddAnimationFrame("JazzWalkingRight", 60.9f * i, 0.f,
			60.9f, 58.5);
	}

	GetSceneResource()->SetColorKey("JazzWalkingRight", 44, 102, 150);



	// ============================  Turtle ============================ 
	GetSceneResource()->CreateAnimationSequence("TurtleWalkingLeft",
		"TurtleWalkingLeft", TEXT("Monster/TurtleWalkingLeft.bmp"), TEXTURE_PATH);

	for (int i = 0; i < 24; ++i)
	{
		GetSceneResource()->AddAnimationFrame("TurtleWalkingLeft", 65.f * i, 0.f,
			65.f, 59);
	}

	GetSceneResource()->SetColorKey("TurtleWalkingLeft", 0, 128, 255);



	// =============================  Bird =============================
	GetSceneResource()->CreateAnimationSequence("BirdCage",
		"BirdCage", TEXT("Monster/BirdCage.bmp"), TEXTURE_PATH);

	for (int i = 0; i < 8; ++i)
	{
		GetSceneResource()->AddAnimationFrame("BirdCage", 64.f * i, 0.f,
			64.f, 55.f);
	}

	GetSceneResource()->SetColorKey("BirdCage", 0, 128, 255);



	// ============================  Queen Earlong ============================ 
	GetSceneResource()->CreateAnimationSequence("QueenIdle",
		"QueenIdle", TEXT("Monster/QueenIdle.bmp"), TEXTURE_PATH);

	for (int i = 0; i < 9; ++i)
	{
		GetSceneResource()->AddAnimationFrame("QueenIdle", 55.55f * i, 0.f,
			55.55f, 58.f);
	}

	GetSceneResource()->SetColorKey("QueenIdle", 0, 128, 255);
}

