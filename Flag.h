#pragma once

enum class ETexture_Type
{
	Sprite, // ���ӵ� ������ �̹��� �ϳ��� �ִ� ��. �Ϲ��̹����� Sprite ����
	Frame // ���� ������ �ִ� ��
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