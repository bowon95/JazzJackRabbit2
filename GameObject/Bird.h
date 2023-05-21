#pragma once
#include "Monster.h"
class CBird :
	public CMonster
{
	friend class CScene;

protected:
	CBird();
	CBird(const CBird& Obj);
	virtual ~CBird();

private:
	Vector2		m_Dir;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
};

