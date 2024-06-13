#pragma once

#include "Define.h"

class CScrollMgr
{
private:
	CScrollMgr();
	~CScrollMgr();

public:
	float		Get_ScrollX() { return m_fScrollX; }
	float		Get_ScrollY() { return m_fScrollY; }

public:
	void		Move_ScrollX(float _fX) { m_fScrollX += _fX; }
	void		Move_ScrollY(float _fY) { m_fScrollY += _fY; }

	void		Set_ScrollX(float _fX) { m_fScrollX = _fX; }
	void		Set_ScrollY(float _fY) { m_fScrollY = _fY; }
	void		Scroll_Lock();

public:
	static CScrollMgr*		Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CScrollMgr;

		return m_pInstance;
	}

	static void		Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CScrollMgr*	m_pInstance;

	float		m_fScrollX = 0;
	float		m_fScrollY = 0;
};

#define SCROLL_INST CScrollMgr::Get_Instance()
