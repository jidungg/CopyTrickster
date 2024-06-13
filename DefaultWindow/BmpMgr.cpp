#include "stdafx.h"
#include "BmpMgr.h"

CBmpMgr*	CBmpMgr::m_pInstance = nullptr;

CBmpMgr::CBmpMgr()
{
}

CBmpMgr::~CBmpMgr()
{
	Release();
}

void CBmpMgr::Insert_Bmp(const TCHAR * pFilePath, const TCHAR * pImgKey)
{
	auto	iter = find_if(m_mapBit.begin(), m_mapBit.end(), [&](auto& MyPair)->bool
	{
		if (!lstrcmp(MyPair.first, pImgKey))
			return true;

		return false;
	});

	if (iter == m_mapBit.end())
	{
		CMyBmp*	pBmp = new CMyBmp;
		pBmp->Load_Bmp(pFilePath);

		m_mapBit.emplace(pImgKey, pBmp);
	}
}

HDC CBmpMgr::Find_Img(const TCHAR * pImgKey)
{
	auto	iter = find_if(m_mapBit.begin(), m_mapBit.end(), [&](auto& MyPair)->bool
	{
		if (!lstrcmp(MyPair.first, pImgKey))
			return true;

		return false;
	});

	if (iter == m_mapBit.end())
		return nullptr;

	return iter->second->Get_MemDC();
}

HBITMAP CBmpMgr::Find_BITMAP(const TCHAR* pImgKey)
{
	auto	iter = find_if(m_mapBit.begin(), m_mapBit.end(), [&](auto& MyPair)->bool
		{
			if (!lstrcmp(MyPair.first, pImgKey))
				return true;

			return false;
		});

	if (iter == m_mapBit.end())
		return nullptr;
	return iter->second->Get_BITMAP();
}

HDC CBmpMgr::Get_IconDC(SLOT_TYPE _eType)
{
	switch (_eType)
	{
	case SLOT_TYPE::INVEN:
	case SLOT_TYPE::EQUIP:
		return Find_Img(L"UI_Item_Icon");
		break;
	case SLOT_TYPE::SKILL:
		return Find_Img(L"UI_Icon_Skill");
		break;
	case SLOT_TYPE::END:
		break;
	default:
		break;
	}
	return HDC();
}

void CBmpMgr::Release()
{
	for_each(m_mapBit.begin(), m_mapBit.end(), [](auto& MyPair)
	{
		if (MyPair.second)
		{
			delete MyPair.second;
			MyPair.second = nullptr;
		}
	});

	m_mapBit.clear();
}
