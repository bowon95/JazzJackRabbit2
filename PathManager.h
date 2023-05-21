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
	// 여러개의 경로를 저장해두고 필요할 때마다 쓸 수 있게끔. 
	// 키값은 문자열, value값은 PathInfo* .
	std::unordered_map<std::string, PathInfo*>		m_mapPath;

public:
	bool Init();
	// m_mapPath 에 경로를 등록하는 함수 
	bool AddPath(const std::string& Name, const TCHAR* Path,
		const std::string& BasePathName = ROOT_PATH); // 루트패스를 기준으로 넣을 것임.
	const PathInfo* FindPath(const std::string& Name);

	DECLARE_SINGLE(CPathManager);
};

 