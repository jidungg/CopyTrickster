#pragma once

#include "Define.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	virtual void	Initialize()PURE;
	virtual int		Update()PURE;
	virtual void	Render(HDC hDC)PURE;
	virtual void	Release()PURE;

protected:
	void		Update_Rect();

protected:
	RECT		m_tRect;
	INFO		m_tInfo;

	float		m_fSpeed;
};

