#pragma once
#include "Window.h"
#include "UISlot.h"

class CUIQuickSlot :
    public CWindow
{
public:
    CUIQuickSlot(POINT _pt);
    ~CUIQuickSlot() { Release(); }
    // CUI을(를) 통해 상속됨
    void Initialize() override;
    void Update() override;
    void Update_Rect() override;
    void Late_Update() override;
    void Render(HDC hdc) override;
    void Release() override;
    CUI* On_Mouse_Up(POINT _pt) override;
    void On_Laid(CUI* _pSlot, POINT _pt) override;
    void Operate(int _iIdx);
private:
    HDC m_hFrameDC;
    const int m_iSlotCount = 8;
    int m_iTitleHeight = 15;
    int m_iIconX = 27;
    int m_iIconY = 27;
    int m_iSlotStartX = 4;
    int m_iSlotStartY = 18;
    int m_iGap = 32;
    vector<RECT> m_SlotPoints;
    vector<CItemSlot*> m_pSlots;
    HDC m_hCoolTimeDC;
};

