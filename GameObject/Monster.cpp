
#include "Monster.h"
#include "../Scene/Scene.h"
#include "Bullet.h"

CMonster::CMonster()    
{
    SetTypeID<CMonster>(); // CMonsterŸ������ ID ��Ƴ��´�. 
}

CMonster::CMonster(const CMonster& Obj) :
    CCharacter(Obj),
    m_Dir(Obj.m_Dir),
    m_FireTime(Obj.m_FireTime)

{
}


CMonster::~CMonster()
{
}

bool CMonster::Init()
{
    CGameObject::Init();

    m_MoveSpeed = 300.f;
    m_Dir = Vector2(0.f, 1.f);
    m_FireTime = 0.f;

    SetPos(900.f, 100.f);
    SetSize(100.f, 100.f);
    SetPivot(0.5f, 0.5f);

    return true;
}

void CMonster::Update(float DeltaTime)
{
    CGameObject::Update(DeltaTime);

    //MoveDir(m_Dir);

    m_FireTime += DeltaTime;

    if (m_FireTime >= 0.5f) // 0.5�ʿ� �� ��.
    {
        m_FireTime -= 0.5f;

        // Bullet ����
        CBullet* Bullet = m_Scene->CreateObject<CBullet>("Bullet");

        float BulletX = m_Pos.x - m_Pivot.x * m_Size.x -
            (1.f - Bullet->GetPivot().x) * Bullet->GetSize().x;

        Bullet->SetPos(BulletX, m_Pos.y); // y�� �ҷ��̶� ���Ͷ� �����ϱ� �״��.
    }
}

void CMonster::PostUpdate(float DeltaTime)
{
    CCharacter::PostUpdate(DeltaTime);
}

void CMonster::Render(HDC hDC, float DeltaTime)
{
    CCharacter::Render(hDC, DeltaTime);
    /*
    Vector2 RenderLT;

    RenderLT = m_Pos - m_Pivot * m_Size;

    Rectangle(hDC, (int)RenderLT.x, (int)RenderLT.y,
        (int)(RenderLT.x + m_Size.x), (int)(RenderLT.y + m_Size.y));
        */
}
