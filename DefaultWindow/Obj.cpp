#include "stdafx.h"
#include "Obj.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"


CObj::CObj() : m_eCurDir(DIR_END) , m_bDead(false)
, m_eRender(RENDER_END)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRenderRect, sizeof(RECT));
	ZeroMemory(&m_tFrame, sizeof(FRAME));
}


CObj::~CObj()
{
}

void CObj::Update_Rect()
{
	m_tRenderRect.left = long(m_tInfo.fX - Get_RX() / 2.f)  + m_iRenderOffsetX;
	m_tRenderRect.top = long(m_tInfo.fY - Get_RY() / 2.f) + m_iRenderOffsetY;
	m_tRenderRect.right = long(m_tInfo.fX + Get_RX() / 2.f) + m_iRenderOffsetX;
	m_tRenderRect.bottom = long(m_tInfo.fY + Get_RY() / 2.f) + m_iRenderOffsetY;
	m_tCollisionRect.left = long(m_tInfo.fX - Get_CX() / 2.f);
	m_tCollisionRect.top = long(m_tInfo.fY - Get_CY() / 2.f);
	m_tCollisionRect.right = long(m_tInfo.fX + Get_CX() / 2.f);
	m_tCollisionRect.bottom = long(m_tInfo.fY + Get_CY() / 2.f);
}

void CObj::Move_Frame()
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < g_dwTime)
	{
		//모션 특정 프레임에 실행할 함수가 있으면
		if (m_tFrame.vecFuncFrame != nullptr &&m_tFrame.vecFuncFrame->empty()== false)
		{
			if (m_tFrame.iCurFuncIdx < m_tFrame.vecFuncFrame->size())
			{
				//현재 프레임이 함수 실행할 프레임이면
				if (m_tFrame.iFrameStart == (*m_tFrame.vecFuncFrame)[m_tFrame.iCurFuncIdx])
				{
					Motion_Func();
					m_tFrame.iCurFuncIdx++;
				}
			}
	
		}
		++m_tFrame.iFrameStart;
		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
		{
			if (m_tFrame.bRepeat)
			{
				m_tFrame.iFrameStart = 0;
				m_tFrame.iCurFuncIdx = 0;
			}
			else
			{
				On_Motion_End();
				m_bMotionEnded = true;
				m_tFrame.iFrameStart = m_tFrame.iFrameEnd;
			}
		}

		m_tFrame.dwTime = g_dwTime;
	}
}

POINT CObj::Get_RenderPoint()
{
	return { (int)m_tInfo.fX + Get_RenderOffsetX(),(int)m_tInfo.fY + Get_RenderOffsetY() };
}

void CObj::On_Collision(CObj* _pObj)
{
}

void CObj::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_tFrame.pFrameKey);

	//Rectangle(hDC, m_tCollisionRect.left + iScrollX, m_tCollisionRect.top + iScrollY, m_tCollisionRect.right + iScrollX, m_tCollisionRect.bottom + iScrollY);
	GdiTransparentBlt(hDC,
		m_tRenderRect.left + iScrollX,
		m_tRenderRect.top + iScrollY,
		(int)m_tInfo.fRX,
		(int)m_tInfo.fRY,
		hMemDC,
		(int)m_tInfo.fRX * m_tFrame.iFrameStart,
		(int)m_tInfo.fRY * m_tFrame.iMotion,
		(int)m_tInfo.fRX,
		(int)m_tInfo.fRY,
		MAGENTA);
}

DIRECTION CObj::Calc_Dir(POINT _tP)
{
	float fRad = Calc_Radius(_tP);

	return Calc_Dir(fRad);
}

DIRECTION CObj::Calc_Dir(float _fRad)
{
	float fAbsRad = abs(_fRad);

	if (fAbsRad <= PI / 8)
	{
		return DIR_RIGHT;
	}
	else if (fAbsRad <= (RD_RAD + PI / 8))
	{
		return _fRad > 0 ? DIR_RD : DIR_RU;
	}
	else if (fAbsRad <= (DOWN_RAD + PI / 8))
	{
		return _fRad > 0 ? DIR_DOWN : DIR_UP;

	}
	else if (fAbsRad <= (LD_RAD + PI / 8))
	{
		return _fRad > 0 ? DIR_LD : DIR_LU;

	}
	else
	{
		return DIR_LEFT;

	}



	return DIR_END;
}

DIRECTION CObj::Calc_FDir(POINT _tP)
{
	POINT tP = Get_Point();
	if (tP.x > _tP.x)
	{
		if (tP.y > _tP.y)
		{
			return DIR_LU;
		}
		else
		{
			return DIR_LD;
		}
	}
	else
	{
		if (tP.y > _tP.y)
		{
			return DIR_RU;
		}
		else
		{
			return DIR_RD;
		}
	}
	return DIRECTION();
}

DIRECTION CObj::EDir_To_FDir(DIRECTION _eDir)
{
	switch (_eDir)
	{
	case DIR_UP:
		return DIR_RU;
	case DIR_LU:
		return DIR_LU;
	case DIR_LEFT:
		return DIR_LD;
	case DIR_LD:
		return DIR_LD;
	case DIR_DOWN:
		return DIR_LD;
	case DIR_RD:
		return DIR_RD;
	case DIR_RIGHT:
		return DIR_RD;
	case DIR_RU:
		return DIR_RU;
	case DIR_END:
	default:
		return DIR_END;
	}
}

DIRECTION CObj::EDir_To_TDir(DIRECTION _eDir)
{
	DIRECTION dir = EDir_To_FDir(_eDir);
	switch (dir)
	{

	case DIR_LU:
		return DIR_LD;
	case DIR_LD:
		return DIR_LD;
	case DIR_RD:
		return DIR_RD;
	case DIR_RU:
		return DIR_RD;
	case DIR_END:
	default:
		break;
	}
}

int CObj::FDir_To_Motion_Idx(DIRECTION _eDir)
{
	switch (_eDir)
	{
	case DIR_LD:
		return 0;
	case DIR_LU:
		return 1;
	case DIR_RD:
		return 2;
	case DIR_RU:
		return 3;
	default:
		return 0;
	}
}

int CObj::TDir_To_Motion_Idx(DIRECTION _eDir)
{
	switch (_eDir)
	{
	case DIR_LD:
		return 0;
	case DIR_RD:
		return 1;
	default:
		return 0;
	}
}

float CObj::Calc_Radius(POINT _tP)
{
	float fDX = _tP.x - m_tInfo.fX;
	float fDY = _tP.y - m_tInfo.fY;
	float fDist = sqrtf(fDX * fDX + fDY * fDY);
	float fRad = acosf(fDX / fDist);
	if (fDY < 0)
		fRad = -fRad;
	return fRad;
}

float CObj::Get_Current_Radius()
{
	switch (m_eCurDir)
	{
	case DIR_UP:
		return UP_RAD;
	case DIR_LU:
		return LU_RAD;
	case DIR_LEFT:
		return LEFT_RAD;
	case DIR_LD:
		return LD_RAD;
	case DIR_DOWN:
		return DOWN_RAD;
	case DIR_RD:
		return RD_RAD;
	case DIR_RIGHT:
		return RIGHT_RAD;
	case DIR_RU:
		return RU_RAD;
	case DIR_END:
	default:
		break;
	}
	return 0.0f;
}
