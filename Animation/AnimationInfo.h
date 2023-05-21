#pragma once

#include "../GameInfo.h"

struct AnimationNotify
{
	int	Frame; // 몇 번째 프레임이 등록할것인지
	bool Call; // 현재모션이 동작되고있을 때 함수가 호출되었는지 여부
	std::function<void()>	Function;

	AnimationNotify() :
		Frame(0),
		Call(false)
	{
	}
	
};

/*
애니메이션 시퀀스를 하나 가지고 있으면서 해당 애니메이션을 총 몇 초에 걸쳐서 한번
재생을 할 것인지 이 애니메이션이 계속 반복해서 재생하는지 등을 정의해두는 객체이다.
*/
class CAnimationInfo
{
	friend class CAnimation;
	friend class CGameObject;

private:
	CAnimationInfo();
	~CAnimationInfo();

private:
	CSharedPtr<class CAnimationSequence>	m_Sequence;
	int		m_Frame; // 현재 애니메이션이 동작되는 프레임. 현재 몇 번째 프레임이 돌아가고있는지 저장
	float	m_Time; // 애니메이션 프레임을 증가시켜주기 위한 시간값.

	// 한 프레임이 증가하기 위한 시간. ex 프레임이 3개짜린데 
	// 프레임 3개를 한바퀴 다도는데 1초가 걸리면 프레임 1개에 걸리는 시간은 1/3 이다. 
	// 그 1/3 을 m_FrameTime에 저장한다. 
	float	m_FrameTime; 
	float	m_PlayTime; // 모션 한 번이 동작되기 위한 시간.
	float	m_PlayScale; // 재생속도 배율.
	bool	m_Loop; // 반복해서 재생해야하는지 여부.
	bool	m_Reverse; // 역재생여부.
	std::function<void()>	m_EndFunction; // 애니메이션이 끝날때마다 호출될 함수등록.
	std::vector<AnimationNotify*>	m_vecNotify;

public:
	template <typename T>
	void SetEndFunction(T* Obj, void(T::* Func)())
	{
		m_EndFunction = std::bind(Func, Obj);
	}

	template <typename T>
	void AddNotify(int Frame, T* Obj, void(T::* Func)())
	{
		AnimationNotify* Notify = new AnimationNotify;

		Notify->Frame = Frame;
		Notify->Function = std::bind(Func, Obj);

		m_vecNotify.push_back(Notify);

	}
};

