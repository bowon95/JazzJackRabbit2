
#include "Dragon.h"
#include "../Scene/Scene.h"
#include "Bullet.h"
#include "Player.h"

CDragon::CDragon()
{
    SetTypeID<CDragon>();
}

CDragon::CDragon(const CDragon& Obj)    :
    CMonster(Obj),
    m_Dir(Obj.m_Dir),
    m_FireTime(Obj.m_FireTime)
{
}

CDragon::~CDragon()
{
}

bool CDragon::Init()
{
    CGameObject::Init();

    SetTexture("Dragon", TEXT("DragonIdleLeft.bmp"));
    SetColorKey(0, 128, 255);

    m_Dir = Vector2(0.f, 0.f);
    m_FireTime = 0.f;

    SetPos(1000.f, 600.f);
    SetSize(36.f, 21.f);
    SetPivot(0.5f, 0.5f);

    return true;
}

void CDragon::Update(float DeltaTime)
{
    CGameObject::Update(DeltaTime);

    // MoveDir(m_Dir);

    m_FireTime += DeltaTime;

    if (m_FireTime >= 1.f)
    {
        m_FireTime -= 1.f;

        //Bullet »ý¼º
        CBullet* Bullet = m_Scene->CreateObject<CBullet>("Bullet");

        float BulletX = m_Pos.x - m_Pivot.x * m_Size.x -
            (1.f - Bullet->GetPivot().x) * Bullet->GetSize().x;

        Bullet->SetPos(BulletX, m_Pos.y);
    }
}

void CDragon::PostUpdate(float DeltaTime)
{
    CCharacter::PostUpdate(DeltaTime);
}

void CDragon::Render(HDC hDC, float DeltaTime)
{
    CCharacter::Render(hDC, DeltaTime);
  /*  Vector2 RenderLT;

    RenderLT = m_Pos - m_Pivot * m_Size;

    Rectangle(hDC, (int)RenderLT.x, (int)RenderLT.y,
        (int)(RenderLT.x + m_Size.x), (int)(RenderLT.y + m_Size.y));*/
}
