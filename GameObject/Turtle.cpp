
#include "Turtle.h"
#include "../Scene/Scene.h"
#include "Bullet.h"

CTurtle::CTurtle()
{
	SetTypeID<CTurtle>();
}

CTurtle::CTurtle(const CTurtle& Obj) :
	CMonster(Obj),
	m_Dir(Obj.m_Dir)
{
}

CTurtle::~CTurtle()
{
}

bool CTurtle::Init()
{
	CGameObject::Init();

	m_MoveSpeed = 100.f;
	m_Dir = Vector2(0.f, 0.f);

	SetPos(500.f, 700.f);
	SetSize(300.f, 300.f);
	SetPivot(0.5f, 1.f);

	CreateAnimation();

	AddAnimation("TurtleWalkingLeft");

	return true;
}

void CTurtle::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CTurtle::PostUpdate(float DeltaTime)
{
	CCharacter::PostUpdate(DeltaTime);
}

void CTurtle::Render(HDC hDC, float DeltaTime)
{
	CCharacter::Render(hDC, DeltaTime);
}
