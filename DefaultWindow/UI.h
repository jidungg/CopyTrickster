#pragma once
#include "Define.h"
class CUISlot;
class CUI
{
public:
	CUI();
	CUI(int _iXSize, int _iYSize);
	CUI(POINT _pt) { m_iXPos = _pt.x; m_iYPos = _pt.y; };
	CUI(int _iXPos, int _iYPos, int _iXSize, int _iYSize);
	virtual ~CUI();
public:
	virtual void Initialize()PURE;
	virtual void Update()PURE;
	virtual void Update_Rect();
	virtual void Late_Update()PURE;
	virtual void Render(HDC hdc)PURE;
	virtual void Release()PURE;

	virtual CUI* On_Click(POINT _pt)PURE;
	virtual CUI* On_Mouse_Down(POINT _pt)PURE;
	virtual CUI* On_Mouse_Up(POINT _pt)PURE;
	virtual CUI* On_Mouse_Press(POINT _pt)PURE;
	virtual CUI* On_Drag(POINT _pt);
	virtual CUI* On_Drop(CUI* _pt);
	virtual void On_Laid(CUI* _pSlot, POINT _pt);

	void Set_Parent(CUI* _pP) { m_pParent = _pP; }
	void Set_Position(POINT _pt) { m_iXPos = _pt.x; m_iYPos = _pt.y; }
	void Set_XSize(int _iX) { m_iXSize = _iX; }
	void Set_YSize(int _iY) { m_iYSize = _iY; }
	virtual void Move_X(int _iX) { m_iXPos += _iX;}
	virtual void Move_Y(int _iY) { m_iYPos += _iY;}

	void Set_Close();
	void Set_Open();
	bool Is_Closed() { return m_bClosed; }
	void Toggle_Closed() { if (m_bClosed) Set_Open(); else Set_Close(); }
	UI_TYPE Get_UI_Type() { return m_eUIType; }
	RECT	Get_Rect() { return m_tRect; }
	int Get_Order() { return m_iOrder; }
protected:
	RECT m_tRect;//실제 화면상 렉트
	CUI* m_pParent = nullptr;
	int m_iXPos = 0;//부모 기준 좌표
	int m_iYPos = 0;//부모 기준 좌표
	int m_iXSize = 300;//크기
	int m_iYSize = 300;//크기

	bool m_bClosed = false;

	UI_TYPE m_eUIType;
	static int m_iStaticOrder;
	int m_iOrder = -1;
};

