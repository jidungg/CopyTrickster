#include "stdafx.h"
#include "CEffect.h"
#include "ScrollMgr.h"



CEffect::CEffect(EFFECT_DATA _data, int _iMotionOffset)
{
	m_tData = _data;
	m_tData.tFrame.dwTime = g_dwTime;
	m_tData.tFrame.iMotion += _iMotionOffset;
}

CEffect::~CEffect()
{
}

bool CEffect::Move_Frame()
{
	if (m_tData.tFrame.dwTime + m_tData.tFrame.dwSpeed < g_dwTime)
	{
		++m_tData.tFrame.iFrameStart;
		if (m_tData.tFrame.iFrameStart > m_tData.tFrame.iFrameEnd)
		{
			return true;
		}
		m_tData.tFrame.dwTime = g_dwTime;
	}
	return false;
}

void CEffect::Render(HDC hdc, POINT _pt)
{
	FRAME& _tFrame = m_tData.tFrame;
	POINT& _tPoint =_pt;
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	int ileft = _tPoint.x - m_tData.iRX / 2;
	int iRight = _tPoint.x + m_tData.iRX / 2;
	int iTop = _tPoint.y - m_tData.iRY / 2;
	int iBot = _tPoint.y + m_tData.iRY / 2;
	//Rectangle(hDC,  ileft+ iScrollX, iTop + iScrollY,iRight + iScrollX, iBot+ iScrollY);
	GdiTransparentBlt(hdc,
		ileft + iScrollX + m_tData.iRenderOffsetX,
		iTop + iScrollY + m_tData.iRenderOffsetY,
		m_tData.iRX,
		m_tData.iRY,
		m_tData.hMemDC,
		m_tData.iRX * _tFrame.iFrameStart,
		m_tData.iRY * _tFrame.iMotion,
		m_tData.iRX,
		m_tData.iRY,
		MAGENTA);
}

