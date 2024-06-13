#include "stdafx.h"
#include "Controller.h"
#include "UIMgr.h"
#include "ScrollMgr.h"
#include "TileMgr.h"
#include "Monster.h"
#include "ObjMgr.h"
#include "MouseMgr.h"
#include "Window.h"
#include "SceneMgr.h"
#include "CItemMgr.h"
#include "SoundMgr.h"

CController* CController::m_pInstance = nullptr;

CController::CController()
{
}

CController::~CController()
{
	Release();
}

void CController::Initialize()
{
	m_pQuickSlot = UI_INST->Get_QuickSlot();
	m_hCursorDC = BMP_INST->Find_Img(L"UI_Cursor");

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = 0;
}

void CController::Update()
{
	if (KEY_INST->Key_Up(VK_F8))
		g_bEditMode = !g_bEditMode;

	if (g_bEditMode)
	{
		Edit_Input();
	}
	else
	{
		Mouse_Input();
		Key_Input();

	}
}

void CController::Late_Update()
{
	if (UI_INST->IsInUI(pt))
	{
		m_eCursorState = CURSOR_STATE::UI;

	}
	else if (m_bMouseDrillMode)
	{
		m_eCursorState = CURSOR_STATE::DRILL;
	}
	else if (pTarget)
	{
		switch (pTarget->Get_ID())
		{
		case OBJ_ID::OBJ_MONSTER:
			m_eCursorState = CURSOR_STATE::ATTACK;
			break;
		case OBJ_ID::OBJ_NPC:
			m_eCursorState = CURSOR_STATE::TALK;
			break;
		case OBJ_ID::OBJ_PORTAL:
			m_eCursorState = CURSOR_STATE::DOOR;
			break;
		case OBJ_ID::OBJ_ITEM:
			m_eCursorState = CURSOR_STATE::GRAB;
			break;
		}
	}
	else if (pTile && pTile->Get_Tile_Data().bBlock)
	{
		m_eCursorState = CURSOR_STATE::BLOCKED;

	}
	else
	{
		m_eCursorState = CURSOR_STATE::NORMAL;
	}

	if ((m_ePrevCursorState != m_eCursorState))
	{
		switch (m_eCursorState)
		{
		case CURSOR_STATE::UI:
			m_tFrame.iFrameEnd = 4;
			break;
		case CURSOR_STATE::ATTACK:
			m_tFrame.iFrameEnd = 3;
			break;
		case CURSOR_STATE::SKILL:
			m_tFrame.iFrameEnd = 6;
			break;
		case CURSOR_STATE::DOOR:
			m_tFrame.iFrameEnd = 2;
			break;
		case CURSOR_STATE::NORMAL:
			m_tFrame.iFrameEnd = 0;
			break;
		case CURSOR_STATE::GRAB:
			m_tFrame.iFrameEnd = 5;
			break;
		case CURSOR_STATE::TALK:
			m_tFrame.iFrameEnd = 2;
			break;
		case CURSOR_STATE::QUEST:
			m_tFrame.iFrameEnd = 5;
			break;
		case CURSOR_STATE::DRILL:
			m_tFrame.iFrameEnd = 2;
			break;
		case CURSOR_STATE::BLOCKED:
			m_tFrame.iFrameEnd = 0;
			break;
		case CURSOR_STATE::END:
			break;
		default:
			break;
		}

		m_tFrame.iFrameStart = 0;
		m_tFrame.dwTime = g_dwTime;
		m_ePrevCursorState = m_eCursorState;
	}

	if (m_tFrame.dwTime + m_tFrame.dwSpeed < g_dwTime)
	{
		++m_tFrame.iFrameStart;
		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
		{
			m_tFrame.iFrameStart = 0;
	
		}

		m_tFrame.dwTime = g_dwTime;
	}
}

void CController::Render(HDC hdc)
{
	GdiTransparentBlt(hdc, pt.x, pt.y, m_iCursorCX, m_iCursorCX,
		m_hCursorDC,
		m_tFrame.iFrameStart * m_iCursorCX,
		(int)m_eCursorState * m_iCursorCX,
		m_iCursorCX, m_iCursorCX,
		MAGENTA);
	if (g_bEditMode)
		Rectangle(hdc, pt.x, pt.y, pt.x+10, pt.y+10);
}

void CController::Release()
{
}

bool CController::IsInWindow(POINT _tP)
{
	if (_tP.x < 0)
		return false;
	if (_tP.x >  WINCX)
		return false;
	if (_tP.y < 0)
		return false;
	if (_tP.y > WINCY)
		return false;
	return true;
}

void CController::Edit_Input()
{
	if (KEY_INST->Key_Down('B'))
	{
		m_bCurBlock = !m_bCurBlock;
	}
	if (KEY_INST->Key_Down('S'))
	{
		TILE_INST->Save_Tile(SCENE_INST->Get_Scene_ID());
	}
	if (KEY_INST->Key_Down('L'))
	{
		TILE_INST->Load_Tile(SCENE_INST->Get_Scene_ID());
	}
	if (KEY_INST->Key_Down(VK_F1))
	{
		m_eCurTile = TILE_TYPE::NORMAL;
	}
	else if (KEY_INST->Key_Down(VK_F2))
	{
		m_eCurTile = TILE_TYPE::MONSTER;
	}
	else if (KEY_INST->Key_Down(VK_F3))
	{
		m_eCurTile = TILE_TYPE::NPC;
	}
	else if (KEY_INST->Key_Down(VK_F4))
	{
		m_eCurTile = TILE_TYPE::PORTAL;
	}
	else if (KEY_INST->Key_Down(VK_F5))
	{
		m_eCurTile = TILE_TYPE::ENV;
	}

	for (int i = 0; i < 9; i++)
	{
		if (KEY_INST->Key_Down(i + 0x30))
		{
			m_iCurOption = i -1;
		}
	}
	if (KEY_INST->Key_Pressing(VK_LEFT))
	{
		SCROLL_INST->Move_ScrollX(10);
	}
	if (KEY_INST->Key_Pressing(VK_RIGHT))
	{
		SCROLL_INST->Move_ScrollX(-10);
	}
	if (KEY_INST->Key_Pressing(VK_DOWN))
	{
		SCROLL_INST->Move_ScrollY(-10);
	}
	if (KEY_INST->Key_Pressing(VK_UP))
	{
		SCROLL_INST->Move_ScrollY(10);
	}
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	if (KEY_INST->Key_Pressing(VK_LBUTTON))
	{



		pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		CTileMgr::Get_Instance()->Picking_Tile(pt, {m_bCurBlock, m_eCurTile, m_iCurOption});
	}
}

void CController::Mouse_Input()
{
	pt = MOUSE_INST->Get_Mouse_Point();
	//ScreenToClient(g_hWnd,&pt);
	if (IsInWindow(pt) == false)
		return;


	if (KEY_INST->Key_Down(VK_LBUTTON))
	{
		if (UI_INST->On_Mouse_Down(pt))
		{
			m_eCursorState = CURSOR_STATE::UI;
			SOUND_INST->StopSound(SOUND_CLICK);
			SOUND_INST->PlaySound(L"ui_click.wav", CHANNELID::SOUND_CLICK, 0.5);
			return;
		}
	}

	if (KEY_INST->Key_Up(VK_LBUTTON))
	{
		if(UI_INST->On_Mouse_Up(pt))
		{
			m_eCursorState = CURSOR_STATE::UI;
			return;
		}
	}

	if (KEY_INST->Key_Pressing(VK_LBUTTON))
	{
		if (UI_INST->On_Mouse_Press(pt))
		{
			m_eCursorState = CURSOR_STATE::UI;
			return;
		}
	}

	POINT tWorldPT = pt;
	tWorldPT.x -= (long)SCROLL_INST->Get_ScrollX();
	tWorldPT.y -= (long)SCROLL_INST->Get_ScrollY();

	pTarget = (OBJ_INST->IsInObj(tWorldPT));
	pTile = TILE_INST->Get_Tile(tWorldPT);

	

	if (KEY_INST->Key_Down(VK_LBUTTON))
	{


		if (m_pPlayer == nullptr || m_pPlayer->Get_Dead())
		{
			m_pPlayer = nullptr;
			return;
		}
	
		if (m_bMouseDrillMode && ITEM_INST->Is_Equiped(EQUIP_TYPE::DRILL))
		{
			m_pPlayer->Set_Dest(tWorldPT);
			m_pPlayer->Set_Target(nullptr);
			m_pPlayer->Set_Drill_Mode(true);
			m_bMouseDrillMode = false;
			return;
		}
		else
		{
			m_pPlayer->Set_Drill_Mode(false);
			m_pPlayer->End_Drill();
			m_bMouseDrillMode = false;
		}


		if (pTarget)
		{
			if (pTarget->Get_ID() != OBJ_PLAYER)
			{
				m_pPlayer->Set_Target(pTarget);
				if(dynamic_cast<CCharacter*>(pTarget))
					UI_INST->Set_Cur_Taget((CCharacter*)pTarget);
			}
			return;
		}



		if (pTile)
		{
			if (pTile->Get_Tile_Data().bBlock == false)
			{
				m_pPlayer->Set_Dest(tWorldPT);
				m_pPlayer->Set_Target(nullptr);
			}
			return;
		}
	}



}

void CController::Key_Input()
{
	if (KEY_INST->Key_Down('R'))
	{
		m_pPlayer->Toggle_Run();
	}
	if (KEY_INST->Key_Down('I'))
	{
		UI_INST->Toggle_Window(WINDOW_ID::INVENTORY);
	}
	if (KEY_INST->Key_Down('Q'))
	{
		UI_INST->Toggle_Window(WINDOW_ID::QUEST);
	}
	if (KEY_INST->Key_Down('E'))
	{
		UI_INST->Toggle_Window(WINDOW_ID::EQUIP);
	}
	if (KEY_INST->Key_Down('K'))
	{
		UI_INST->Toggle_Window(WINDOW_ID::SKILL);
	}
	if (KEY_INST->Key_Down('D'))
	{
		m_bMouseDrillMode = !m_bMouseDrillMode;
	}
	if (m_pPlayer->Get_Stat()._iHP <= 0)
	{
		if (KEY_INST->Key_Down(VK_RETURN))
		{
			SCENE_INST->Revive();
		}
	}
	if (KEY_INST->Key_Down(VK_F1))
	{
		m_pQuickSlot->Operate(0);
	}
	else if (KEY_INST->Key_Down(VK_F2))
	{
		m_pQuickSlot->Operate(1);
	}
	else if (KEY_INST->Key_Down(VK_F3))
	{
		m_pQuickSlot->Operate(2);
	}
	else if (KEY_INST->Key_Down(VK_F4))
	{
		m_pQuickSlot->Operate(3);
	}
	else if (KEY_INST->Key_Down(VK_F5))
	{
		m_pQuickSlot->Operate(4);
	}
	else if (KEY_INST->Key_Down(VK_F6))
	{
		m_pQuickSlot->Operate(5);
	}
	else if (KEY_INST->Key_Down(VK_F7))
	{
		m_pQuickSlot->Operate(6);
	}
	else if (KEY_INST->Key_Down(VK_F8))
	{
		m_pQuickSlot->Operate(7);
	}
}
