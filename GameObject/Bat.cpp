#include "Bat.h"
#include "../Scene/Scene.h"

CBat::CBat()
{
    SetTypeID<CBat>();
}

CBat::CBat(const CBat& Obj) :
    CMonster(Obj),
    m_Dir(Obj.m_Dir)
{
}

CBat::~CBat()
{
}

bool CBat::Init()
{
    CGameObject::Init();

    m_MoveSpeed = 100.f;
    m_Dir = Vector2(0.f, 0.f);

    SetPos(1000.f, 70.f);
    SetSize(25.f, 38.f);
    SetPivot(0.5f, 0.5f);

    SetTexture("Bat", TEXT("Bat.bmp"));
    SetColorKey(0, 128, 255);

    return true;
}

void CBat::Update(float DeltaTime)
{
    CGameObject::Update(DeltaTime);
}

void CBat::PostUpdate(float DeltaTime)
{
    CCharacter::PostUpdate(DeltaTime);
}

void CBat::Render(HDC hDC, float DeltaTime)
{
    CCharacter::Render(hDC, DeltaTime);
}
