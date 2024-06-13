#pragma once
#include "UIInventory.h"

class CUIEquipSlot : public CUISlot
{
public:
    CUIEquipSlot() { m_eSlotType = SLOT_TYPE::EQUIP; }
    CUIEquipSlot(POINT _pt);
    // CUISlot을(를) 통해 상속됨
    void Late_Update() override;

    void Release() override;

    void Render(HDC hdc) override;
    CUI* On_Drop(CUI* _pt) override;
    void On_Double_Click(POINT _pt) override;
    void Operate() override;
    void Set_EqType(EQUIP_TYPE _eType) { m_eEqType = _eType; }
    int Get_IconOffset() override;
    EQUIP_TYPE Get_EqType() { return m_eEqType; }
protected:
    EQUIP_TYPE m_eEqType;

    // CUISlot을(를) 통해 상속됨
};

class CUIEquipInventory :
    public CWindow
{
public:
    CUIEquipInventory(int _iXPos, int _iYPos, int _iXSize, int _iYSize, HDC hActive, HDC hDeactive, HDC hMinActive, HDC hMinDeactive);

    void Initialize();
    void Render_Content(HDC hdc) override;
private:

    POINT m_Offsets[(int)EQUIP_TYPE::END];
    CUIEquipSlot m_Slots[(int)EQUIP_TYPE::END];
    CEquipInventory* m_pEqInventory;
};

