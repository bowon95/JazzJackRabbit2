#pragma once

#include "GameInfo.h"
#include "SingletonMacro.h"

// Down, Push, Up 에 각각 Function을 따로 등록할 수 있게
// enum class 만듦. 이 enum class 에 관한 배열 필요해서 아래에 만듦.
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
	bool Down; // 누르기 시작할 때
	bool Push; // 누르고 있을 때
	bool Up;   // 누르고 있던 키가 올라올 때

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
	void* Obj; // 객체
	// #include <functional> std::function<반환타입(인자)>  변수명
	// 변수명에 멤버/전역 함수 상관없이 등록해놓고 사용 가능
	std::function<void()>	func;

	BindFunction() :
		Obj(nullptr)
	{
	}
};

struct BindKey
{
	// 이름
	std::string Name; 
	// 어떤 키를 사용하는지
	KeyState* key;
	bool Ctrl; // Ctrl조합키 사용여부
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
	// 같은키중복은 multimap으로 해야 함. 
	std::unordered_map<unsigned char, KeyState*>	m_mapKeyState; // 키등록
	std::unordered_map<std::string, BindKey*>		m_mapBindKey; // 이름으로 BindKey만들수있게.

	bool	m_Ctrl; // Ctrl 조합키 체크를 위한 변수

public:
	bool Init();
	void Update(float DeltaTime);

private:
	void UpdateMouse(float DeltaTime);
	void UpdateKeyState(float DeltaTime);
	void UpdateBindKey(float DeltaTime);

	void SetKeyCtrl(const std::string& Name, bool Ctrl = true); // Ctrl조합키 사용 여부 등록

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
		// bind함수는 std안에 존재하는 함수.멤버함수를 등록할 때 함수 주소, 객체 주소를 등록해야한다.
		Function->func = std::bind(Func, Object);

		Key->vecFunction[(int)Type].push_back(Function);
	}

	DECLARE_SINGLE(CInput)
};

