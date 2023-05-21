#include "GameManager.h"
#include "resource.h"
#include "Timer.h"
#include "GameObject/Player.h"
#include "Scene/SceneManager.h"
#include "Input.h"
#include "Resource/ResourceManager.h"
#include "PathManager.h"

DEFINITION_SINGLE(CGameManager)
bool CGameManager::m_Loop = true; // static 멤버변수라.

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


    ReleaseDC(m_hWnd, m_hDC); // 이 핸들을 이용해서 생성한 이 DC 를 제거해라.
}

bool CGameManager::Init(HINSTANCE hInst)
{
	m_hInst = hInst;

    m_RS.Width = 1280;
    m_RS.Height = 720;

	Register();

	Create();

    //경로관리자 초기화
    if (!CPathManager::GetInst()->Init())
        return false;

    // 리소스 관리자 초기화
    if (!CResourceManager::GetInst()->Init())
        return false;
    
    // 입력 관리자 초기화
    if (!CInput::GetInst()->Init())
        return false;

    // 장면 관리자생성
    if (!CSceneManager::GetInst()->Init())
        return false;

    // 타이머 생성
    m_Timer = new CTimer;
    m_Timer->Init();

    // DC를 얻어온다.
    m_hDC = GetDC(m_hWnd); //m_hWnd <- 이 윈도우창에 대한 그리기 도구 가져와!

    m_FrameLimitTime = 1 / 60.f;

    // 백버퍼를 만든다.
    m_hBackDC = CreateCompatibleDC(m_hDC);

    // 윈도우 창의 크기와 동일한 크기의 백버퍼용 비트맵을 만들어준다.
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

        // PeekMessage : 이 함수도 메세지 큐에서 메세지를 꺼내오는
        // 함수이다. 단, 이 함수는 메세지 큐가 비어있을 경우 false
        // 를 반환하며 바로 빠져나오게 된다.
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);

            DispatchMessage(&msg);
        }
        // 메세지 큐가 비어있을 경우 동작된다. 즉, 윈도우의 데드타임시
       // 이 else 구문이 동작되기 때문에 여기에 실제 게임로직을
       // 작성하면 된다.
        else
        {
            Logic();
        }
    }
    return (int)msg.wParam;
}

void CGameManager::Logic()
{ 
    m_Timer->Update(); //  매번호출되게 만들어서 타이머를 갱신해 델타타임 및 FPS 를 구한다.

    float DeltaTime = m_Timer->GetDeltaTime() * m_TimeScale;

    m_DeltaTime = DeltaTime;

    Input(DeltaTime);

    // Scene이 교체될 경우 처음부터 다시 동작시킨다. 
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
    //Rectangle(m_hBackDC, -1, 1, m_RS.Width + 1, m_RS.Height + 1); // 이 사각형이
    // m_hBackDC의 기존에 잇던 모든 걸 지워줌.
    // 위치를 0,0으로하면 테두리라인까지 그려질 수 있기 때문에 여유롭게
    //1픽셀을 추가로 잡아준다.

    CSceneManager::GetInst()->Render(m_hBackDC, DeltaTime);

    // 위에서 백버퍼에 모든 오브젝트가 출력이 되었다.
    // 마지막으로 백버퍼를 주표면 버퍼에 그려낸다.
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
        m_Loop = false; // 루프 빠져나감.
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
 