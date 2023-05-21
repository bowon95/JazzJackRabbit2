#pragma once
#include "Monster.h"
class CTurtle :
	public CMonster
{
	friend class CScene;

protected:
	CTurtle();
	CTurtle(const CTurtle& Obj);
	virtual ~CTurtle();

private:
	Vector2		m_Dir;
	float	m_FireTime;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
};

