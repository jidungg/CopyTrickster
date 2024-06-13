#include "stdafx.h"
#include "MouseMgr.h"
#include "Define.h"
CMouseMgr* CMouseMgr::m_pInstance = nullptr;
CMouseMgr::CMouseMgr()
{
}

CMouseMgr::~CMouseMgr()
{
}

POINT CMouseMgr::Get_Mouse_Point()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	return pt;
}
