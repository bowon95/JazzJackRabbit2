#pragma once

#include "../GameInfo.h"

class CScene
{
	friend class CSceneManager; // ���Ŵ����� ó������
// ���� ���� ��Ģ�� �°� ���Բ� �����ϱ� ���� protected�� ����. 
// ������ ���� Ȯ���� �ּ�ȭ�Ѵ�.
protected:
	CScene();
	virtual ~CScene();

private:
	class CSceneResource* m_Resource;
	class CCamera* m_Camera;

protected:
	std::list<CSharedPtr<class CGameObject>>	m_ObjList[(int)ERender_Layer::Max]; // ������Ʈ ����Ʈ.
	CSharedPtr<class CGameObject>	m_Player; // �÷��̾� ���� ���� ��� ���� ������ ����.


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
	T* CreateObject(const std::string& Name = "GameObject") // �̸� �ȳ����� GameObject�� �������
	{
		T* Obj = new T;

		Obj->SetName(Name);
		Obj->m_Scene = this; //GameObject�� �ڽ��� �Ҽӵ� Scene�� �˰Ե�. Init���� Scene�� ������ �ְ� ��.  

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

