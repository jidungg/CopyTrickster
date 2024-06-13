#include "stdafx.h"
#include "EquipInventory.h"
#include "CItemMgr.h"
#include "CItemDataBase.h"
#include "Player.h"
#include "ObjMgr.h"


CEquipInventory::CEquipInventory()
{
	for (int i = 0; i < (int)EQUIP_TYPE::END; i++)
	{

		m_pEquipSlots[i] = new CItemSlot(i);
	}
	m_pPlayer = static_cast<CPlayer*>( OBJ_INST->Get_Player());
}

CEquipInventory::~CEquipInventory()
{
	Release();
}

void CEquipInventory::Release()
{
	for (auto& i : m_pEquipSlots)
	{
		Safe_Delete(i);
	}
}

ITEM_ID CEquipInventory::Equip(ITEM_ID _eID)
{
	CItem* pItem = ITEMDB_INST->Get_ItemData(_eID);
	EQUIP_TYPE eType = static_cast<CEquipItem*>(pItem)->m_eEuipType;
	ITEM_ID eIID = m_pEquipSlots[(int)eType]->Get_Item_ID();
	m_pEquipSlots[(int)eType]->Insert_Item(_eID);
	m_pPlayer->AddStat(pItem->m_tStat);
	return eIID;
}

ITEM_ID CEquipInventory::Unequip(EQUIP_TYPE _eEType)
{
	ITEM_ID eItemID = m_pEquipSlots[(int)_eEType]->Get_Item_ID();
	CItem* pItem = ITEMDB_INST->Get_ItemData(eItemID);
	m_pPlayer->SubStat(pItem->m_tStat);
	return m_pEquipSlots[(int)_eEType]->Pop_Item();
}

bool CEquipInventory::Is_Equiped(EQUIP_TYPE _eEqType)
{
	return m_pEquipSlots[(int)_eEqType]->Get_Item_ID() != ITEM_ID::END;
}