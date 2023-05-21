#pragma once

#include "../../Ref.h"
#include "../Texture/Texture.h"

class CAnimationSequence :
    public CRef
{
    friend class CAnimationManager;
    friend class CAnimationInfo;

private:
    CAnimationSequence();
    ~CAnimationSequence();

private:
    // 사용할 텍스쳐를 반드시 들고 있어야한다.
    CSharedPtr<CTexture>  m_Texture;
    // 여러개의 프레임을 가지고 있을 수 있으니 벡터로 처리.(스프라이트이미지에서 한 모션을 한 프레임을 봤다)
    std::vector<AnimationFrameData> m_vecFrame;

public:
    CTexture* GetTexture()    const
    {
        return m_Texture;
    }

    ETexture_Type GetTextureType()  const
    {
        return m_Texture->GetTextureType();
    }

    const AnimationFrameData& GetFrame(int Index)   const
    {
        return m_vecFrame[Index];
    }

    // 이 프레임 갯수가 몇개짜린지
    int GetFrameCount() const
    {
        return(int)m_vecFrame.size();
    }

public:
    void AddFrame(const Vector2& Start, const Vector2& End);
    void AddFrame(float PosX, float PosY, float SizeX, float SizeY);

};

