#pragma once
#include "GameObject.h"
class CBullet :
    public CGameObject
{
	friend class CScene;

protected:
	CBullet();
	CBullet(const CBullet& Obj);
	virtual ~CBullet();

private:
	int		m_Dir;
	float	m_Angle;
	float	m_Distance; // ÃÑ¾Ë »ç°Å¸®

public:
	void SetDistance(float Dist)
	{
		m_Distance = Dist;
	}

	void SetDir(int Dir)
	{
		m_Dir = Dir;
	}

	void SetAngle(float Angle)
	{
		m_Angle = Angle;
	}

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
};

