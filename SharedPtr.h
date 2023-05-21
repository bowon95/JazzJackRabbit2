#pragma once

template <typename T>
class CSharedPtr
{
public:
	CSharedPtr() :
		m_Ptr(nullptr)
	{
	}

	CSharedPtr(const CSharedPtr<T>& ptr)
	{
		m_Ptr = ptr.m_Ptr;

		if (m_Ptr)
			m_Ptr->AddRef();
	}

	CSharedPtr(T* ptr)
	{
		m_Ptr = ptr;

		if (m_Ptr)
			m_Ptr->AddRef();
	}

	~CSharedPtr()
	{
		if (m_Ptr)
			m_Ptr->Release();
	}

private:
	T* m_Ptr;

public:
	void operator = (const CSharedPtr<T>& ptr)
	{
		// 기존에 참조하고 있던 객체가 있을 경우 카운트를 1 감소한다.
		if (m_Ptr)
			m_Ptr->Release();

		m_Ptr = ptr.m_Ptr;

		if (m_Ptr)
			m_Ptr->AddRef();
	}

	void operator = (T* ptr)
	{
		// 기존에 참조하고 있던 객체가 있을 경우 카운트를 1 감소한다.
		if (m_Ptr)
			m_Ptr->Release();

		m_Ptr = ptr;

		if (m_Ptr)
			m_Ptr->AddRef();
	}

	bool operator == (const CSharedPtr<T>& ptr)	const
	{
		return m_Ptr == ptr.m_Ptr;
	}

	bool operator == (T* ptr)	const
	{
		return m_Ptr == ptr;
	}

	bool operator != (const CSharedPtr<T>& ptr)	const
	{
		return m_Ptr != ptr.m_Ptr;
	}

	bool operator != (T* ptr)	const
	{
		return m_Ptr != ptr;
	}

	operator T* ()	const // 컨벌젼. 사용하는 객체 자체를  m_Ptr로 인식시키는 기능.
	{
		return m_Ptr;
	}

	T* operator -> ()	const
	{
		return m_Ptr;
	}

	T* operator * ()	const // 역참조해도 m_Ptr 리턴.
	{
		return m_Ptr;
	}

	T* Get()	const
	{
		return m_Ptr;
	}
};

