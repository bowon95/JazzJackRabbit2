
#include "Player.h"
#include "../Scene/Scene.h"
#include "Bullet.h"
#include "../Input.h"
#include "../GameManager.h"

CPlayer::CPlayer()
{
    SetTypeID<CPlayer>(); // CPlayerŸ������ ID ��Ƴ��´�. 
}

CPlayer::CPlayer(const CPlayer& Obj)    :
    CCharacter(Obj)
{
}


CPlayer::~CPlayer()
{
}

bool CPlayer::Init()
{
    CGameObject::Init();

    m_MoveSpeed = 400.f;

    SetPos(100.f, 100.f);
    SetSize(43.f, 52.f); // �ִϸ��̼��� ���۵Ǵ� ���� �ִϸ��̼� ũ��� �ڵ����� �������� ������ ���̻� �߿����� ����.
    SetPivot(0.5f, 1.f); // �� �� ���.

    SetTexture("Player", TEXT("JazzIdleRight.bmp"));
    SetColorKey(44, 102, 150);

    SetTexture("Player", TEXT("JazzIdleLeft.bmp"));
    SetColorKey(44, 102, 150);

    CreateAnimation();
    AddAnimation("JazzWalkingLeft");
    AddAnimation("JazzWalkingRight");
    AddAnimation("JazzFireLeft", false, 0.3f); // ���� �� ����.
    AddAnimation("JazzFireRight", false, 0.3f);

    SetEndFunction<CPlayer>("JazzFireRight", this, &CPlayer::AttackEnd);
    SetEndFunction<CPlayer>("JazzFireLeft", this, &CPlayer::AttackEnd);

    AddNotify<CPlayer>("JazzFireRight", 2, this, &CPlayer::Attack); // 2��° �����ӿ� ��Ƽ����
    AddNotify<CPlayer>("JazzFireLeft", 2, this, &CPlayer::Attack);

    m_vecSequenceKey[0].push_back("JazzIdleLeft");
    m_vecSequenceKey[0].push_back("JazzWalkingLeft");
    m_vecSequenceKey[0].push_back("JazzFireLeft");

    m_vecSequenceKey[1].push_back("JazzIdleRight");
    m_vecSequenceKey[1].push_back("JazzWalkingRight");
    m_vecSequenceKey[1].push_back("JazzFireRight");

    // ������ ���� �ִ� ���.
    m_PlayerDir = 1;

    m_Attack = false;

    CInput::GetInst()->AddBindFunction<CPlayer>("MoveUp", 
        Input_Type::Push, this, &CPlayer::MoveUp);

    CInput::GetInst()->AddBindFunction<CPlayer>("MoveDown",
        Input_Type::Push, this, &CPlayer::MoveDown);

    CInput::GetInst()->AddBindFunction<CPlayer>("MoveRight",
        Input_Type::Push, this, &CPlayer::MoveRight);

    CInput::GetInst()->AddBindFunction<CPlayer>("MoveLeft",
        Input_Type::Push, this, &CPlayer::MoveLeft);

    CInput::GetInst()->AddBindFunction<CPlayer>("Fire",
        Input_Type::Down, this, &CPlayer::Fire);

    CInput::GetInst()->AddBindFunction<CPlayer>("Jump",
        Input_Type::Down, this, &CPlayer::Jump);

    CInput::GetInst()->AddBindFunction<CPlayer>("Run",
        Input_Type::Down, this, &CPlayer::Run);

    return true;
}

void CPlayer::Update(float DeltaTime)
{
    CCharacter::Update(DeltaTime);

    DeltaTime *= m_TimeScale;
}

void CPlayer::PostUpdate(float DeltaTime)
{
    CCharacter::PostUpdate(DeltaTime);

    if (m_PlayerDir == 1)
    {
        // 0�� ����� ���������� �̵� �� ����ٴ� ���̴�.
        // 0���� ���� ���� �������� �̵��ߴٴ� ���̴�.
        if (m_Move.x < 0.f)
            m_PlayerDir = -1;
    }

    else
    {
        if (m_Move.x > 0.f)
            m_PlayerDir = 1;
    }

    int AnimDirIndex = 0;

    if (m_PlayerDir == -1)
        AnimDirIndex = 1;



    if (m_Move.x != 0.f || m_Move.y != 0.f) // �����ΰ��
    {
        // �̵��� ��� �������̴��� ������ ����Ѵ�.
        m_Attack = false; 
        //ChangeAnimation(m_vecSequenceKey[AnimDirIndex][1]);
    }

    else if(!m_Attack) // �������̾ƴҶ����� Idle�� ���ư���
    {
        ChangeAnimation(m_vecSequenceKey[AnimDirIndex][0]);
    }
       
}

void CPlayer::Render(HDC hDC, float DeltaTime)
{
    CCharacter::Render(hDC, DeltaTime);
}

void CPlayer::MoveUp()
{
    Vector2 Dir;
    Dir.y -= 1;

    m_Pos += Dir * 400.f * DELTA_TIME * m_TimeScale;

    //ChangeAnimation("Jazz...");
}

void CPlayer::MoveDown() 
{
    Vector2 Dir;
    Dir.y += 1;

    m_Pos += Dir * 400.f * DELTA_TIME * m_TimeScale;
    //ChangeAnimation("PlayerRightWalk");
}

void CPlayer::MoveRight()
{
    MoveDir(Vector2(1.f, 0.f));

    ChangeAnimation("JazzWalkingRight");
}

void CPlayer::MoveLeft()
{
    MoveDir(Vector2(-1.f, 0.f));

    ChangeAnimation("JazzWalkingLeft");
}

void CPlayer::Fire()
{
    if (m_Attack)
        return;

    m_Attack = true;

    int AnimDirIndex = 0;

    if (m_PlayerDir == -1)
        AnimDirIndex = 1;

    //ChangeAnimation(m_vecSequenceKey[AnimDirIndex][2]);
}

void CPlayer::Jump()
{
}

void CPlayer::Run()
{
}

void CPlayer::AttackEnd()
{
    m_Attack = false;
}

void CPlayer::Attack()
{
    CBullet* Bullet = m_Scene->CreateObject<CBullet>("Bullet");

    Bullet->SetPos(m_Pos);
}
