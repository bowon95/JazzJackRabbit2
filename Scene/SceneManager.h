#pragma once

#include "../GameInfo.h"
#include "../SingletonMacro.h"

class CSceneManager
{
private:
	// SceneManager가 관리하는 Scene. Scene마다 오브젝트 가지고 있게 한다. 
	class CScene* m_Scene;

public:
	bool Init();
	// 반환타입bool : Scene이 교체되는지 여부 판단을 위해.
	bool Update(float DeltaTime);
	void PostUpdate(float DeltaTime);
	void Render(HDC hDC, float DeltaTime);

public:
	template <typename T>// 어떤 씬을 만들지 모르니 템플릿
	bool CreateScene()
	{
		T* Scene = new T;
		
		if (!Scene->Init())
		{
			SAFE_DELETE(Scene);
			return false;
		}

		if (!m_Scene)
			m_Scene = (CScene*)Scene;

		return true;
	}


	DECLARE_SINGLE(CSceneManager);

};

