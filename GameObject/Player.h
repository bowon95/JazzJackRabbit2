#pragma once

#include "Character.h"

class CPlayer :
    public CCharacter
{
	friend class CScene;

protected:
	CPlayer();
	CPlayer(const CPlayer& Obj);
	virtual ~CPlayer();

private:
	int m_PlayerDir; // 플레이어가 보는 방향
	std::vector<std::string>	m_vecSequenceKey[2];

	bool m_Attack; 

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);

private:
	void MoveUp();
	void MoveDown();
	void MoveRight();
	void MoveLeft();
	void Fire();
	void Jump();
	void Run();

private:
	void AttackEnd();
	void Attack();

};

