#pragma once

#include "SingletonMacro.h"
#include "GameInfo.h"

struct PathInfo
{
	TCHAR	Path[MAX_PATH];
	char	PathMultibyte[MAX_PATH];

	PathInfo()	:
		Path{},
		PathMultibyte{}
	{
	}
};

class CPathManager
{
private:
	// �������� ��θ� �����صΰ� �ʿ��� ������ �� �� �ְԲ�. 
	// Ű���� ���ڿ�, value���� PathInfo* .
	std::unordered_map<std::string, PathInfo*>		m_mapPath;

public:
	bool Init();
	// m_mapPath �� ��θ� ����ϴ� �Լ� 
	bool AddPath(const std::string& Name, const TCHAR* Path,
		const std::string& BasePathName = ROOT_PATH); // ��Ʈ�н��� �������� ���� ����.
	const PathInfo* FindPath(const std::string& Name);

	DECLARE_SINGLE(CPathManager);
};

 