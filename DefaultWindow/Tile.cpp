#include "stdafx.h"
#include "Tile.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include <string>

CTile::CTile()
{
	m_tTileData = { false , TILE_TYPE::NORMAL, -1};
}

CTile::CTile(TILE_DATA _tData)
{
	Set_Tile_Data(_tData);
}

CTile::~CTile()
{
	Release();
}

void CTile::Initialize()
{
	m_tInfo.fRX = TILECX;
	m_tInfo.fRY = TILECY;
	m_tInfo.fCX = TILECX;
	m_tInfo.fCY = TILECY;

}

int CTile::Update()
{

	Update_Rect();
	return OBJ_NOEVENT;
}
void CTile::Update_Rect()
{
	m_tCollisionRect.left = long(m_tInfo.fX - m_tInfo.fCX / 2.f);
	m_tCollisionRect.top = long(m_tInfo.fY - m_tInfo.fCY / 2.f);
	m_tCollisionRect.right = long(m_tInfo.fX + m_tInfo.fCX / 2.f);
	m_tCollisionRect.bottom = long(m_tInfo.fY + m_tInfo.fCY / 2.f);
}
void CTile::Late_Update()
{
}

void CTile::Render(HDC hDC)
{
	HPEN myPen = (HPEN)GetStockObject(BLACK_PEN);
	HPEN oldPen;

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	if (m_tTileData.bBlock)
	{
		myPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		oldPen = (HPEN)SelectObject(hDC, myPen);
		MoveToEx(hDC, m_tCollisionRect.left + iScrollX, m_tCollisionRect.top + iScrollY, nullptr);
		LineTo(hDC, m_tCollisionRect.right + iScrollX, m_tCollisionRect.bottom + iScrollY);
		SelectObject(hDC, oldPen);
		DeleteObject(myPen);
	}

	switch (m_tTileData.eType)
	{
	case TILE_TYPE::NORMAL:
		myPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
		break;
	case TILE_TYPE::MONSTER:
		myPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 0));
		break;
	case TILE_TYPE::NPC:
		myPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
		break;
	case TILE_TYPE::PORTAL:
		myPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
		break;
	case TILE_TYPE::ENV:
		myPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 255));
		break;
	default:
		break;
	}
	oldPen = (HPEN)SelectObject(hDC, myPen);

	Rectangle(hDC, m_tCollisionRect.left + iScrollX, m_tCollisionRect.top + iScrollY, m_tCollisionRect.right + iScrollX, m_tCollisionRect.bottom + iScrollY);
	wstring str = to_wstring(m_tTileData.iOption);
	TextOut(hDC, m_tCollisionRect.left + iScrollX, m_tCollisionRect.top + iScrollY, str.c_str(), str.length());
	SelectObject(hDC, oldPen);
	DeleteObject(myPen);
}

void CTile::Release()
{
}
