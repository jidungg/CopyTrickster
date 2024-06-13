#include "stdafx.h"
#include "Lava.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "EventMgr.h"
#include "Character.h"
#include "ScrollMgr.h"

CLava::CLava()
{

    int iR = rand() % 3;

    m_tInfo.fRX = 182;
    m_tInfo.fRY = 88;
    m_tInfo.fCX = 0;
    m_tInfo.fCY = 0;
    m_hBMPDC = BMP_INST->Find_Img(L"OBJ_Lava");
    m_tFrame.iMotion = iR;
    m_tFrame.iFrameStart = 0;
    m_tFrame.iFrameEnd = 5;
    m_tFrame.dwSpeed = 400;
    m_tFrame.dwTime = 0;
    m_tFrame.bRepeat= true;
    m_tFrame.vecFuncFrame = new vector<int>{0, 1, 2, 3, 4, 5};
    m_eRender = RENDERID::RENDER_BULLET;
    m_eObjID = OBJ_M_BULLET;
}


void CLava::Initialize()
{
}

void CLava::Render(HDC hdc)
{
    int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
    int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
    GdiTransparentBlt(hdc,
        m_tRenderRect.left + iScrollX,
        m_tRenderRect.top + iScrollY,
        (int)m_tInfo.fRX,
        (int)m_tInfo.fRY,
        m_hBMPDC,
        (int)m_tInfo.fRX * m_tFrame.iFrameStart,
        (int)m_tInfo.fRY * m_tFrame.iMotion,
        (int)m_tInfo.fRX,
        (int)m_tInfo.fRY,
        MAGENTA);
}

int CLava::Update()
{
    __super::Update_Rect();
    return m_bDead ? OBJ_DEAD : OBJ_NOEVENT;
}

void CLava::Late_Update()
{
    Move_Frame();
}

void CLava::Release()
{
}

void CLava::Set_Common_Motion(COMMON_STATE _eState)
{
}
void CLava::Change_Motion()
{
}

void CLava::On_Motion_End()
{
}

void CLava::Motion_Func()
{
    CObj* pPlayer = OBJ_INST->Get_Player();
    RECT	rc{};
    if (IntersectRect(&rc, &pPlayer->Get_CollisionRect(), &m_tRenderRect))
    {
        EVENT_INST->Push_Event(new CDamageEvent((CCharacter*)this, (CCharacter*)pPlayer, m_iAttack, false, EFFECT_ID::NORMAL_HIT));
    }

}

void CLava::Interaction(CObj* _pObj)
{
}

void CLava::On_Collision(CObj* _pObj)
{

}
