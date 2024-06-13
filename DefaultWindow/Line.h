#pragma once

#include "Define.h"

class CLine
{
public:
	CLine();
	CLine(LINEPOINT& tLeft, LINEPOINT& tRight);
	~CLine();

public:
	void		Render(HDC hDC);

public:
	LINE		Get_Info() { return m_tInfo; }
private:
	LINE		m_tInfo;
};

