#pragma once

#include "../GameInfo.h"
#include "../SingletonMacro.h"

class CSceneManager
{
private:
	// SceneManager�� �����ϴ� Scene. Scene���� ������Ʈ ������ �ְ� �Ѵ�. 
	class CScene* m_Scene;

public:
	bool Init();
	// ��ȯŸ��bool : Scene�� ��ü�Ǵ��� ���� �Ǵ��� ����.
	bool Update(float DeltaTime);
	void PostUpdate(float DeltaTime);
	void Render(HDC hDC, float DeltaTime);

public:
	template <typename T>// � ���� ������ �𸣴� ���ø�
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

