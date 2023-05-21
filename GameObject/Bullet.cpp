
#include "Bullet.h"

CBullet::CBullet()
{
    SetTypeID<CBullet>(); // CBulletŸ������ ID ��Ƴ��´�. 
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
    m_Angle = 180.f; // ���� 180��. �������̸� 0��

    //SetPos(900.f, 100.f); 
    SetSize(10.f, 10.f);
    SetPivot(0.5f, 0.8f); // ���Ϳ��� ������ ��ġ�� �ٲ�.

    return true;
}

void CBullet::Update(float DeltaTime)
{
    CGameObject::Update(DeltaTime);

    Move(m_Angle);

    m_Distance -= m_MoveSpeed * DeltaTime;

    if (m_Distance <= 0.f)
        SetActive(false); //Scene���� �˾Ƽ� ���ŵ�.
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