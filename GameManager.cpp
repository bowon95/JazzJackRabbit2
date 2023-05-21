#include "GameManager.h"
#include "resource.h"
#include "Timer.h"
#include "GameObject/Player.h"
#include "Scene/SceneManager.h"
#include "Input.h"
#include "Resource/ResourceManager.h"
#include "PathManager.h"

DEFINITION_SINGLE(CGameManager)
bool CGameManager::m_Loop = true; // static ���������.

CGameManager::CGameManager()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
     //_CrtSetBreakAlloc(100);
}

CGameManager::~CGameManager()
{
    CSceneManager::DestroyInst();

    CPathManager::DestroyInst();

    CInput::DestroyInst();

    CResourceManager::DestroyInst();

    SAFE_DELETE(m_Timer);

    SelectObject(m_hBackDC, m_hBackPrevBmp);
    DeleteObject(m_hBackBmp);
    DeleteObject(m_hBackDC);


    ReleaseDC(m_hWnd, m_hDC); // �� �ڵ��� �̿��ؼ� ������ �� DC �� �����ض�.
}

bool CGameManager::Init(HINSTANCE hInst)
{
	m_hInst = hInst;

    m_RS.Width = 1280;
    m_RS.Height = 720;

	Register();

	Create();

    //��ΰ����� �ʱ�ȭ
    if (!CPathManager::GetInst()->Init())
        return false;

    // ���ҽ� ������ �ʱ�ȭ
    if (!CResourceManager::GetInst()->Init())
        return false;
    
    // �Է� ������ �ʱ�ȭ
    if (!CInput::GetInst()->Init())
        return false;

    // ��� �����ڻ���
    if (!CSceneManager::GetInst()->Init())
        return false;

    // Ÿ�̸� ����
    m_Timer = new CTimer;
    m_Timer->Init();

    // DC�� ���´�.
    m_hDC = GetDC(m_hWnd); //m_hWnd <- �� ������â�� ���� �׸��� ���� ������!

    m_FrameLimitTime = 1 / 60.f;

    // ����۸� �����.
    m_hBackDC = CreateCompatibleDC(m_hDC);

    // ������ â�� ũ��� ������ ũ���� ����ۿ� ��Ʈ���� ������ش�.
    m_hBackBmp = CreateCompatibleBitmap(m_hDC, m_RS.Width, m_RS.Height);

    m_hBackPrevBmp = (HBITMAP)SelectObject(m_hBackDC, m_hBackBmp);

    m_TimeScale = 1.f;

	return true;
}

int CGameManager::Run()
{
    MSG msg;

    while (m_Loop)
    {

        // PeekMessage : �� �Լ��� �޼��� ť���� �޼����� ��������
        // �Լ��̴�. ��, �� �Լ��� �޼��� ť�� ������� ��� false
        // �� ��ȯ�ϸ� �ٷ� ���������� �ȴ�.
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);

            DispatchMessage(&msg);
        }
        // �޼��� ť�� ������� ��� ���۵ȴ�. ��, �������� ����Ÿ�ӽ�
       // �� else ������ ���۵Ǳ� ������ ���⿡ ���� ���ӷ�����
       // �ۼ��ϸ� �ȴ�.
        else
        {
            Logic();
        }
    }
    return (int)msg.wParam;
}

void CGameManager::Logic()
{ 
    m_Timer->Update(); //  �Ź�ȣ��ǰ� ���� Ÿ�̸Ӹ� ������ ��ŸŸ�� �� FPS �� ���Ѵ�.

    float DeltaTime = m_Timer->GetDeltaTime() * m_TimeScale;

    m_DeltaTime = DeltaTime;

    Input(DeltaTime);

    // Scene�� ��ü�� ��� ó������ �ٽ� ���۽�Ų��. 
    if (Update(DeltaTime))
        return;

    PostUpdate(DeltaTime);

    Collision(DeltaTime);

    Render(DeltaTime);
}

void CGameManager::Input(float DeltaTime)
{
    CInput::GetInst()->Update(DeltaTime);
}

bool CGameManager::Update(float DeltaTime)
{
    CResourceManager::GetInst()->Update();

    return CSceneManager::GetInst()->Update(DeltaTime);
}

void CGameManager::PostUpdate(float DeltaTime)
{
    CSceneManager::GetInst()->PostUpdate(DeltaTime);
}

void CGameManager::Collision(float DeltaTime)
{
}

void CGameManager::Render(float DeltaTime)
{
    //Rectangle(m_hBackDC, -1, 1, m_RS.Width + 1, m_RS.Height + 1); // �� �簢����
    // m_hBackDC�� ������ �մ� ��� �� ������.
    // ��ġ�� 0,0�����ϸ� �׵θ����α��� �׷��� �� �ֱ� ������ �����Ӱ�
    //1�ȼ��� �߰��� ����ش�.

    CSceneManager::GetInst()->Render(m_hBackDC, DeltaTime);

    // ������ ����ۿ� ��� ������Ʈ�� ����� �Ǿ���.
    // ���������� ����۸� ��ǥ�� ���ۿ� �׷�����.
    BitBlt(m_hDC, 0, 0, m_RS.Width, m_RS.Height, m_hBackDC, 0, 0, SRCCOPY);

}

void CGameManager::Register()
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;

    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;

    wcex.hInstance = m_hInst;

    wcex.hIcon = LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_ICON1));

    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    wcex.lpszMenuName = nullptr;

    wcex.lpszClassName = TEXT("JazzJackRabbit2");

    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

    RegisterClassExW(&wcex);
}

bool CGameManager::Create()
{
    m_hWnd = CreateWindowW(TEXT("JazzJackRabbit2"),
        TEXT("JazzJackRabbit2"), WS_OVERLAPPEDWINDOW,
        100, 0, 1280, 720, nullptr, nullptr, m_hInst, nullptr);

    if (!m_hWnd)
    {
        return false;  
    }

    RECT    rc = { 0, 0, m_RS.Width, m_RS.Height};

    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

    MoveWindow(m_hWnd, 50, 50, rc.right - rc.left,
        rc.bottom - rc.top, TRUE);
  
    ShowWindow(m_hWnd, SW_SHOW);

    UpdateWindow(m_hWnd);

    return true;
}

LRESULT CGameManager::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        m_Loop = false; // ���� ��������.
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
 