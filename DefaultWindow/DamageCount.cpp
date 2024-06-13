#include "stdafx.h"
#include "DamageCount.h"
#include "ScrollMgr.h"

CDamageCount::CDamageCount(EFFECT_DATA _data, int _iValue, bool bRising)
	:CRisingEffect(_data, 0, 1.0f, 2000), m_iValue(_iValue)
{
	while (m_iValue >=1)
	{
		int iCur = m_iValue % 10;
		m_vecNumbers.push_back(iCur);
		m_iValue /= 10;
	}
	m_iDigits = m_vecNumbers.size();
}

void CDamageCount::Render(HDC hdc, POINT _pt)
{
	if(m_bRising)
		m_tData.iRenderOffsetY -= m_fRisingSpeed;

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	int iWidth = m_tData.iRX * m_iDigits;
	int ileft= _pt.x - iWidth / 2;
	int iTop = _pt.y - m_tData.iRY / 2;

	for (int i = m_iDigits - 1; i >= 0; i--)
	{
		GdiTransparentBlt(hdc,
			ileft + iScrollX + m_tData.iRenderOffsetX + m_tData.iRX*(m_iDigits - i-1),
			iTop + iScrollY + m_tData.iRenderOffsetY,
			m_tData.iRX,
			m_tData.iRY,
			m_tData.hMemDC,
			m_tData.iRX * m_vecNumbers[i],
			0,
			m_tData.iRX,
			m_tData.iRY,
			MAGENTA);
	}


	

	//Rectangle(hDC,  ileft+ iScrollX, iTop + iScrollY,iRight + iScrollX, iBot+ iScrollY);

}

CRecoverCount::CRecoverCount(EFFECT_DATA _data, int _iValue)
	: CRisingEffect(_data, 0, 1.0f, 2000), m_iValue(_iValue)
{
	while (m_iValue >= 1)
	{
		int iCur = m_iValue % 10;
		m_vecNumbers.push_back(iCur);
		m_iValue /= 10;
	}
	m_iDigits = m_vecNumbers.size();
}

void CRecoverCount::Render(HDC hdc, POINT _pt)
{
}


