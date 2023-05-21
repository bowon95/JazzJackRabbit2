#pragma once
#include "Monster.h"
class CBat :
	public CMonster
{
	friend class CScene;

protected:
	CBat();
	CBat(const CBat& Obj);
	virtual ~CBat();

private:
	Vector2		m_Dir;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
};

