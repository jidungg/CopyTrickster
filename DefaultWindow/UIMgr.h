#pragma once
#include "UI.h"
#include <queue>
#include "Window.h"
#include "Monster.h"
#include "CharacterHPBar.h"
#include "CUIMonsterHPInfo.h"
#include "UIQuickSlot.h"
#include "UINPCConversation.h"

class CUIInventorySlot;
class CCharacterHPBar;
struct WindowCmp {
	bool operator()(CWindow* a, CWindow* b) {
		return a->Get_Order() > b->Get_Order();
	}
};

class CPlayer;
class CUIMgr
{
private:
	CUIMgr();
	~CUIMgr();

public:
	static CUIMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CUIMgr;

		return m_pInstance;
	}

	static void		Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
private:
	static CUIMgr* m_pInstance;

public:
	void Initialize();
	void Update();
	void Late_Update();
	void Render(HDC hdc);
	void Release();

	bool On_Mouse_Up(POINT _pt);
	bool On_Mouse_Down(POINT _pt);
	bool On_Mouse_Press(POINT _pt);
	void Set_Cur_Taget(CCharacter* _pTarget) { m_pCurMonsterHPInfo->Set_Monster(_pTarget); }
	void Set_CurUI(CUI* _pSlot) { m_pDragUI = _pSlot; }
	CWindow* Get_Top_Window(POINT _tP);
	CUIQuickSlot* Get_QuickSlot() { return m_pQuickSlot; }
	void Toggle_Window(WINDOW_ID);
	CUINPCConversation* Get_NPC_Conversation_UI() { return m_pNPCConversation; }
	void TurnOn_NPC_Conversation_UI(CNPC* _pNPC);
	void PrintItemIcon(HDC hdc, POINT _pt, ITEM_ID _eID);
	bool IsInUI(POINT _pt);
	void On_Quest_Clear();
private:
	vector<CWindow*> m_vecWindow;
	vector<CUI*> m_vecUI;

	priority_queue < CWindow*, vector<CWindow*>, WindowCmp> m_qRenderQue;

	CWindow* m_pCurrentWindow = nullptr;
	CUI* m_pDragUI = nullptr;
	bool m_bDrag = false;
	POINT m_tGrabPoint;

	CPlayer* m_pPlayer;

	CUIMonsterHPInfo* m_pCurMonsterHPInfo;
	CUIQuickSlot* m_pQuickSlot;
	CUINPCConversation* m_pNPCConversation;
	HDC m_hItemIconDC;
};

#define UI_INST CUIMgr::Get_Instance()