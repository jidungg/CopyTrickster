#include "stdafx.h"
#include "EnvObj.h"
#include "ScrollMgr.h"

CEnvObj::CEnvObj(ENV_DATA& _eEnvData, POINT _pt)
{
    m_tInfo.fX = _pt.x;
    m_tInfo.fY = _pt.y;
    m_iRenderOffsetX = _eEnvData.iROffX;
    m_iRenderOffsetY = _eEnvData.iROffY;
    m_tInfo.fRX = _eEnvData.iRX;
    m_tInfo.fRY = _eEnvData.iRY;
    m_hDC = _eEnvData.hDC;
    m_eRender = RENDER_GAMEOBJECT;
    m_eObjID = OBJ_ENV;
}

CEnvObj::~CEnvObj()
{
	Release();
}

void CEnvObj::Set_Common_Motion(COMMON_STATE _eState)
{
}

void CEnvObj::Render(HDC hdc)
{
    int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
    int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
    GdiTransparentBlt(hdc,
        m_tRenderRect.left + iScrollX ,
        m_tRenderRect.top + iScrollY,
        (int)m_tInfo.fRX,
        (int)m_tInfo.fRY,
        m_hDC,
        0,
        0,
        (int)m_tInfo.fRX,
        (int)m_tInfo.fRY,
        MAGENTA);
}

void CEnvObj::Initialize()
{
}

int CEnvObj::Update()
{
    Update_Rect();
	return 0;
}

void CEnvObj::Late_Update()
{
}

void CEnvObj::Release()
{
}

void CEnvObj::Change_Motion()
{
}

void CEnvObj::On_Motion_End()
{
}

void CEnvObj::Motion_Func()
{
}

void CEnvObj::Interaction(CObj* _pObj)
{
}
