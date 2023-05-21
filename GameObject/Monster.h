#pragma once

#include "Character.h"

class CMonster	:
	public CCharacter
{
	friend class CScene;

protected:
	CMonster();
	CMonster(const CMonster& Obj);
	virtual ~CMonster();

private:
	Vector2		m_Dir;
	float	m_FireTime; // 일정시간에 총알 발사

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
};

