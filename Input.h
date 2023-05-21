#pragma once

#include "GameInfo.h"
#include "SingletonMacro.h"

// Down, Push, Up �� ���� Function�� ���� ����� �� �ְ�
// enum class ����. �� enum class �� ���� �迭 �ʿ��ؼ� �Ʒ��� ����.
enum class Input_Type
{
	Down,
	Push,
	Up,
	End
};

struct KeyState
{
	unsigned char key;
	bool Down; // ������ ������ ��
	bool Push; // ������ ���� ��
	bool Up;   // ������ �ִ� Ű�� �ö�� ��

	KeyState() :
		key(0),
		Down(false),
		Push(false),
		Up(false)
	{
	}
};

struct BindFunction
{
	void* Obj; // ��ü
	// #include <functional> std::function<��ȯŸ��(����)>  ������
	// ������ ���/���� �Լ� ������� ����س��� ��� ����
	std::function<void()>	func;

	BindFunction() :
		Obj(nullptr)
	{
	}
};

struct BindKey
{
	// �̸�
	std::string Name; 
	// � Ű�� ����ϴ���
	KeyState* key;
	bool Ctrl; // Ctrl����Ű ��뿩��
	// bool Alt; 
	// bool Shift; 

	std::vector<BindFunction*>	vecFunction[(int)Input_Type::End];

	BindKey() :
		key(nullptr),
		Ctrl(false)
	{
	}

};

class CInput
{
private:
	// ����Ű�ߺ��� multimap���� �ؾ� ��. 
	std::unordered_map<unsigned char, KeyState*>	m_mapKeyState; // Ű���
	std::unordered_map<std::string, BindKey*>		m_mapBindKey; // �̸����� BindKey������ְ�.

	bool	m_Ctrl; // Ctrl ����Ű üũ�� ���� ����

public:
	bool Init();
	void Update(float DeltaTime);

private:
	void UpdateMouse(float DeltaTime);
	void UpdateKeyState(float DeltaTime);
	void UpdateBindKey(float DeltaTime);

	void SetKeyCtrl(const std::string& Name, bool Ctrl = true); // Ctrl����Ű ��� ���� ���

	KeyState* FindKeyState(unsigned char Key);
	BindKey* FindBindKey(const std::string& Name);

public:
	bool AddBindKey(const std::string& Name, unsigned char Key);

public:
	template <typename T>
	void AddBindFunction(const std::string& KeyName,
		Input_Type Type,
		T* Object, void (T::* Func)())
	{
		BindKey* Key = FindBindKey(KeyName);

		if (!Key)
			return;

		BindFunction* Function = new BindFunction;

		Function->Obj = Object;
		// bind�Լ��� std�ȿ� �����ϴ� �Լ�.����Լ��� ����� �� �Լ� �ּ�, ��ü �ּҸ� ����ؾ��Ѵ�.
		Function->func = std::bind(Func, Object);

		Key->vecFunction[(int)Type].push_back(Function);
	}

	DECLARE_SINGLE(CInput)
};

