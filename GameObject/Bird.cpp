#include "Bird.h"
#include "../Scene/Scene.h"

CBird::CBird()
{
	SetTypeID<CBird>();
}

CBird::CBird(const CBird& Obj) :
	CMonster(Obj),
	m_Dir(Obj.m_Dir)
{
}

CBird::~CBird()
{
}

bool CBird::Init()
{
	CGameObject::Init();

	m_MoveSpeed = 100.f;
	m_Dir = Vector2(0.f, 1.f);

	SetPos(800.f, 500.f);
	SetSize(300.f, 300.f);
	SetPivot(0.5f, 0.5f);

	SetTexture("Bird", TEXT("Bird.bmp"));

	CreateAnimation();

	AddAnimation("BirdCage");

	return true;
}

void CBird::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	//MoveDir(m_Dir);
}

void CBird::PostUpdate(float DeltaTime)
{
	CCharacter::PostUpdate(DeltaTime);
}

void CBird::Render(HDC hDC, float DeltaTime)
{
	CCharacter::Render(hDC, DeltaTime);
}
