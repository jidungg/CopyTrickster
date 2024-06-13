#include "stdafx.h"
#include "Item.h"
#include "CItemDataBase.h"
#include "Character.h"
#include "CItemMgr.h"

CItem::CItem(CItem& _Item)
{
	m_tStat = _Item.m_tStat;
	m_eID = _Item.m_eID;
	m_eType = _Item.m_eType;
	m_iPrice = _Item.m_iPrice;
	m_strName = _Item.m_strName;
	m_strToolTip = _Item.m_strToolTip;
}

CItem::CItem(ITEM_ID _eID)
	:m_eID(_eID)
{
}

CItem::~CItem()
{
}


bool CItem::operator==(const CItem& other) const
{
	return m_eID == other.m_eID ;
}

void CConsumableItem::Use(CCharacter* _pObj, CCharacter* _pSbj)
{
	if (m_eType != ITEM_TYPE::CONSUMABLE)
		return;
	if (m_tStat._iHP > 0)
	{
		EVENT_INST->Push_Event(new CRecoverEvent(_pObj, m_tStat._iHP, true));

	}
	if (m_tStat._iMP > 0)
	{
		EVENT_INST->Push_Event(new CRecoverEvent(_pObj, m_tStat._iMP, false));

	}
}
