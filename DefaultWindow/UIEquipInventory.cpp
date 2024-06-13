#include "stdafx.h"
#include "UIEquipInventory.h"
#include "CItemDataBase.h"

CUIEquipInventory::CUIEquipInventory(int _iXPos, int _iYPos, int _iXSize, int _iYSize, HDC hActive, HDC hDeactive, HDC hMinActive, HDC hMinDeactive)
	:CWindow(WINDOW_ID::EQUIP, _iXPos, _iYPos, _iXSize, _iYSize, hActive, hDeactive, hMinActive, hMinDeactive)
{
}

void CUIEquipInventory::Initialize()
{
	CWindow::Initialize();
	m_pEqInventory = ITEM_INST->Get_Equip_Inventory();

	m_Offsets[(int)EQUIP_TYPE::WEAPON] = { 20,62 };
	m_Offsets[(int)EQUIP_TYPE::HAT] = { 56,29 };
	m_Offsets[(int)EQUIP_TYPE::EAR] = { 94,29 };
	m_Offsets[(int)EQUIP_TYPE::SHIELD] = { 131,63};
	m_Offsets[(int)EQUIP_TYPE::DRILL] = { 130,129};
	HDC hIconDC = BMP_INST->Find_Img(L"UI_Item_Icon");
	for (int i = 0; i < (int)EQUIP_TYPE::END; i++)
	{
		m_Slots[i].Set_EqType((EQUIP_TYPE)i);
		m_Slots[i].Set_IconDC(hIconDC);
		m_Slots[i].Set_Parent(this);
		m_Slots[i].Set_Position(m_Offsets[i]);
		m_Slots[i].Set_XSize(SLOT_CX);
		m_Slots[i].Set_YSize(SLOT_CY);
		m_Slots[i].Set_Slot(m_pEqInventory->Get_Slot((EQUIP_TYPE)i));
		m_vecComponents.push_back(&m_Slots[i]);
	}
	
}

void CUIEquipInventory::Render_Content(HDC hdc)
{
	for (auto& i : m_Slots)
	{
		i.Render(hdc);
	}
}



CUIEquipSlot::CUIEquipSlot(POINT _pt) : CUISlot(_pt.x, _pt.y, SLOT_CX, SLOT_CY)
{
	SLOT_TYPE::EQUIP;
}

void CUIEquipSlot::Render(HDC hdc)
{
	if (m_pCurSlot->Get_Item_ID() == ITEM_ID::END)
		return;
	GdiTransparentBlt(hdc, m_tDraw.x, m_tDraw.y, SLOT_CX, SLOT_CY,
		m_hIconDC, SLOT_CX * (int)m_pCurSlot->Get_Item_ID(), 0, SLOT_CX, SLOT_CY,
		MAGENTA);
}

CUI* CUIEquipSlot::On_Drop(CUI* _pt)
{
	ResetDrawPoint();
	m_bDrag = false;
	if (_pt == nullptr)
	{
		return nullptr;
	}

	CUIInventorySlot* pDroppedUISlot = dynamic_cast<CUIInventorySlot*>(_pt);
	//인벤슬롯에 떨궜는지?
	if (pDroppedUISlot == nullptr)
	{
		return nullptr;
	}

	ITEM_ID eID = pDroppedUISlot->Get_Slot()->Get_Item_ID();
	//인벤 슬롯에 이미 아이템이 있는지?
	if (eID == ITEM_ID::END)
	{
		//슬롯에 아이템 없으면 그냥 해제
		ITEM_INST->Unequip(Get_EqType());
		return nullptr;
	}
	//슬롯에 아이템 있으면 스왑.
	else
	{
		ITEM_INST->Equip(pDroppedUISlot->Get_Slot());

		return nullptr;
	}

	return nullptr;
}

void CUIEquipSlot::On_Double_Click(POINT _pt)
{
	m_dwLastClickTime = -1;

	Operate();
	
}

int CUIEquipSlot::Get_IconOffset()
{
	return (int)m_pCurSlot->Get_Item_ID();
}

void CUIEquipSlot::Operate()
{
	ITEM_ID eId = m_pCurSlot->Get_Item_ID();
	if (eId == ITEM_ID::END)
		return;
	ITEM_INST->Unequip(m_eEqType);
}

void CUIEquipSlot::Late_Update()
{
}

void CUIEquipSlot::Release()
{
}
