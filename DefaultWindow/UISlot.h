#pragma once
#include "UI.h"

class CItemSlot;
class CUISlot :
    public CUI
{
public:
    CUISlot() = default;
    CUISlot(int _iXPos, int _iYPos, int _iXSize, int _iYSize) : CUI(_iXPos, _iYPos,_iXSize, _iYSize)
    {
        m_tDraw.x = _iXPos;
        m_tDraw.y = _iYPos;
        m_eUIType = UI_TYPE::SLOT;
    }

    // CUI을(를) 통해 상속됨Se
    void Initialize() override;
    void Update() override;

    CUI* On_Mouse_Down(POINT _pt) override;
    CUI* On_Mouse_Up(POINT _pt) override;
    CUI* On_Mouse_Press(POINT _pt) override;
    CUI* On_Click(POINT _pt) override;
    CUI* On_Drag(POINT _pt) override;
  
    virtual void On_Double_Click(POINT _pt);
    virtual void Operate()PURE;
    void Set_IconDC(HDC _hdc) { m_hIconDC = _hdc; }
    void Set_Slot(CItemSlot* _pSlot) { m_pCurSlot = _pSlot; }
    CItemSlot* Get_Slot() { return m_pCurSlot; }
    SLOT_TYPE Get_Slot_Type() { return m_eSlotType; }
    HDC Get_IconDC() { return m_hIconDC; }
    virtual int Get_IconOffset() PURE;
    virtual void Move_X(int _iX) { m_tDraw.x += _iX; }
    virtual void Move_Y(int _iY) { m_tDraw.y += _iY; }
    void ResetDrawPoint() {
        m_tDraw.x = m_tRect.left;
        m_tDraw.y = m_tRect.top;
    };
protected:
    bool m_bDrag = false;
    POINT m_tDraw;
    DWORD m_dwLastClickTime = -1;
    HDC m_hIconDC;
    CItemSlot* m_pCurSlot;
    SLOT_TYPE m_eSlotType;
};

