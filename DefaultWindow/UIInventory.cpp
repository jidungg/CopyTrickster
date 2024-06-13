#include "stdafx.h"
#include "UIInventory.h"
#include <string>
#include "CItemDataBase.h"
#include "UIMgr.h"
#include "UIEquipInventory.h"

CUIInventory::CUIInventory(int _iXPos, int _iYPos, int _iXSize, int _iYSize, HDC hActive, HDC hDeactive,HDC hMinActive, HDC hMinDeactive)
	:CWindow(WINDOW_ID::INVENTORY,_iXPos, _iYPos,_iXSize,_iYSize,hActive, hDeactive, hMinActive, hMinDeactive)
{
	
}

CUIInventory::~CUIInventory()
{
}



void CUIInventory::Initialize()
{
	CWindow::Initialize();
	m_hSelectedTabLeftDC = BMP_INST->Find_Img(L"UI_Tab_Indicator_Left");
	m_hSelectedTabMidDC = BMP_INST->Find_Img(L"UI_Tab_Indicator_Mid");
	m_hSelectedTabRightDC = BMP_INST->Find_Img(L"UI_Tab_Indicator_Right");

	HDC hIconDC = BMP_INST->Find_Img(L"UI_Item_Icon");
	m_pInventory = ITEM_INST->Get_Inventory();
	int iSlotCount = m_pInventory->Get_Slot_Count();
	int iSlotColCount = 8;
	int iSlotRowCount = 4;
	m_vecSlots.resize(iSlotCount);
	for (int i = 0; i < iSlotCount; i++)
	{
		m_vecSlots[i].Initialize();
		m_vecSlots[i].Set_IconDC(hIconDC);
		m_vecSlots[i].Set_Parent(this);
		m_vecSlots[i].Set_XSize(SLOT_CX);
		m_vecSlots[i].Set_YSize(SLOT_CY);
		m_vecSlots[i].Set_Position({m_iSlotXOff + SLOT_CX *(i% iSlotColCount), m_iSlotYOff + SLOT_CY * (i/iSlotColCount) });
		m_vecComponents.push_back(&m_vecSlots[i]);
	}

	m_vecTabButtonText[(int)ITEM_TYPE::EQUIP] = L"장비";
	m_vecTabButtonText[(int)ITEM_TYPE::CONSUMABLE] = L"사용";
	m_vecTabButtonText[(int)ITEM_TYPE::ETC] = L"기타";
	Update();

	Set_Tab(ITEM_TYPE::EQUIP);

}

void CUIInventory::Update()
{

	CWindow::Update();
}


void CUIInventory::Update_Rect()
{
	CWindow::Update_Rect();
	int iLeft = m_tRect.left + m_iTabXOff;
	int iWidth = m_iTabTextWidth + m_iTabButtonPadding * 2;

	for (int i = 0; i < (int)ITEM_TYPE::END; i++)
	{
		m_vecTabButtonRect[i] = { iLeft ,
			m_tRect.top + m_iTabYOff,
			iLeft + iWidth,
			m_tRect.top + m_iTabYOff + m_iTabButtonHeight };
		iLeft += iWidth;
	}
}

void CUIInventory::Render_Tab_Content(HDC hdc)
{
	SetBkMode(hdc, TRANSPARENT);
	int tabButtonLeft = m_iTabXOff;
	int tabButtonSize = 0;
	GdiTransparentBlt(hdc,
		m_vecTabButtonRect[(int)m_eCurTab].left,
		m_vecTabButtonRect[(int)m_eCurTab].top,
		m_iTabButtonPadding,
		17,
		m_hSelectedTabLeftDC,
		0, 0, 
		m_iTabButtonPadding, 17, 
		MAGENTA);
	GdiTransparentBlt(hdc, 
		m_vecTabButtonRect[(int)m_eCurTab].left + m_iTabButtonPadding,
		m_vecTabButtonRect[(int)m_eCurTab].top,
		m_iTabTextWidth ,
		18,
		m_hSelectedTabMidDC,
		0, 0,
		32, 18,
		MAGENTA);
	GdiTransparentBlt(hdc, 
		m_vecTabButtonRect[(int)m_eCurTab].right - m_iTabButtonPadding,
		m_vecTabButtonRect[(int)m_eCurTab].top,
		m_iTabButtonPadding, 18,
		m_hSelectedTabRightDC,
		0, 0,
		m_iTabButtonPadding, 18,
		MAGENTA);

	for (int i = 0; i < (int)ITEM_TYPE::END; i++)
	{
		//Rectangle(hdc, m_vecTabButtonRect[i].left, m_vecTabButtonRect[i].top, m_vecTabButtonRect[i].right, m_vecTabButtonRect[i].bottom);
		DrawText(hdc, m_vecTabButtonText[i], -1, &m_vecTabButtonRect[i], DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	}
}

void CUIInventory::Render_Content(HDC hdc)
{
	//for (auto& i : m_vecSlots)
	//{
	//	i.Render(hdc);
	//}
}

 CUI* CUIInventory::On_Mouse_Down(POINT _pt)
{
	for (int i = 0; i < (int)ITEM_TYPE::END; i++)
	{
		if (PtInRect(&m_vecTabButtonRect[i], _pt))
		{
			Set_Tab((ITEM_TYPE)i);
			break;
		}
	}
	return CWindow::On_Mouse_Down(_pt);
}

void CUIInventory::Set_Tab(ITEM_TYPE _eType)
{
	auto pTab = m_pInventory->Get_Inventory_Tab(_eType);
	int iCount = pTab->Get_Slot_Count();
	for (int i = 0; i < iCount; i++)
	{
		m_vecSlots[i].Set_Slot((*pTab).Get_Nth_Slot(i));
	}
	m_eCurTab = _eType;
}




// SLOT =======================================================================
CUIInventorySlot::CUIInventorySlot(POINT _pt) : CUISlot(_pt.x, _pt.y, SLOT_CX,SLOT_CY)
{
	m_eSlotType = SLOT_TYPE::INVEN;
}




void CUIInventorySlot::Render(HDC hdc)
{
	//Rectangle(hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	if (m_pCurSlot->Get_Item_ID() == ITEM_ID::END)
		return;
	GdiTransparentBlt(hdc,  m_tDraw.x, m_tDraw.y, SLOT_CX, SLOT_CY,
		m_hIconDC, SLOT_CX * (int)m_pCurSlot->Get_Item_ID(), 0, SLOT_CX, SLOT_CY,
		MAGENTA);
	wstring str;
	str = std::to_wstring( m_pCurSlot->Get_Count());
	SIZE textSize = { 0,0 };
	
	TextOut(hdc, m_tRect.right - m_iCountTextXOff, m_tRect.bottom - m_iCountTextXOff,str.c_str(), str.length());
}

void CUIInventorySlot::Release()
{
}


//UIEquipSlot은 여기 안옴. 따로 오버라이딩.
CUI* CUIInventorySlot::On_Drop(CUI* _pt)
{
	ResetDrawPoint();
	m_bDrag = false;
	if (_pt == nullptr)
	{
		return nullptr;
	}

	CUIEquipSlot* pESlot =  dynamic_cast<CUIEquipSlot*>(_pt);
	if (pESlot == nullptr)
	{
		return nullptr;
	}

	ITEM_ID eID =  m_pCurSlot->Get_Item_ID();
	if (eID == ITEM_ID::END)
	{
		return nullptr;
	}

	ITEM_TYPE eType = ITEM_INST->Get_Type_byID(eID);
	if (ITEM_TYPE::EQUIP ==  eType)
	{
		if (ITEM_INST->Get_EquipType_byID(eID) == pESlot->Get_EqType())
		{
			ITEM_INST->Equip(m_pCurSlot);

		}
	}

	return nullptr;
}


void CUIInventorySlot::On_Double_Click(POINT _pt)
{
	m_dwLastClickTime = -1;
	Operate();
}

void CUIInventorySlot::Operate()
{
	ITEM_ID eId = m_pCurSlot->Get_Item_ID();
	if (eId == ITEM_ID::END)
		return;
	ITEM_TYPE eItemType = ITEMDB_INST->Get_ItemData(m_pCurSlot->Get_Item_ID())->m_eType; 
	switch (eItemType)
	{
	case ITEM_TYPE::EQUIP:
		ITEM_INST->Equip(m_pCurSlot);
		break;
	case ITEM_TYPE::CONSUMABLE:
		ITEM_INST->Consume(m_pCurSlot);
		break;
	case ITEM_TYPE::ETC:
		break;
	case ITEM_TYPE::END:
		break;
	default:
		break;
	}
}

int CUIInventorySlot::Get_IconOffset()
{
	return  (int)m_pCurSlot->Get_Item_ID();
}

void CUIInventorySlot::Late_Update()
{
}

