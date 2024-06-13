#include "stdafx.h"
#include "Portal.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "SceneMgr.h"
#include "Character.h"
#include "ObjMgr.h"
#include "SoundMgr.h"
CPortal::CPortal()
{
    m_eRender = RENDER_GAMEOBJECT;
	m_eObjID = OBJ_PORTAL;
}

CPortal::~CPortal()
{
}

void CPortal::Initialize()
{
	m_tInfo.fCX = TILECX;
	m_tInfo.fCY = TILECY;
	m_tInfo.fRX = 109;
	m_tInfo.fRY = 110;

	m_hMemDC = BMP_INST->Find_Img(L"Portal");
	m_eRender = RENDER_PORTAL;
	m_eObjID = OBJ_PORTAL;
}

int CPortal::Update()
{
	__super::Update_Rect();
    return OBJ_NOEVENT;
}

void CPortal::Late_Update()
{
}

void CPortal::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	GdiTransparentBlt(hDC,
		m_tRenderRect.left + iScrollX,
		m_tRenderRect.top + iScrollY,
		(int)m_tInfo.fRX,
		(int)m_tInfo.fRY,
		m_hMemDC,
		0,
		0,
		(int)m_tInfo.fRX,
		(int)m_tInfo.fRY,
		MAGENTA);
	//Rectangle(hDC, m_tCollisionRect.left + iScrollX, m_tCollisionRect.top + iScrollY, m_tCollisionRect.right + iScrollX, m_tCollisionRect.bottom + iScrollY);
}

void CPortal::Release()
{
}

void CPortal::Change_Motion()
{
}

void CPortal::On_Motion_End()
{
}

void CPortal::Motion_Func()
{
}

void CPortal::Interaction(CObj* _pObj)
{
	SCENE_INST->Scene_Change(m_eScene);
	static_cast<CCharacter*>(_pObj)->Make_Stop();
	SOUND_INST->PlaySoundW(L"etc_warp.wav", SOUND_EFFECT, 1);
}

void CPortal::Set_Common_Motion(COMMON_STATE _eState)
{
}
