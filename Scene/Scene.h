#pragma once

#include "../GameInfo.h"

class CScene
{
	friend class CSceneManager; // 씬매니저만 처리가능
// 내가 만든 규칙에 맞게 쓰게끔 유도하기 위해 protected로 쓴다. 
// 문제가 생길 확률을 최소화한다.
protected:
	CScene();
	virtual ~CScene();

private:
	class CSceneResource* m_Resource;
	class CCamera* m_Camera;

protected:
	std::list<CSharedPtr<class CGameObject>>	m_ObjList[(int)ERender_Layer::Max]; // 오브젝트 리스트.
	CSharedPtr<class CGameObject>	m_Player; // 플레이어 얻어다 쓰는 경우 많기 때문에 만듦.


public:
	class CCamera* GetCamera()	const
	{
		return m_Camera;
	}

	class CSceneResource* GetSceneResource()	const
	{
		return m_Resource;
	}

	class CGameObject* GetPlayer()	const
	{
		return m_Player;
	}

	void SetPlayer(class CGameObject* Player);

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);

public:
	template <typename T>
	T* CreateObject(const std::string& Name = "GameObject") // 이름 안넣으면 GameObject로 만들어짐
	{
		T* Obj = new T;

		Obj->SetName(Name);
		Obj->m_Scene = this; //GameObject가 자신이 소속된 Scene을 알게됨. Init전에 Scene을 가지고 있게 됨.  

		if (!Obj->Init())
		{
			SAFE_DELETE(Obj);
			return nullptr;
		}

		m_ObjList[(int)Obj->GetRenderLayer()].push_back((CGameObject*)Obj);

		return Obj;
	}



private:
	static bool SortY(const CSharedPtr<class CGameObject>& Src, const CSharedPtr<class CGameObject>& Dest);


};

