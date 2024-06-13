#pragma once

#include "Obj.h"

class CPlayer;
class CObjMgr
{
private:
	CObjMgr();
	~CObjMgr();

public:
	static CObjMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CObjMgr;

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


public:
	CObj*		Get_Target(OBJ_ID eID, CObj* pObj);
	CObj*	Get_Player();
	void		Delete_ID(OBJ_ID eID);

public:
	void		Add_Object(OBJ_ID eID, CObj* pObj);
	void		Update();
	void		Late_Update();
	void		Render(HDC hDC);
	void		Release();

	CObj*		IsInObj(OBJ_ID _eID, POINT _pt);
	CObj*		IsInObj( POINT _pt);
	void		ResetObjList();
private:
	list<CObj*>		m_ObjList[OBJ_END];

	list<CObj*>		m_RenderList[RENDER_END];

	static CObjMgr*	m_pInstance;
};

#define OBJ_INST CObjMgr::Get_Instance()
