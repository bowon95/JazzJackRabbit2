#pragma once
#include "Monster.h"
class CQueenEarlong :
    public CMonster
{
	friend class CScene;

protected:
	CQueenEarlong();
	CQueenEarlong(const CQueenEarlong& Obj);
	virtual ~CQueenEarlong();

private:
	Vector2		m_Dir;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
};


