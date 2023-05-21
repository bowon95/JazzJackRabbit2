
#include "Bullet.h"

CBullet::CBullet()
{
    SetTypeID<CBullet>(); // CBullet타입으로 ID 잡아놓는다. 
}

CBullet::CBullet(const CBullet& Obj) :
    CGameObject(Obj),
    m_Dir(Obj.m_Dir),
    m_Angle(Obj.m_Angle),
    m_Distance(Obj.m_Distance)
{
}


CBullet::~CBullet()
{
}

bool CBullet::Init()
{
    m_MoveSpeed = 500.f;
    m_Distance = 600.f;
    m_Angle = 180.f; // 왼쪽 180도. 오른쪽이면 0도

    //SetPos(900.f, 100.f); 
    SetSize(10.f, 10.f);
    SetPivot(0.5f, 0.8f); // 몬스터에서 나오는 위치가 바뀜.

    return true;
}

void CBullet::Update(float DeltaTime)
{
    CGameObject::Update(DeltaTime);

    Move(m_Angle);

    m_Distance -= m_MoveSpeed * DeltaTime;

    if (m_Distance <= 0.f)
        SetActive(false); //Scene에서 알아서 제거됨.
}

void CBullet::PostUpdate(float DeltaTime)
{
    CGameObject::PostUpdate(DeltaTime);
}

void CBullet::Render(HDC hDC, float DeltaTime)
{
    Vector2 RenderLT;

    RenderLT = m_Pos - m_Pivot * m_Size;

    Ellipse(hDC, (int)RenderLT.x, (int)RenderLT.y,
        (int)(RenderLT.x + m_Size.x), (int)(RenderLT.y + m_Size.y));
}