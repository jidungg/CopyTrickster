#include "stdafx.h"
#include "UISlot.h"

void CUISlot::Initialize()
{
    m_iXSize = SLOT_CX;
    m_iYSize = SLOT_CY;
}

void CUISlot::Update()
{
    Update_Rect();
    if (m_bDrag == false)
    {
        m_tDraw.x = m_tRect.left;
        m_tDraw.y = m_tRect.top;

    }
}

CUI* CUISlot::On_Mouse_Down(POINT _pt)
{
    m_bDrag = true;
    return this;
}

CUI* CUISlot::On_Mouse_Up(POINT _pt)
{
    m_bDrag = false;
    return this;
}

CUI* CUISlot::On_Mouse_Press(POINT _pt)
{
    return this;
}

CUI* CUISlot::On_Click(POINT _pt)
{
    if (m_dwLastClickTime == -1)
    {
        m_dwLastClickTime = g_dwTime;
        return this;
    }
    if (m_dwLastClickTime + DOUBLE_CLICK_TIME > g_dwTime)
        On_Double_Click(_pt);
    m_dwLastClickTime = g_dwTime;
    return this;
}

CUI* CUISlot::On_Drag(POINT _pt)
{
    Move_X(_pt.x);
    Move_Y(_pt.y);
    return this;
}


void CUISlot::On_Double_Click(POINT _pt)
{
}
