#include "stdafx.h"
#include "RisingEffect.h"
#include "ScrollMgr.h"


CRisingEffect::CRisingEffect(EFFECT_DATA _data, int _iMotionOffset, float _fSpeed, DWORD _dwRisingTime)
	:CEffect(_data,_iMotionOffset),  m_fRisingSpeed(_fSpeed)
{
	m_tData.tFrame.dwSpeed = _dwRisingTime;
}

void CRisingEffect::Render(HDC hdc, POINT _pt)
{
	m_tData.iRenderOffsetY -= m_fRisingSpeed;

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	int ileft = _pt.x - m_tData.iRX / 2;
	int iTop = _pt.y - m_tData.iRY / 2;
	//Rectangle(hDC,  ileft+ iScrollX, iTop + iScrollY,iRight + iScrollX, iBot+ iScrollY);
	GdiTransparentBlt(hdc,
		ileft + iScrollX + m_tData.iRenderOffsetX,
		iTop + iScrollY + m_tData.iRenderOffsetY,
		m_tData.iRX,
		m_tData.iRY,
		m_tData.hMemDC,
		m_tData.iRX * m_tData.tFrame.iFrameStart,
		m_tData.iRY * m_tData.tFrame.iMotion,
		m_tData.iRX,
		m_tData.iRY,
		MAGENTA);
}
