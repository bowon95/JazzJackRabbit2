#pragma once

#include "../GameInfo.h"

struct AnimationNotify
{
	int	Frame; // �� ��° �������� ����Ұ�����
	bool Call; // �������� ���۵ǰ����� �� �Լ��� ȣ��Ǿ����� ����
	std::function<void()>	Function;

	AnimationNotify() :
		Frame(0),
		Call(false)
	{
	}
	
};

/*
�ִϸ��̼� �������� �ϳ� ������ �����鼭 �ش� �ִϸ��̼��� �� �� �ʿ� ���ļ� �ѹ�
����� �� ������ �� �ִϸ��̼��� ��� �ݺ��ؼ� ����ϴ��� ���� �����صδ� ��ü�̴�.
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
	int		m_Frame; // ���� �ִϸ��̼��� ���۵Ǵ� ������. ���� �� ��° �������� ���ư����ִ��� ����
	float	m_Time; // �ִϸ��̼� �������� ���������ֱ� ���� �ð���.

	// �� �������� �����ϱ� ���� �ð�. ex �������� 3��¥���� 
	// ������ 3���� �ѹ��� �ٵ��µ� 1�ʰ� �ɸ��� ������ 1���� �ɸ��� �ð��� 1/3 �̴�. 
	// �� 1/3 �� m_FrameTime�� �����Ѵ�. 
	float	m_FrameTime; 
	float	m_PlayTime; // ��� �� ���� ���۵Ǳ� ���� �ð�.
	float	m_PlayScale; // ����ӵ� ����.
	bool	m_Loop; // �ݺ��ؼ� ����ؾ��ϴ��� ����.
	bool	m_Reverse; // ���������.
	std::function<void()>	m_EndFunction; // �ִϸ��̼��� ���������� ȣ��� �Լ����.
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

