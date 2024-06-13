#pragma once
#include "UI.h"
#include "BmpMgr.h"
#include "WindowBasicButton.h"

#define UI_SHEET_CELL_X 48
#define UI_SHEET_CELL_Y 48
#define UI_CELL_X 32
#define UI_CELEL_Y 32
#define BORDER_SIZE 6
#define TAPPER_WIDTH 20
#define TITLE_HEIGHT 24
#define HEADER_WIDTH (TAPPER_WIDTH + TITLE_HEIGHT)
#define FOOTER_WIDTH 15


class CWindow : public CUI
{
public:
	CWindow(){}
	CWindow(WINDOW_ID _eID, int _iXPos, int _iYPos, int _iXSize, int _iYSize, HDC hActive, HDC hDeactive, HDC hMinActive, HDC hMinDeactive);
	~CWindow();
	// CUI을(를) 통해 상속됨
	void Initialize() override;
	void Update() override;
	void Update_Rect() override;
	void Late_Update() override;
	void Render(HDC hdc) override;
	void Release() override;

	CUI* On_Click(POINT _pt) override;
	//드래그 드랍 시에 타겟 반환
	CUI* On_Mouse_Up(POINT _pt) override;
	CUI* On_Mouse_Down(POINT _pt) override;
	CUI* On_Mouse_Press(POINT _pt) override;
	CUI* On_Drag(POINT _pt) override;
	CUI* On_Drop(CUI* _pt) override;

	//void Set_BMPKey(TCHAR* _pKey) {m_hActiveBMP = BMP_INST->Find_Img(_pKey);}
	void Set_Size(int _iX, int _iY) { m_iXSize = _iX; m_iYSize = _iY; }
	void Set_X_Size(int _iX) { m_iXSize = _iX;  }
	void Set_Y_Size(int _iY) { m_iYSize = _iY;  }
	void Set_ID(WINDOW_ID _eT) { m_eWindowType = _eT; }
	void Set_Minimize() { m_bMinimal = true; }
	void Set_UnMinimize() { m_bMinimal = false; }
	void Set_Active(bool _bActive) { m_bActivate = _bActive; }
	void Set_Top() { m_iOrder = m_iStaticOrder++; }
	void Toggle_Active() { m_bActivate = !m_bActivate; }
	void Close() { m_bClosed = true; }
	void Open() { m_bClosed = true; }

	POINT Get_Offset(POINT _pt);
	bool IsInTitleBar(POINT _pt) { return PtInRect(&m_tTitleRect, _pt); }
protected:

	virtual void Render_Tab_Content(HDC hdc);
	virtual void Render_Content(HDC hdc);


	bool m_bActivate = false;
	bool m_bMinimal = false;

	HDC m_hActiveBMP;
	HDC m_hDeactiveBMP;
	HDC m_hMinimalActiveBMP;
	HDC m_hMinimalDectiveBMP;

	RECT m_tTitleRect;

	WINDOW_ID m_eWindowType = WINDOW_ID::INVENTORY;

	vector<CUI*> m_vecComponents;
	CWindowBasicButton* m_pMimimalizeButton = nullptr;
	CWindowBasicButton* m_pCloseButton = nullptr;



	// CUI을(를) 통해 상속됨

};

