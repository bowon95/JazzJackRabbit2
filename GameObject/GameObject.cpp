
#include "GameObject.h"
#include "../Resource/Texture/Texture.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Resource/Animation/AnimationSequence.h" 
#include "../GameManager.h"
#include "../Scene/Camera.h"

CGameObject::CGameObject() :
	m_Scene(nullptr),
	m_Animation(nullptr),
	m_TimeScale(1.f),
	m_MoveSpeed(0.f),
	m_RenderLayer(ERender_Layer::Default)
{
	SetTypeID<CGameObject>();
}

CGameObject::CGameObject(const CGameObject& Obj)	:
	CRef(Obj),
	m_Scene(nullptr),
	m_Pos(Obj.m_Pos),
	m_Size(Obj.m_Size),
	m_Pivot(Obj.m_Pivot),
	m_TimeScale(Obj.m_TimeScale)
{
}

CGameObject::~CGameObject()
{
	SAFE_DELETE(m_Animation);
}

void CGameObject::SetTexture(const std::string& Name)
{
	m_Texture = m_Scene->GetSceneResource()->FindTexture(Name);
}

void CGameObject::SetTexture(CTexture* Texture)
{
	m_Texture = Texture;
}

void CGameObject::SetTexture(const std::string& Name, const TCHAR* FileName,
	const std::string& PathName)
{
	m_Scene->GetSceneResource()->LoadTexture(Name, FileName, PathName);

	m_Texture = m_Scene->GetSceneResource()->FindTexture(Name);
}

void CGameObject::SetTextureFullPath(const std::string& Name,
	const TCHAR* FullPath)
{
	m_Scene->GetSceneResource()->LoadTextureFullPath(Name, FullPath);

	m_Texture = m_Scene->GetSceneResource()->FindTexture(Name);
}

#ifdef UNICODE

void CGameObject::SetTexture(const std::string& Name,
	const std::vector<std::wstring>& vecFileName, const std::string& PathName)
{
	m_Scene->GetSceneResource()->LoadTexture(Name, vecFileName, PathName);

	m_Texture = m_Scene->GetSceneResource()->FindTexture(Name);
}

void CGameObject::SetTextureFullPath(const std::string& Name,
	const std::vector<std::wstring>& vecFullPath)
{
	m_Scene->GetSceneResource()->LoadTextureFullPath(Name, vecFullPath);

	m_Texture = m_Scene->GetSceneResource()->FindTexture(Name);
}

#else

void CGameObject::SetTexture(const std::string& Name,
	const std::vector<std::string>& vecFileName, const std::string& PathName)
{
	m_Scene->GetSceneResource()->LoadTexture(Name, vecFileName, PathName);

	m_Texture = m_Scene->GetSceneResource()->FindTexture(Name);
}

void CGameObject::SetTextureFullPath(const std::string& Name,
	const std::vector<std::string>& vecFullPath)
{
	m_Scene->GetSceneResource()->LoadTextureFullPath(Name, vecFullPath);

	m_Texture = m_Scene->GetSceneResource()->FindTexture(Name);
}

#endif

bool CGameObject::SetColorKey(unsigned char r, unsigned char g, unsigned char b, int Index)
{
	if(!m_Texture)
		return false;

	m_Texture->SetColorKey(r, g, b, Index);
	
	return true;
}

bool CGameObject::SetColorKeyAll(unsigned char r, unsigned char g, unsigned char b)
{
	if (!m_Texture)
		return false;

	m_Texture->SetColorKeyAll(r, g, b);

	return true;
}


void CGameObject::CreateAnimation()
{
	m_Animation = new CAnimation;

	m_Animation->m_Owner = this;
	m_Animation->m_Scene = m_Scene;
}

void CGameObject::AddAnimation(const std::string& SequenceName, bool Loop, float PlayTime, float PlayScale, bool Reverse)
{
	m_Animation->AddAnimation(SequenceName, Loop, PlayTime, PlayScale, Reverse);
}

void CGameObject::SetPlayTime(const std::string& Name, float PlayTime)
{
	m_Animation->SetPlayTime(Name, PlayTime);
}

void CGameObject::SetPlayScale(const std::string& Name, float PlayScale)
{
	m_Animation->SetPlayScale(Name, PlayScale);
}

void CGameObject::SetPlayLoop(const std::string& Name, bool Loop)
{
	m_Animation->SetPlayLoop(Name, Loop);
}

void CGameObject::SetPlayReverse(const std::string& Name, bool Reverse)
{
	m_Animation->SetPlayReverse(Name, Reverse);
}

void CGameObject::SetCurrentAnimation(std::string& Name)
{
	m_Animation->SetCurrentAnimation(Name);
}

void CGameObject::ChangeAnimation(const std::string& Name)
{
	m_Animation->ChangeAnimation(Name);
}

bool CGameObject::CheckCurrentAnimation(const std::string& Name)
{
	return m_Animation->CheckCurrentAnimation(Name);
}

void CGameObject::MoveDir(const Vector2& Dir)
{
	m_Pos += Dir * m_MoveSpeed * DELTA_TIME * m_TimeScale;
}

void CGameObject::Move(const Vector2& MoveValue)
{
	m_Pos += MoveValue * m_TimeScale;
}

void CGameObject::Move(float Angle)
{
	Vector2 Dir;
	Dir.x = cosf(DegreeToRadian(Angle));
	Dir.y = sinf(DegreeToRadian(Angle));

	m_Pos += Dir * m_MoveSpeed * DELTA_TIME * m_TimeScale;
}

bool CGameObject::Init()
{
	return true;
}

void CGameObject::Update(float DeltaTime)
{
	if (m_Animation)
		m_Animation->Update(DeltaTime * m_TimeScale);
}

void CGameObject::PostUpdate(float DeltaTime)
{
	m_Move = m_Pos - m_PrevPos;

	// �ִϸ��̼��� ���۵� ��� �̹��� ũ��� ����� �����ϱ� ������ ���⿡�� �����
	// �ٽ� �����ֵ��� �Ѵ�. => �ִϸ��̼Ƕ� ũ�Ⱑ ����Ǵ��� �Ź� �� �� y�� ���ؼ� Y���� ����.
	if (m_Animation)
	{
		CAnimationInfo* Current = m_Animation->m_CurrentAnimation;

		const AnimationFrameData& FrameData = Current->m_Sequence->GetFrame(Current->m_Frame);

		m_Size = FrameData.End - FrameData.Start;
	}
}

void CGameObject::Render(HDC hDC, float DeltaTime)
{
	Vector2 Pos = m_Pos - m_Scene->GetCamera()->GetPos();

	if (m_Animation)
	{
		CAnimationInfo* Current = m_Animation->m_CurrentAnimation;

		const AnimationFrameData& FrameData = Current->m_Sequence->GetFrame(Current->m_Frame);

		Vector2	Size = FrameData.End - FrameData.Start;

		Vector2	RenderLT;

		RenderLT = Pos - m_Pivot * Size;

		if (Current->m_Sequence->GetTextureType() == ETexture_Type::Sprite)
		{
			if (Current->m_Sequence->GetTexture()->GetEnableColorKey())
			{
				TransparentBlt(hDC, (int)RenderLT.x, (int)RenderLT.y,
					(int)Size.x, (int)Size.y,
					Current->m_Sequence->GetTexture()->GetDC(),
					(int)FrameData.Start.x, (int)FrameData.Start.y,
					(int)Size.x, (int)Size.y,
					Current->m_Sequence->GetTexture()->GetColorKey());
			}

			else
			{
				BitBlt(hDC, (int)RenderLT.x, (int)RenderLT.y,
					(int)Size.x, (int)Size.y,
					Current->m_Sequence->GetTexture()->GetDC(),
					(int)FrameData.Start.x, (int)FrameData.Start.y, SRCCOPY);
			}
		}

		else
		{
		}
	}

	else
	{
		if (m_Texture)
		{
			Vector2	RenderLT;

			RenderLT = Pos - m_Pivot * m_Size;

			if (m_Texture->GetEnableColorKey())
			{
				if (m_Texture->GetTextureType() == ETexture_Type::Sprite)
				{
					TransparentBlt(hDC, (int)RenderLT.x, (int)RenderLT.y,
						(int)m_Size.x, (int)m_Size.y, m_Texture->GetDC(),
						0, 0, (int)m_Size.x, (int)m_Size.y, m_Texture->GetColorKey());
				}

				else
				{
				}
			}

			else
			{
				if (m_Texture->GetTextureType() == ETexture_Type::Sprite)
				{
					BitBlt(hDC, (int)RenderLT.x, (int)RenderLT.y,
						(int)m_Size.x, (int)m_Size.y, m_Texture->GetDC(),
						0, 0, SRCCOPY);
				}

				else
				{
				}
			}
		}
	}

	m_PrevPos = m_Pos;
}
