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

	// ���������� �ִ� ���������� ��ü���/���������̸�.exe �� ���ڿ���
	// ������ �ȴ�. '���������̸�.exe' �κ��� �ʿ䰡 ������ �������Ѵ�. 
	// �ڿ������� ���ʴ�� Ž���ϸ� /�� | ���� �κб��� ã�´�.
	//ex. ��ΰ� Bin/aa.exe �������. �� �ε����� 10��. 
	// /�� �ε����� 3. �������� ��(e ~ a����) �� 6��.  �׷��� for������ -1�Ѵ�.
	GetModuleFileName(0, Root, MAX_PATH);

	// ����� ���ϸ����� ���ڿ��� �� ���̴�. 
	int Length = lstrlen(Root);

	// ���� ���� ���ڿ����� ������ �ϳ��� �̵��ϸ� Ž��.
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

	// #ifdef : �ڿ� �ִ� ������ #define���� ���ǵǾ� �ִ�����
	// �Ǵ��ϴ� if���̴�. 
	// ������ �ܰ迡�� �ڿ� �ִ� ������ (���⼭�� UNICODE)#define���� ���ǵǾ��ִ���
	// �Ǵ�.
#ifdef UNICODE

	// �����ڵ�� �Ǿ��ִ� ���ڿ��� ��Ƽ����Ʈ�� �ٲٱ� ���� ���� ���´�.
	// WideCharToMultiByte : �����ڵ带 ��Ƽ����Ʈ�� �ٲ��ִ� ��.
	// 1������ : �ڵ������� �ʿ�. CP_ACP (������ �ƽ�Ű �ڵ� ������)  
	// 2������ : �÷���. 0
	// 3������ : �ٲ��� ���ڿ�
	// 4������ : �ٲ��� ���ڿ� ����. -1�̸� ��ü�� �ٲ۴�.
	// 5������ ~ 8�����ڰ� 0�� ��� : 3��° ���ڸ� ���ڿ��� ��Ƽ����Ʈ�� �ٲٱ� ���� ���ڿ� ������ ���ϵ�.
	int PathLength = WideCharToMultiByte(CP_ACP, 0, Info->Path, -1,
		0, 0, 0, 0);
	// ���������� �ٲ۴�. 5��°���ڿ� 6��°���� ���̸�ŭ����.
	WideCharToMultiByte(CP_ACP, 0, Info->Path, -1,
		Info->PathMultibyte, PathLength, 0, 0);

#else

	strcpy_s(info->PathMultibyte, Info->Path);

#endif // UNICODE

	m_mapPath.insert(std::make_pair(ROOT_PATH, Info));

	// ROOT_PATH ���ٰ� �ڿ� Texture/ �ٿ��ִ� �ý���.
	AddPath(TEXTURE_PATH, TEXT("Texture/"));

	return true;
}

bool CPathManager::AddPath(const std::string& Name, const TCHAR* Path, const std::string& BasePathName)
{
	if (FindPath(Name)) // �� �̸����� ��ϵ� �� �ִٸ�.
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
