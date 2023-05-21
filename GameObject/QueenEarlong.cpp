
#include "QueenEarlong.h"
#include "../Scene/Scene.h"

CQueenEarlong::CQueenEarlong()
{
	SetTypeID<CQueenEarlong>();
}

CQueenEarlong::CQueenEarlong(const CQueenEarlong& Obj)	:
	CMonster(Obj),
	m_Dir(Obj.m_Dir)
{
}

CQueenEarlong::~CQueenEarlong()
{
} 

bool CQueenEarlong::Init()
{
	CGameObject::Init();

	m_Dir = Vector2(0.f, 0.f);

	CreateAnimation();

	AddAnimation("QueenIdle");

	SetPos(1100.f, 600.f);
	SetSize(150.f, 150.f);
	SetPivot(0.5f, 0.5f);

	return true;
}

void CQueenEarlong::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	// MoveDir(m_Dir);
}

void CQueenEarlong::PostUpdate(float DeltaTime)
{
	CMonster::PostUpdate(DeltaTime);
}

void CQueenEarlong::Render(HDC hDC, float DeltaTime)
{
	CMonster::Render(hDC, DeltaTime);
}
