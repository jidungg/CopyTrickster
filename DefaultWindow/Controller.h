#pragma once
#include "Player.h"
#include "KeyMgr.h"
#include "Tile.h"
#include "UIQuickSlot.h"

class CController
{
private:
	CController();
	~CController();

public:
	static CController* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CController;

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
	static CController* m_pInstance;


public:
	void Initialize();
	void Update();
	void Late_Update();
	void Render(HDC hdc);
	void Release();

	void Set_Player(CPlayer* _pPlayer) { m_pPlayer = _pPlayer; }

	bool IsInWindow(POINT _tP);
	void Mouse_Input();
	void Key_Input();
private:
	CPlayer* m_pPlayer = nullptr;


//Editor=====================
public:
	void Edit_Input();
private:
	TILE_TYPE m_eCurTile = TILE_TYPE::END;
	bool m_bCurBlock = false;
	int m_iCurOption = -1;
	CUIQuickSlot* m_pQuickSlot;
	bool m_bMouseDrillMode = false;

	POINT	pt;
	HDC m_hCursorDC;
	FRAME m_tFrame;
	int m_iCursorCX = 40;
	CURSOR_STATE m_eCursorState = CURSOR_STATE::NORMAL;
	CURSOR_STATE m_ePrevCursorState = CURSOR_STATE::END;

	CObj* pTarget = nullptr;
	CTile* pTile = nullptr;

	bool m_bRythmMode = false;
};

#define CONTROLLER_INST CController::Get_Instance()