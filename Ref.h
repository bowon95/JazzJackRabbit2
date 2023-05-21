#pragma once

#include "GameInfo.h"

class CRef
{
public:
	CRef();
	CRef(const CRef& ref); // 복사생성자
	virtual ~CRef();

protected:
	int		m_RefCount;
	std::string m_Name;
	std::string m_TypeName;
	size_t	m_TypeID; // 런타임도중에 클래스 타입알기 위해
	bool	m_Enable;	// 활성, 비활성
	bool	m_Active;	// 살아 있는지 죽었는지

public:
	void AddRef(); // 카운트 추가
	int Release(); // 카운트 감소

public:
	int GetRefCount()	const
	{
		return m_RefCount;
	}
public:
	bool GetEnable()	const
	{
		return m_Enable;
	}

	bool GetActive()	const
	{
		return m_Active;
	}

	size_t GetTypeID()	const
	{
		return m_TypeID;
	}

	const std::string& GetTypeName()	const
	{
		return m_TypeName;
	}

	const std::string& GetName()	const
	{
		return m_Name;
	}

	void SetEnable(bool Enable)
	{
		m_Enable = Enable;
	}

	void SetActive(bool Active)
	{
		m_Active = Active;
	}

	void SetName(const std::string& Name)
	{
		m_Name = Name;
	}

	template <typename T>
	bool CheckTypeID() const
	{
		//m_TypeID가 T타입인지아닌지 bool (참거짓)으로 판별해줌
		return m_TypeID == typeid(T).hash_code();
	}

public:
	template<typename T>
	void SetTypeID()
	{
		// T가 어떤 타입인지 바로 문자열로나옴.ex. int 넣으면 int 라고 문자열 나옴.
		m_TypeName = typeid(T).name();
		// 모든 클래스들은 어떤 클래스인지 식별하기 위한고유의 번호가 있음. 식별번호얻어온다.
		m_TypeID = typeid(T).hash_code();
	}
};

