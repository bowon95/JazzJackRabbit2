#include "Input.h"

DEFINITION_SINGLE(CInput)

CInput::CInput()
{
}

CInput::~CInput()
{
	//Input �� �������� ����� Ű �� ����
	{
		auto iter = m_mapKeyState.begin();
		auto iterEnd = m_mapKeyState.end();

		for (; iter != iterEnd; ++iter)
		{
			SAFE_DELETE(iter->second);
		}

		m_mapKeyState.clear();
	}

	{
		auto iter = m_mapBindKey.begin();
		auto iterEnd = m_mapBindKey.end();

		for (; iter != iterEnd; ++iter)
		{
			for (int i = 0; i < (int)Input_Type::End; ++i)
			{
				size_t	Size = iter->second->vecFunction[i].size();

				for (size_t j = 0; j < Size; ++j)
				{
					SAFE_DELETE(iter->second->vecFunction[i][j]);
				}
			}

			SAFE_DELETE(iter->second);
		}

		m_mapBindKey.clear();
	}
}

bool CInput::Init()
{
	// ĳ���� ��ǲ
	AddBindKey("MoveUp", VK_UP);
	AddBindKey("MoveDown", VK_DOWN);
	AddBindKey("MoveRight", VK_RIGHT);
	AddBindKey("MoveLeft", VK_LEFT);
	AddBindKey("Fire", VK_SPACE);  
	AddBindKey("Jump", VK_CONTROL); 
	AddBindKey("Run", VK_SHIFT); 

	AddBindKey("Select", VK_RETURN);
	//(?) AddBindKey("", VK_ESCAPE); ������ ��ŵ�̳� ���� �� �޴�â �Ǵ� 
			// ���ư���
	// �����̽��ٰ� Ȯ�� ��ư�̸�..?
	
	m_Ctrl = false;

	return true;
}

void CInput::Update(float DeltaTime)
{
	UpdateMouse(DeltaTime);

	UpdateKeyState(DeltaTime);

	UpdateBindKey(DeltaTime);
}

void CInput::UpdateMouse(float DeltaTime)
{
}

void CInput::UpdateKeyState(float DeltaTime)
{
	if (GetAsyncKeyState(VK_CONTROL) & 0x8000)
		m_Ctrl = true;

	else
		m_Ctrl = false;

	auto	iter = m_mapKeyState.begin();
	auto	iterEnd = m_mapKeyState.end();

	for (; iter != iterEnd; ++iter)
	{
		bool KeyPush = false;

		if (GetAsyncKeyState(iter->second->key) & 0x8000)
			KeyPush = true;

		// Ű�� ������ ���
		if (KeyPush)
		{
			// Down�� Push ��� false��� �� Ű�� ���� ���� ���̴�. 
			// �׷��Ƿ� �� �� true �� �����Ѵ�.
			if (!iter->second->Down && !iter->second->Push) 
			{
				iter->second->Down = true;
				iter->second->Push = true;
			}
			// Down�� Push �� �� �ϳ��� true��� Down�� false�� �Ǿ���Ѵ�.
			// Push�� ������ true�� ����Ǿ���.
			else
				iter->second->Down = false;
		}
		// Ű�� �� �������� ��� Push�� true���
		// ���� �����ӿ� Ű�� ������ �ִٰ� ���� �������ٴ� ���̴�.
		else if (iter->second->Push)
		{
			iter->second->Up = true;
			iter->second->Push = false;
			iter->second->Down = false;
		}

		else if (iter->second->Up)
			iter->second->Up = false;
	}	
}

void CInput::UpdateBindKey(float DeltaTime)
{
	auto	iter = m_mapBindKey.begin();
	auto	iterEnd = m_mapBindKey.end();

	for (; iter != iterEnd; ++iter)
	{
		if (iter->second->key->Down &&
			iter->second->Ctrl == m_Ctrl)
		{
			size_t Size = iter->second->vecFunction[(int)Input_Type::Down].size();

			for (size_t i = 0; i < Size; ++i)
			{
				iter->second->vecFunction[(int)Input_Type::Down][i]->func();
			}
		}

		if (iter->second->key->Push &&
			iter->second->Ctrl == m_Ctrl)
		{
			size_t Size = iter->second->vecFunction[(int)Input_Type::Push].size();

			for (size_t i = 0; i < Size; ++i)
			{
				iter->second->vecFunction[(int)Input_Type::Push][i]->func();
			}
		}

		if (iter->second->key->Up &&
			iter->second->Ctrl == m_Ctrl)
		{
			size_t Size = iter->second->vecFunction[(int)Input_Type::Up].size();

			for (size_t i = 0; i < Size; ++i)
			{
				iter->second->vecFunction[(int)Input_Type::Up][i]->func();
			}
		}
	}
}
 
void CInput::SetKeyCtrl(const std::string& Name, bool Ctrl)
{
	BindKey* Key = FindBindKey(Name);

	if (!Key)
		return;

	Key->Ctrl = Ctrl;
}

KeyState* CInput::FindKeyState(unsigned char Key)
{
	auto	iter = m_mapKeyState.find(Key);

	// iter�� end�� ��ȯ�ϸ� ��ã�Ҵٴ� ���.
	if (iter == m_mapKeyState.end())
		return nullptr;
	// iter->first :  key,
	// iter->second : value ����ִ�.
	return iter->second;
}

BindKey* CInput::FindBindKey(const std::string& Name)
{
	auto	iter = m_mapBindKey.find(Name);

	if (iter == m_mapBindKey.end())
		return nullptr;

	return iter->second;
}

bool CInput::AddBindKey(const std::string& Name, unsigned char Key)
{
	// ���� �̸����� BindKey�� ��ϵǾ� ���� ���
	if (FindBindKey(Name))
		return false;

	BindKey* NewKey = new BindKey;

	// �ش� Ű�� �̹� KeyState�� ��ϵǾ� �ִ����� ã�´�. 
	KeyState* State = FindKeyState(Key);

	// ����� �ȵǾ����� ��� KeyState�� ���� ����Ѵ�.
	if (!State)
	{
		State = new KeyState;

		State->key = Key;

		m_mapKeyState.insert(std::make_pair(Key, State));
	}

	NewKey->key = State;
	NewKey->Name = Name;


	m_mapBindKey.insert(std::make_pair(Name, NewKey));

	return true;
}
