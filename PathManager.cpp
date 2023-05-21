#include "PathManager.h"

DEFINITION_SINGLE(CPathManager)

CPathManager::CPathManager()
{
}

CPathManager::~CPathManager()
{
	auto	iter = m_mapPath.begin();
	auto	iterEnd = m_mapPath.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE(iter->second);
	}
}

bool CPathManager::Init()
{
	TCHAR	Root[MAX_PATH] = {};

	// 실행파일이 있는 폴더까지의 전체경로/실행파일이름.exe 로 문자열이
	// 나오게 된다. '실행파일이름.exe' 부분은 필요가 없으니 날려야한다. 
	// 뒤에서부터 차례대로 탐색하며 /나 | 이전 부분까지 찾는다.
	//ex. 경로가 Bin/aa.exe 라고하자. 총 인덱스는 10개. 
	// /의 인덱스는 3. 지워야할 거(e ~ a까지) 총 6개.  그래서 for문에서 -1한다.
	GetModuleFileName(0, Root, MAX_PATH);

	// 경로의 제일마지막 문자열이 될 것이다. 
	int Length = lstrlen(Root);

	// 제일 뒤의 문자열부터 앞으로 하나씩 이동하며 탐색.
	for (int i = Length - 1; i >= 0; --i)
	{
		if (Root[i] == '/' || Root[i] == '\\')
		{
			memset(&Root[i + 1], 0, sizeof(TCHAR) * (Length - i - 1));
			break;
		}

	}

	PathInfo* Info = new PathInfo;

	lstrcpy(Info->Path, Root);

	// #ifdef : 뒤에 있는 내용이 #define으로 정의되어 있는지를
	// 판단하는 if문이다. 
	// 컴파일 단계에서 뒤에 있는 내용이 (여기서는 UNICODE)#define으로 정의되어있는지
	// 판단.
#ifdef UNICODE

	// 유니코드로 되어있는 문자열을 멀티바이트로 바꾸기 위한 수를 얻어온다.
	// WideCharToMultiByte : 유니코드를 멀티바이트로 바꿔주는 것.
	// 1번인자 : 코드페이지 필요. CP_ACP (무조건 아스키 코드 페이지)  
	// 2번인자 : 플래그. 0
	// 3번인자 : 바꿔줄 문자열
	// 4번인자 : 바꿔줄 문자열 갯수. -1이면 전체를 바꾼다.
	// 5번인자 ~ 8번인자가 0일 경우 : 3번째 인자를 문자열을 멀티바이트로 바꾸기 위한 문자열 갯수가 리턴됨.
	int PathLength = WideCharToMultiByte(CP_ACP, 0, Info->Path, -1,
		0, 0, 0, 0);
	// 최종적으로 바꾼다. 5번째인자에 6번째인자 길이만큼으로.
	WideCharToMultiByte(CP_ACP, 0, Info->Path, -1,
		Info->PathMultibyte, PathLength, 0, 0);

#else

	strcpy_s(info->PathMultibyte, Info->Path);

#endif // UNICODE

	m_mapPath.insert(std::make_pair(ROOT_PATH, Info));

	// ROOT_PATH 얻어다가 뒤에 Texture/ 붙여주는 시스템.
	AddPath(TEXTURE_PATH, TEXT("Texture/"));

	return true;
}

bool CPathManager::AddPath(const std::string& Name, const TCHAR* Path, const std::string& BasePathName)
{
	if (FindPath(Name)) // 이 이름으로 등록된 게 있다면.
		return false;
	
	const PathInfo* BasePath = FindPath(BasePathName);

	PathInfo* Info = new PathInfo;

	if (BasePath)
		lstrcpy(Info->Path, BasePath->Path);

	lstrcat(Info->Path, Path);

#ifdef UNICODE

	int PathLength = WideCharToMultiByte(CP_ACP, 0, Info->Path, -1,
		0, 0, 0, 0);

	WideCharToMultiByte(CP_ACP, 0, Info->Path, -1,
		Info->PathMultibyte, PathLength, 0, 0);

#else

	strcpy_s(info->PathMultibyte, Info->Path);

#endif // UNICODE

	m_mapPath.insert(std::make_pair(Name, Info));

	return true;
}

const PathInfo* CPathManager::FindPath(const std::string& Name)
{
	auto iter = m_mapPath.find(Name);

	if (iter == m_mapPath.end())
		return nullptr;

	return iter->second;
}
