#pragma once

#include "../../Ref.h"

struct ImageInfo
{
    HDC      hMemDC; // ����ִ� �޸� DC�� ����� �ű⿡ �̹����� ä���. ����.
    HBITMAP  hBmp;   // ���忡 ���ϴ� �� �Ĵ� ��.
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
        // ������ ������� �����ش�.
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
        return m_vecImageInfo[Index]->hMemDC; // Index��°�� DC
    }

    //COLORREF ����ü�� unsigned int Ÿ���̱� ������ ���ڸ� unsigned char�� �޴´�.)
    // rgb ���� 0~255������ ���̴�.
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
    // �����̳� ���縦 �����ϱ� ���ؼ��̴�. ��ΰ� 100������ ������ ���� ������ ������
    // 100������ ������ �����ϴ� ��Ȳ�� �� ���� �ֱ� �����̴�. ���۷����� ���簡 ���Ͼ��
    // ������ ������. (���۷��� ��� ������ �ᵵ ��.)
    // const ���̴� ������ �� �Լ� �ȿ��� ���ڷ� �Ѱ��� vector�� ������ �� ���� ��
    //�ϱ� ���ؼ�
    bool LoadTextureFullPath(const std::vector<std::wstring>& vecFullPath);

#else // �����ڵ尡 �ƴ� ���� wstring�� �ƴ϶� �׳� string ��.

    bool LoadTexture(const std::vector<std::string>& vecFileName,
        const std::string& PathName = TEXTURE_PATH);
    bool LoadTextureFullPath(const std::vector<std::string>& vecFullPath);

#endif // UNICODE  

};

