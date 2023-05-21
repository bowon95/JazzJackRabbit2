#pragma once

#include "../Ref.h"

class CWidget :
    public CRef
{
    friend class CWidgetComponent;
    friend class CWidgetWindow;

protected:
    CWidget();
    CWidget(const CWidget& widget);
    virtual ~CWidget();

protected:
    class CScene* m_Scene;
    class CWidgetWindow* m_Owner;
    int     m_ZOrder; // 위젯끼리 출력 순서
    Vector2 m_Pos;
    Vector2 m_Size;
    bool    m_MouseHovered; // 마우스가 위젯 위에 있는지 아닌지

public:
    const Vector2& GetPos()	const
    {
        return m_Pos;
    }

    const Vector2& GetSize()	const
    {
        return m_Size;
    }

    int GetZOrder() const
    {
        return m_ZOrder;
    }

public:
    void SetPos(float x, float y)
    {
        m_Pos.x = x;
        m_Pos.y = y;
    }

    void SetPos(const Vector2& Pos)
    {
        m_Pos = Pos;
    }

    void SetSize(float x, float y)
    {
        m_Size.x = x;
        m_Size.y = y;
    }

    void SetSize(const Vector2& Size)
    {
        m_Size = Size;
    }

    void SetZOrder(int ZOrder)
    {
        m_ZOrder = ZOrder;
    }

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render(HDC hDC, float DeltaTime);
    virtual void Render(HDC hDC, const Vector2& Pos, float DeltaTime);

// !!!!마우스충돌은 필요없을듯!!!
public:
    bool CollisionMouse(const Vector2& Pos);

public:
    virtual void CollisionMouseHoveredCallback(const Vector2& Pos);
    virtual void CollisionMouseReleaseCallback();
};

