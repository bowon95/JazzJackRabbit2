#pragma once
#include "Monster.h"
class CDragon :
    public CMonster
{
	friend class CScene;

protected:
	CDragon();
	CDragon(const CDragon& Obj);
	virtual ~CDragon();

private:
	Vector2		m_Dir;
	float	    m_FireTime;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
};

