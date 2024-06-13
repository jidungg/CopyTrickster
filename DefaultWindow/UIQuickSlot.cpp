#include "stdafx.h"
#include "UIQuickSlot.h"
#include "UISlot.h"
#include "CItemMgr.h"
#include "UIMgr.h"
#include "UIInventory.h"
#include <string>
#include "Player.h"
#include "ObjMgr.h"
#include "UISkillSlot.h"

CUIQuickSlot::CUIQuickSlot(POINT _pt)
{
    m_eUIType = UI_TYPE::WINDOW;
    m_iOrder = m_iStaticOrder++;
    m_hFrameDC = BMP_INST->Find_Img(L"UI_QuickSlot");
    m_iXPos = _pt.x;
    m_iYPos = _pt.y;
    m_iXSize = 66;
    m_iYSize = 144;
    m_pMimimalizeButton = nullptr;
    m_pCloseButton = nullptr;
    m_bClosed = false;

    m_SlotPoints.resize(m_iSlotCount);
    m_pSlots.resize(m_iSlotCount, nullptr);
    int iRow = 4;
    int iCol = 2;
 
    for (int r = 0; r < iRow; r++)
    {
        for (int c = 0; c < iCol; c++)
        {
            m_SlotPoints[iCol * r + c].left = m_iSlotStartX + m_iGap * c;
            m_SlotPoints[iCol * r + c].top = m_iSlotStartY + m_iGap * r;
            m_SlotPoints[iCol * r + c].right = m_SlotPoints[iCol * r + c].left + m_iIconX;
            m_SlotPoints[iCol * r + c].bottom = m_SlotPoints[iCol * r + c].top + m_iIconY;
        }
    }
    m_hCoolTimeDC = BMP_INST->Find_Img(L"UI_Skill_Cooltime");
}

void CUIQuickSlot::Initialize()
{
}

void CUIQuickSlot::Update()
{
    Update_Rect();

}

void CUIQuickSlot::Update_Rect()
{
    int iXOffset = 0, iYOffset = 0;
    if (m_pParent != nullptr)
    {
        iXOffset = m_pParent->Get_Rect().left;
        iYOffset = m_pParent->Get_Rect().top;
    }
    m_tRect.left = iXOffset + m_iXPos;
    m_tRect.top = iYOffset + m_iYPos;
    m_tRect.right = iXOffset + (m_iXPos + m_iXSize);
    m_tRect.bottom = iYOffset + (m_iYPos + m_iYSize);

    m_tTitleRect.left = m_iXPos;
    m_tTitleRect.top = m_iYPos;
    m_tTitleRect.right = m_iXPos + m_iXSize;
    m_tTitleRect.bottom = m_iYPos + m_iTitleHeight;
}

void CUIQuickSlot::Late_Update()
{
}

void CUIQuickSlot::Render(HDC hdc)
{
    GdiTransparentBlt(hdc, m_tRect.left, m_tRect.top, m_iXSize, m_iYSize,
        m_hFrameDC, 0, 0, m_iXSize, m_iYSize,
        MAGENTA);

    //for (auto& slot : m_SlotPoints)
    //{
    //    Rectangle(hdc, m_tRect.left + slot.left, m_tRect.top + slot.top,
    //        m_tRect.left + slot.right , m_tRect.top + slot.bottom);

    //}
    for (int i = 0; i < m_iSlotCount; i++)
    {
        if (m_pSlots[i] == nullptr)
            continue;
        if (m_pSlots[i]->Get_Slot_Type() == SLOT_TYPE::INVEN && m_pSlots[i]->Get_Item_ID() == ITEM_ID::END)
            continue;
        RECT slot = m_SlotPoints[i];
        HDC hIconDC = BMP_INST->Get_IconDC(m_pSlots[i]->Get_Slot_Type());
        GdiTransparentBlt(hdc, m_tRect.left + slot.left, m_tRect.top + slot.top, SLOT_CX, SLOT_CY,
            hIconDC, SLOT_CX * m_pSlots[i]->Get_IconOffset(), 0, SLOT_CX, SLOT_CY,
            MAGENTA);

        if (m_pSlots[i]->Get_Slot_Type() == SLOT_TYPE::SKILL)
        {
            CPlayer* pPlayer =  ((CPlayer*)OBJ_INST->Get_Player());
            SKILL_ID eSkillID = ((CSkillSlot*)m_pSlots[i])->Get_Skill_ID();
            float fCoolRatio =pPlayer->Get_CooltimeRatio(eSkillID);
            int idx = fCoolRatio*12;
            GdiTransparentBlt(hdc, m_tRect.left + slot.left, m_tRect.top + slot.top, 26, 26,
                m_hCoolTimeDC,
                26* idx, 0, 26, 26,
                MAGENTA);
            continue;
        }
        wstring str;
        str = std::to_wstring(m_pSlots[i]->Get_Count());
        SIZE textSize = { 0,0 };

        TextOut(hdc, m_tRect.left + slot.right - 10, m_tRect.top+ slot.bottom - 10, str.c_str(), str.length());
    }
}

void CUIQuickSlot::Release()
{
}

CUI* CUIQuickSlot::On_Mouse_Up(POINT _pt)
{
    for (auto& pUI : m_vecComponents)
    {
        RECT rc = pUI->Get_Rect();
        if (PtInRect(&rc, _pt))
        {
            return pUI->On_Click(_pt);
        }
    }
    return this;
}

void CUIQuickSlot::On_Laid(CUI* _pSlot, POINT _pt)
{
    for (int i = 0; i < m_iSlotCount; i++)
    {
        RECT rc = m_SlotPoints[i];
        rc.left += m_tRect.left;
        rc.top += m_tRect.top;
        rc.right += m_tRect.left;
        rc.bottom += m_tRect.top;

        if (PtInRect(&rc, _pt))
        {
            CUISlot* pSlot = dynamic_cast<CUISlot*>( _pSlot);
            if (pSlot && pSlot->Get_Slot_Type() != SLOT_TYPE::EQUIP)
            {
                CUIInventorySlot* pItemSlot = dynamic_cast<CUIInventorySlot*>(_pSlot);
                if (pItemSlot)
                {
                    if (ITEM_INST->Get_Type_byID(pItemSlot->Get_Slot()->Get_Item_ID()) == ITEM_TYPE::ETC)
                        continue;
                }
                m_pSlots[i] = pSlot->Get_Slot();
                return;
            }
        }
    }
}

void CUIQuickSlot::Operate(int _iIdx)
{
    if (m_pSlots[_iIdx] == nullptr)
        return;
    m_pSlots[_iIdx]->Operate();
    if (m_pSlots[_iIdx]->Get_Slot_Type() != SLOT_TYPE::SKILL)
    {
        if (m_pSlots[_iIdx]->Get_Item_ID() == ITEM_ID::END)
            m_pSlots[_iIdx] = nullptr;

    }
}

