#include "Input.h"

DEFINITION_SINGLE(CInput)

CInput::CInput()
{
}

CInput::~CInput()
{
	//Input 이 끝났으면 등록한 키 다 제거
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
	// 캐릭터 인풋
	AddBindKey("MoveUp", VK_UP);
	AddBindKey("MoveDown", VK_DOWN);
	AddBindKey("MoveRight", VK_RIGHT);
	AddBindKey("MoveLeft", VK_LEFT);
	AddBindKey("Fire", VK_SPACE);  
	AddBindKey("Jump", VK_CONTROL); 
	AddBindKey("Run", VK_SHIFT); 

	AddBindKey("Select", VK_RETURN);
	//(?) AddBindKey("", VK_ESCAPE); 동영상 스킵이나 게임 중 메뉴창 또는 
			// 돌아가기
	// 스페이스바가 확인 버튼이면..?
	
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

		// 키를 눌렀을 경우
		if (KeyPush)
		{
			// Down과 Push 모두 false라면 이 키를 지금 누른 것이다. 
			// 그러므로 둘 다 true 로 변경한다.
			if (!iter->second->Down && !iter->second->Push) 
			{
				iter->second->Down = true;
				iter->second->Push = true;
			}
			// Down과 Push 둘 중 하나라도 true라면 Down은 false가 되어야한다.
			// Push는 위에서 true로 변경되었다.
			else
				iter->second->Down = false;
		}
		// 키가 안 눌러졌을 경우 Push가 true라면
		// 이전 프레임에 키를 누르고 있다가 지금 떨어졌다는 것이다.
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

	// iter가 end를 반환하면 못찾았다는 얘기.
	if (iter == m_mapKeyState.end())
		return nullptr;
	// iter->first :  key,
	// iter->second : value 들어있다.
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
	// 같은 이름으로 BindKey가 등록되어 있을 경우
	if (FindBindKey(Name))
		return false;

	BindKey* NewKey = new BindKey;

	// 해당 키로 이미 KeyState가 등록되어 있는지를 찾는다. 
	KeyState* State = FindKeyState(Key);

	// 등록이 안되어있을 경우 KeyState를 만들어서 등록한다.
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
