#include "stdafx.h"
#include "ObjItem.h"
#include "BmpMgr.h"
#include "CItemDataBase.h"
#include "ScrollMgr.h"
#include "CItemMgr.h"

CObjItem::CObjItem(ITEM_ID _eID, POINT _pt)
	:m_eItemID(_eID)
{
	Set_Pos(_pt.x, _pt.y);
	m_hIconDC = BMP_INST->Find_Img(L"UI_Item_Icon");
	m_dwStartTime = g_dwTime;
	m_eRender = RENDER_GAMEOBJECT;
	m_tInfo.fCX = SLOT_CX;
	m_tInfo.fCY = SLOT_CY;
	m_iRenderOffsetX =  -m_tInfo.fCX / 2;
	m_iRenderOffsetY =  -m_tInfo.fCY / 2;
	m_eObjID = OBJ_ITEM;
}

CObjItem::~CObjItem()
{
}

void CObjItem::Set_Common_Motion(COMMON_STATE _eState)
{
}

void CObjItem::Initialize()
{

}

int CObjItem::Update()
{

	__super::Update_Rect();

	return m_bDead ? OBJ_DEAD : OBJ_NOEVENT;
}

void CObjItem::Late_Update()
{
}

void CObjItem::Render(HDC hDC)
{
	if (m_eItemID == ITEM_ID::END)
		return;
	int iScrollX = SCROLL_INST->Get_ScrollX();
	int iScrollY = SCROLL_INST->Get_ScrollY();
	//Rectangle(hDC, m_tCollisionRect.left + iScrollX, m_tCollisionRect.top + iScrollY, m_tCollisionRect.right + iScrollX, m_tCollisionRect.bottom + iScrollY);
	GdiTransparentBlt(hDC, m_tRenderRect.left + iScrollX , m_tRenderRect.top + iScrollY , SLOT_CX, SLOT_CY,
			m_hIconDC, SLOT_CX * (int)m_eItemID, 0, SLOT_CX, SLOT_CY,
			MAGENTA);
}

void CObjItem::Release()
{
}

void CObjItem::Move_Frame()
{
}

void CObjItem::Change_Motion()
{
}

void CObjItem::On_Motion_End()
{
}

void CObjItem::Motion_Func()
{
}

void CObjItem::Interaction(CObj* _pObj)
{
	if (_pObj->Get_ID() == OBJ_PLAYER)
	{
		ITEM_INST->Add_To_Inventory(m_eItemID);
		Set_Dead();
	}
}
