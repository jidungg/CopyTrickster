#include "stdafx.h"
#include "UIMgr.h"
#include "BmpMgr.h"
#include "Window.h"
#include "Player.h"
#include "ObjMgr.h"
#include "CharacterHPBar.h"
#include "CharacterMPBar.h"
#include "UIInventory.h"
#include "UIEquipInventory.h"
#include "CUISkillInventory.h"
#include "UIQuickSlot.h"
#include "CUIQuestWindow.h"
#include "UIMinimap.h"

CUIMgr* CUIMgr::m_pInstance = nullptr;

CUIMgr::CUIMgr()
{
}

CUIMgr::~CUIMgr()
{
	Release();
}

void CUIMgr::Initialize()
{
	m_hItemIconDC = BMP_INST->Find_Img(L"UI_Item_Icon");


	m_pPlayer = static_cast<CPlayer*>(OBJ_INST->Get_Player());

	CWindow* pWindow;
	pWindow = new CUISkillInventory( 200, 0, 301, 226,
		BMP_INST->Find_Img(L"UI_SkillInven_Active"),
		BMP_INST->Find_Img(L"UI_SkillInven_Deactive"),
		BMP_INST->Find_Img(L"UI_WIndow_Minimal_Active"),
		BMP_INST->Find_Img(L"UI_WIndow_Minimal_Deactive"));
	pWindow->Initialize();
	m_vecWindow.push_back(pWindow);

	pWindow = new CUIInventory( 150, 150, 272, 197,
		BMP_INST->Find_Img(L"UI_Inventory_Active"),
		BMP_INST->Find_Img(L"UI_Inventory_Deactive"),		
		BMP_INST->Find_Img(L"UI_WIndow_Minimal_Active"),
		BMP_INST->Find_Img(L"UI_WIndow_Minimal_Deactive"));
	pWindow->Initialize();
	m_vecWindow.push_back(pWindow);

	pWindow = new CUIQuestWindow( 0, 0, 321, 323,
		BMP_INST->Find_Img(L"UI_Quest_Active"),
		BMP_INST->Find_Img(L"UI_Quest_Deactive"),
		BMP_INST->Find_Img(L"UI_WIndow_Minimal_Active"),
		BMP_INST->Find_Img(L"UI_WIndow_Minimal_Deactive"),
		BMP_INST->Find_Img(L"UI_Quest_Side"));
	pWindow->Initialize();
	m_vecWindow.push_back(pWindow);

	pWindow = new CUIEquipInventory(0,0, 178, 283,
		BMP_INST->Find_Img(L"UI_EquipInven_Active"),
		BMP_INST->Find_Img(L"UI_EquipInven_Deactive"),
		BMP_INST->Find_Img(L"UI_WIndow_Minimal_Active"),
		BMP_INST->Find_Img(L"UI_WIndow_Minimal_Deactive"));
	pWindow->Initialize();
	m_vecWindow.push_back(pWindow);
 
	{
		CCharacterHPBar* pUI;
		pUI = new CCharacterHPBar(10, 30, 250, 28, 2,2);
		pUI->Set_Character(m_pPlayer);
		CUIGuageFrame* pFrame = new CUIGuageFrame(6, 28, 6, 28,
			BMP_INST->Find_Img(L"UI_Player_Gauge_Left"),
			BMP_INST->Find_Img(L"UI_Player_Gauge_Mid"),
			BMP_INST->Find_Img(L"UI_Player_Gauge_Right"));
		pUI->Set_Frame(pFrame);
		CUIGuageFill* pFIll = new CUIGuageFill(6, 20,
			BMP_INST->Find_Img(L"UI_Player_Gauge_Hp"));
		pUI->Set_Fill(pFIll);
		m_vecUI.push_back(pUI);
	}

	{
		CCharacterMPBar* pUI;
		pUI = new CCharacterMPBar(10, 60, 200, 28, 2,2);
		pUI->Set_Character(m_pPlayer);
		CUIGuageFrame* pFrame = new CUIGuageFrame(6, 28, 6, 28,
			BMP_INST->Find_Img(L"UI_Player_Gauge_Left"),
			BMP_INST->Find_Img(L"UI_Player_Gauge_Mid"),
			BMP_INST->Find_Img(L"UI_Player_Gauge_Right"));
		pUI->Set_Frame(pFrame);
		CUIGuageFill* pFIll = new CUIGuageFill(6, 20,
			BMP_INST->Find_Img(L"UI_Player_Gauge_Mp"));
		pUI->Set_Fill(pFIll);
		m_vecUI.push_back(pUI);
	}
	{
		m_pCurMonsterHPInfo = new CUIMonsterHPInfo(WINCX/2 - 112, 30,224, 52,10,35);
		m_vecUI.push_back(m_pCurMonsterHPInfo);
	}

	{
		m_pQuickSlot = new CUIQuickSlot({ WINCX - 66,154 });
		m_pQuickSlot->Initialize();
		
		m_vecWindow.push_back(m_pQuickSlot);
	}
	{
		m_pNPCConversation = new CUINPCConversation();
		m_pNPCConversation->Initialize();
		m_vecWindow.push_back(m_pNPCConversation);
	}
	{
		m_vecUI.push_back(new CUIMinimap(142,153));
	}
}

void CUIMgr::Update()
{
	for (auto& ui : m_vecWindow)
	{
		ui->Update();
	}
	for (auto& i : m_vecUI)
	{
		i->Update();
	}
}

void CUIMgr::Late_Update()
{
	for (auto& ui : m_vecWindow)
	{
		ui->Late_Update();
		m_qRenderQue.push(ui);
	}
	for (auto& i : m_vecUI)
	{
		i->Late_Update();
	}

}

void CUIMgr::Render(HDC hdc)
{
	for (auto& i : m_vecUI)
	{
		i->Render(hdc);
	}
	while (m_qRenderQue.empty() == false)
	{
		m_qRenderQue.top()->Render(hdc);
		m_qRenderQue.pop();
	}
}

void CUIMgr::Release()
{
	for (auto& ui : m_vecWindow)
	{
		Safe_Delete(ui);
	}
	m_vecWindow.clear();
	for (auto& i : m_vecUI)
	{
		
		Safe_Delete( i);
	}
	m_vecUI.clear();
}


bool CUIMgr::On_Mouse_Down(POINT _pt)
{
	m_pCurrentWindow = Get_Top_Window(_pt);
	if (m_pCurrentWindow == nullptr)
		return false;
	for (auto& i : m_vecWindow)
		i->Set_Active(false);
	m_pCurrentWindow->Set_Active(true);
	m_pCurrentWindow->Set_Top();

	if (m_pCurrentWindow->IsInTitleBar(_pt))
	{
		m_pDragUI = m_pCurrentWindow;
		m_bDrag = true;
		m_tGrabPoint = _pt;
	}
	else if (m_pDragUI = m_pCurrentWindow->On_Mouse_Down(_pt))
	{
		m_bDrag = true;
		m_tGrabPoint = _pt;
	}
	else
	{
		m_bDrag = false;

	}
	return true;
}
bool CUIMgr::On_Mouse_Press(POINT _pt)
{
	if (m_pCurrentWindow == nullptr)
		return false;
	if (m_bDrag && m_pDragUI != nullptr)
	{
		POINT tMove;
		tMove.x = _pt.x - m_tGrabPoint.x;
		tMove.y = _pt.y - m_tGrabPoint.y;
		m_pDragUI->On_Drag(tMove);
		m_tGrabPoint = _pt;
	}
	return true;
}
bool CUIMgr::On_Mouse_Up(POINT _tp)
{
	CWindow* pTopWnd = Get_Top_Window(_tp);
	CUI* pUpUI = nullptr;
	bool bIsOnUI = false;
	if (pTopWnd)
	{
		pUpUI = pTopWnd->On_Mouse_Up(_tp);
		bIsOnUI = true;
	}
	if (m_bDrag && m_pDragUI)
	{
		m_pDragUI->On_Drop(pUpUI);
		if (pUpUI)
		{
			pUpUI->On_Laid(m_pDragUI, _tp);
		}
		m_bDrag = false;
		m_pDragUI = nullptr;
	}

	
	return bIsOnUI;
}


CWindow* CUIMgr::Get_Top_Window(POINT _tP)
{
	int topOrder = -1;
	CWindow* pTopWnd = nullptr;
	for (auto& pUI : m_vecWindow)
	{
		if (pUI->Is_Closed())
			continue;
		if (PtInRect(&pUI->Get_Rect(), _tP))
		{
			int tmp = pUI->Get_Order();
			if (topOrder < tmp)
			{
				topOrder = tmp;
				pTopWnd = pUI;
			}
		}
	}
	return pTopWnd;
}

void CUIMgr::Toggle_Window(WINDOW_ID _eId)
{
	m_vecWindow[(int)_eId]->Toggle_Closed();
}

void CUIMgr::TurnOn_NPC_Conversation_UI(CNPC* _pNPC)
{
	m_pNPCConversation->Set_Open();
	m_pNPCConversation->Set_NPC(_pNPC);
}

void CUIMgr::PrintItemIcon(HDC hdc, POINT _pt, ITEM_ID _eID)
{	
	GdiTransparentBlt(hdc,_pt.x, _pt.y,SLOT_CX, SLOT_CY,
		m_hItemIconDC, SLOT_CX * (int)_eID, 0,SLOT_CX, SLOT_CY , MAGENTA);

}

bool CUIMgr::IsInUI(POINT _pt)
{
	for (auto& pUI : m_vecWindow)
	{
		if (pUI->Is_Closed())
			continue;
		if (PtInRect(&pUI->Get_Rect(), _pt))
		{
			return true;

		}
	}
	return false;
}

void CUIMgr::On_Quest_Clear()
{
}
