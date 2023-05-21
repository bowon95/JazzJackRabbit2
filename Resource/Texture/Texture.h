#pragma once

#include "../../Ref.h"

struct ImageInfo
{
    HDC      hMemDC; // 비어있는 메모리 DC를 만들고 거기에 이미지를 채운다. 도장.
    HBITMAP  hBmp;   // 도장에 원하는 것 파는 것.
    HBITMAP  hPrevBmp;
    BITMAP   BmpInfo;
    COLORREF ColorKey;
    bool EnableColorKey;

    ImageInfo() :
        hMemDC(0),
        hBmp(0),
        hPrevBmp(0),
        BmpInfo{},
        ColorKey(RGB(0, 0, 0)),
        EnableColorKey(false)
    {
    }

    ~ImageInfo()    
    {
        // 도구를 원래대로 돌려준다.
        SelectObject(hMemDC, hPrevBmp);
        DeleteObject(hBmp);
        DeleteDC(hMemDC);
    }
};

class CTexture :
    public CRef
{
    friend class CTextureManager;

private:
    CTexture();
    ~CTexture();

private:
    ETexture_Type   m_Type;
    std::vector<ImageInfo*> m_vecImageInfo;

public:
    ETexture_Type   GetTextureType()    const
    {
        return m_Type;
    }

    HDC GetDC(int Index = 0) const
    {
        return m_vecImageInfo[Index]->hMemDC; // Index번째의 DC
    }

    //COLORREF 구조체가 unsigned int 타입이기 때문에 인자를 unsigned char로 받는다.)
    // rgb 값이 0~255사이의 값이다.
    void SetColorKey(unsigned char r, unsigned char g, unsigned char b,
        int Index = 0)
    {
        m_vecImageInfo[Index]->ColorKey = RGB(r, g, b);
        m_vecImageInfo[Index]->EnableColorKey = true;
    }

    void SetColorKeyAll(unsigned char r, unsigned char g, unsigned char b)
    {
        size_t  Size = m_vecImageInfo.size();

        for (size_t i = 0; i < Size; ++i)
        {
            m_vecImageInfo[i]->ColorKey = RGB(r, g, b);
            m_vecImageInfo[i]->EnableColorKey = true;
        }
    }

    bool GetEnableColorKey(int Index = 0)    const
    {
        return m_vecImageInfo[Index]->EnableColorKey;
    }

    COLORREF GetColorKey(int Index = 0)    const
    {
        return m_vecImageInfo[Index]->ColorKey;
    }

public:
    bool LoadTexture(const TCHAR* FileName,
        const std::string& PathName = TEXTURE_PATH);
    bool LoadTextureFullPath(const TCHAR* FullPath);

#ifdef UNICODE

    bool LoadTexture(const std::vector<std::wstring>& vecFileName,
        const std::string& PathName = TEXTURE_PATH);
    // 컨테이너 복사를 방지하기 위해서이다. 경로가 100만개가 있으면 벡터 생성한 다음에
    // 100만개를 통으로 복사하는 상황이 올 수도 있기 때문이다. 레퍼런스는 복사가 안일어나기
    // 때문에 빠르다. (레퍼런스 대신 포인터 써도 됨.)
    // const 붙이는 이유는 이 함수 안에서 인자로 넘겨준 vector를 변경할 수 없게 끔
    //하기 위해서
    bool LoadTextureFullPath(const std::vector<std::wstring>& vecFullPath);

#else // 유니코드가 아닐 때라 wstring이 아니라 그냥 string 씀.

    bool LoadTexture(const std::vector<std::string>& vecFileName,
        const std::string& PathName = TEXTURE_PATH);
    bool LoadTextureFullPath(const std::vector<std::string>& vecFullPath);

#endif // UNICODE  

};

