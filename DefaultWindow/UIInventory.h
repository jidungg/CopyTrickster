#pragma once
#include "Window.h"
#include "CItemMgr.h"
#include "Button.h"
#include "UISlot.h"

class CUIInventorySlot : public CUISlot
{
public:
    CUIInventorySlot() { m_eSlotType = SLOT_TYPE::INVEN; };
    CUIInventorySlot(POINT _pt);

    void Late_Update() override;
    void Render(HDC hdc) override;
    void Release() override;
    CUI* On_Drop(CUI* _pt) override;
    void Operate() override;
    int Get_IconOffset() override;
    virtual void On_Double_Click(POINT _pt);


protected:
    int m_iCountTextXOff = 10;
    int m_iCountTextYOff = 10;
};

class CUIInventory :
    public CWindow
{
public:
    CUIInventory(int _iXPos, int _iYPos, int _iXSize, int _iYSize, HDC hActive, HDC hDeactive, HDC hMinActive, HDC hMinDeactive);
    ~CUIInventory();

    void Initialize(); 
    void Update() override;
    void Update_Rect() override;
    void Render_Tab_Content(HDC hdc) override;
    void Render_Content(HDC hdc) override;
    CUI* On_Mouse_Down(POINT _pt) override;
    void Set_Tab(ITEM_TYPE _eType);
private:
    CInventory* m_pInventory;
    ITEM_TYPE m_eCurTab;
    vector<CUIInventorySlot> m_vecSlots;

    int m_iSlotXOff = 16;
    int m_iSlotYOff = 52;
    int m_iTabXOff = 52;
    int m_iTabYOff = 23;
    
    HDC m_hSelectedTabLeftDC;
    HDC m_hSelectedTabMidDC;
    HDC m_hSelectedTabRightDC;

    int m_iTabButtonPadding = 4;
    int m_iTabTextWidth = 32;
    int m_iTabButtonHeight = 18;
    TCHAR* m_vecTabButtonText[(int)ITEM_TYPE::END];
    RECT m_vecTabButtonRect[(int)ITEM_TYPE::END];
};

