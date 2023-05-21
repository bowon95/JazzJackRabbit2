#include "Ref.h"

CRef::CRef()	:
	m_RefCount(0),
	m_Enable(true),
	m_Active(true),
	m_TypeID(0)
{
}

CRef::CRef(const CRef& ref) :
	m_RefCount(0),
	m_TypeName(ref.m_TypeName),
	m_TypeID(ref.m_TypeID),
	m_Enable(ref.m_Enable),
	m_Active(ref.m_Active)
{
}

CRef::~CRef()
{
}

void CRef::AddRef()
{
	++m_RefCount;
}

int CRef::Release()
{
	--m_RefCount;

	if (m_RefCount <= 0)
	{
		delete this; // 0 �Ǵ� ���� �ڱ��ڽ� �����.
		return 0;
	}

	return m_RefCount;
}
