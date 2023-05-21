#pragma once

enum class ETexture_Type
{
	Sprite, // 연속된 동작이 이미지 하나에 있는 것. 일반이미지는 Sprite 종류
	Frame // 낱장 단위로 있는 것
};

enum class ERender_Layer
{
	Back,
	Default,
	Effect,
	Max
};

enum class EButton_State
{
	Normal,
	MouseHovered,
	Click,
	Disable,
	Max
};

enum class EButton_Sound_State
{
	MouseHovered,
	Click,
	Max
};