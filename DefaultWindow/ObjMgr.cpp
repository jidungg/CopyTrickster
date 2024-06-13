#include "stdafx.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"

CObjMgr*	CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr()
{
}

CObjMgr::~CObjMgr()
{
	Release();
}

CObj * CObjMgr::Get_Target(OBJ_ID eID, CObj * pObj)
{
	if (m_ObjList[eID].empty())
		return nullptr;

	CObj*	pTarget = nullptr;

	float	fDistance(0.f);

	for (auto& Src : m_ObjList[eID])
	{
		if(Src->Get_Dead())
			continue;

		float		fWidth = pObj->Get_Info().fX - Src->Get_Info().fX;
		float		fHeight = pObj->Get_Info().fY - Src->Get_Info().fY;

		float		fDiagonal = sqrt(fWidth * fWidth + fHeight * fHeight);

		if ((!pTarget) || (fDistance > fDiagonal))
		{
			pTarget = Src;
			fDistance = fDiagonal;
		}

	}	
	
	return pTarget;
}

CObj* CObjMgr::Get_Player()
{
	
	return ((*m_ObjList[OBJ_PLAYER].begin()));
}

void CObjMgr::Delete_ID(OBJ_ID eID)
{
	for (auto& pObj : m_ObjList[eID])
		Safe_Delete(pObj);

	m_ObjList[eID].clear();
}

void CObjMgr::Add_Object(OBJ_ID eID, CObj * pObj)
{
	if (OBJ_END <= eID || nullptr == pObj)
		return;

	m_ObjList[eID].push_back(pObj);
}

void CObjMgr::Update()
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto iter = m_ObjList[i].begin(); iter != m_ObjList[i].end(); )
		{
			int iResult = (*iter)->Update();

			if (OBJ_DEAD == iResult)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
				++iter;
		}
	}
}

void CObjMgr::Late_Update()
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto iter = m_ObjList[i].begin(); iter != m_ObjList[i].end(); ++iter)
		{
			(*iter)->Late_Update();

			if (m_ObjList[i].empty())
				break;		

			RENDERID eRender = (*iter)->Get_RenderID();
			m_RenderList[eRender].push_back(*iter);
		}
	}
	//CCollisionMgr::Collision_Rect(m_ObjList[OBJ_ID::OBJ_PLAYER], m_ObjList[OBJ_M_BULLET]);
}

void CObjMgr::Render(HDC hDC)
{
	for (size_t i = 0; i < RENDER_END; ++i)
	{	
		m_RenderList[i].sort([](CObj* Dst, CObj* Src)->bool
		{
			return Dst->Get_Info().fY < Src->Get_Info().fY;
		});

		for(auto& pObj : m_RenderList[i])
			pObj->Render(hDC);
	
		m_RenderList[i].clear();
	}
}

void CObjMgr::Release()
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<CObj*>);
		m_ObjList[i].clear();
	}
}

CObj* CObjMgr::IsInObj(OBJ_ID _eID, POINT _pt)
{
	
	for (auto iter = m_ObjList[_eID].begin(); iter != m_ObjList[_eID].end(); iter++)
	{
		if (PtInRect(&(*iter)->Get_CollisionRect(), _pt))
			return (*iter);
	}
	
	return nullptr;
}

CObj* CObjMgr::IsInObj(POINT _pt)
{
	for (auto& li : m_ObjList)
	{
		for (auto& i : li)
		{
			if (PtInRect(&i->Get_CollisionRect(), _pt))
				return i;
		}
	}
	return nullptr;
}

void CObjMgr::ResetObjList()
{
	for (int i = 0; i < OBJ_ID::OBJ_END; i++)
	{
		if (i == OBJ_PLAYER)
			continue;
		Delete_ID((OBJ_ID)i);
	}
}
