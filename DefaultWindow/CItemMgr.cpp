#include "stdafx.h"
#include "CItemMgr.h"
#include "CItemDataBase.h"
#include "ObjMgr.h"
#include "Item.h"


CItemMgr* CItemMgr::m_pInstance = nullptr;
CItemMgr::CItemMgr()
{
}

CItemMgr::~CItemMgr()
{
	Release();
}

void CItemMgr::Initialize()
{
	m_Inventory.Initialize();
	//m_Inventory.Add_To_Inventory(ITEM_ID::BUNNY_EAR);
	m_Inventory.Add_To_Inventory(ITEM_ID::DAGGER);
	//m_Inventory.Add_To_Inventory(ITEM_ID::DRILL);
	for (size_t i = 0; i < 5; i++)
	{
		m_Inventory.Add_To_Inventory(ITEM_ID::PINK_POTION);
		m_Inventory.Add_To_Inventory(ITEM_ID::BLUE_POTION);
	}

}

void CItemMgr::Release()
{
}

CItem* CItemMgr::Create_Item(ITEM_ID _eID)
{
	
	return new CItem(*ITEMDB_INST->Get_ItemData(_eID));
}

bool CItemMgr::Add_To_Inventory(CItem* _pItem)
{
	return m_Inventory.Add_To_Inventory(_pItem);
}

bool CItemMgr::Add_To_Inventory(ITEM_ID _eID)
{
	return m_Inventory.Add_To_Inventory(_eID);
}

ITEM_ID CItemMgr::Remove_From_Inventory(ITEM_TYPE _eType, int _iIdx)
{
	return m_Inventory.Remove_From_Inventory(_eType, _iIdx);
}

ITEM_ID CItemMgr::Remove_From_Inventory(ITEM_ID _eID, int iAmount)
{
	return m_Inventory.Remove_From_Inventory(_eID, iAmount);

}

void CItemMgr::Equip(CItemSlot* _pSlot)
{
	ITEM_ID eInvenItem = _pSlot->Get_Item_ID();
	Remove_From_Inventory(ITEMDB_INST->Get_ItemData(eInvenItem)->m_eType,
		_pSlot->Get_Idx());
	ITEM_ID eEquippedItem = m_EquipInventory.Equip(eInvenItem);
	if (eEquippedItem == ITEM_ID::END)
		return;
	//
	Add_To_Inventory(eEquippedItem);
}

bool CItemMgr::Unequip(EQUIP_TYPE _eEtype)
{
	
	ITEM_ID eID = m_EquipInventory.Unequip(_eEtype);
	if (Add_To_Inventory(eID))
	{
		return true;
	}
	else
	{
		m_EquipInventory.Equip(eID);
		return false;
	}
}

void CItemMgr::Consume(CItemSlot* _pSlot)
{
	ITEM_ID eID = Remove_From_Inventory(ITEMDB_INST->Get_ItemData(_pSlot->Get_Item_ID())->m_eType,
		_pSlot->Get_Idx());
	auto pitem = ITEMDB_INST->Get_ItemData(eID);
	auto pConsumItem = static_cast<CConsumableItem*>(pitem);
	pConsumItem->Use((CCharacter*)OBJ_INST->Get_Player(),
		nullptr);

}

ITEM_TYPE CItemMgr::Get_Type_byID(ITEM_ID _eID)
{

	switch (_eID)
	{
	case ITEM_ID::DAGGER:
	case ITEM_ID::SWORD:
	case ITEM_ID::TURTLE_BACK:
	case ITEM_ID::SHIELD:
	case ITEM_ID::HAT:
	case ITEM_ID::HELMET:
	case ITEM_ID::BUNNY_EAR:
	case ITEM_ID::DRILL:
		return ITEM_TYPE::EQUIP;
	case ITEM_ID::PINK_POTION:
	case ITEM_ID::BLUE_POTION:
	case ITEM_ID::OCTO_LEG:
	case ITEM_ID::CRAB_FLESH:
		return ITEM_TYPE::CONSUMABLE;
	case ITEM_ID::LAPIS:
	case ITEM_ID::SCALES:
	case ITEM_ID::SPOON:
	case ITEM_ID::VINIL:
	case ITEM_ID::SHOVEL:
	case ITEM_ID::STONE:
		return ITEM_TYPE::ETC;
	case ITEM_ID::END:
	default:
		return ITEM_TYPE::END;
	}
	return ITEM_TYPE();
}

EQUIP_TYPE CItemMgr::Get_EquipType_byID(ITEM_ID _eType)
{
	switch (_eType)
	{
	case ITEM_ID::DAGGER:
		return EQUIP_TYPE::WEAPON;
	case ITEM_ID::SWORD:
		return EQUIP_TYPE::WEAPON;
	case ITEM_ID::TURTLE_BACK:
		return EQUIP_TYPE::SHIELD;
	case ITEM_ID::SHIELD:
		return EQUIP_TYPE::SHIELD;
	case ITEM_ID::HAT:
		return EQUIP_TYPE::HAT;
	case ITEM_ID::HELMET:
		return EQUIP_TYPE::HAT;
	case ITEM_ID::BUNNY_EAR:
		return EQUIP_TYPE::EAR;
	case ITEM_ID::DRILL:
		return EQUIP_TYPE::DRILL;
	default:
		return EQUIP_TYPE::END;
		break;
	}
	return EQUIP_TYPE();
}


int CItemMgr::Get_Item_Count(ITEM_ID _eID)
{
	if (_eID == ITEM_ID::END)
		return 0;
	return m_Inventory.Get_Item_Count(_eID);
}

bool CItemMgr::Check_Enough_Inventory(list<pair<ITEM_ID, int>>& _eItemList)
{
	return m_Inventory.Check_Enough_Slot(_eItemList);
}


//InventoryTab===========================================================

bool CInventoryTab::Add_Item(CItem* _pItem)
{
	return Add_Item(_pItem->m_eID);
}

bool CInventoryTab::Add_Item(ITEM_ID _eID)
{
	for (auto& iter = m_Slots.begin(); iter != m_Slots.end(); iter++)
	{
		if ((*iter)->Get_Item_ID() != ITEM_ID::END)
			continue;
		(*iter)->Insert_Item(_eID);
		return true;
	}
	return false;
}

ITEM_ID CInventoryTab::Remove_Item(int _idx)
{
	return m_Slots[_idx]->Pop_Item();
}

ITEM_ID CInventoryTab::Remove_Item(ITEM_ID _idx, int _iAmount)
{
	for (auto& i : m_Slots)
	{
		if (i->Get_Item_ID() == _idx)
		{
			for (int j = 0; j < _iAmount; j++)
			{
				ITEM_ID retID = i->Pop_Item();
				if (retID == ITEM_ID::END)
					return retID;
			}
			return _idx;
		}
	}
	return ITEM_ID::END;
}

void CInventoryTab::Reserve_Slot(int _iCount)
{
	for (int i = 0; i < _iCount; i++)
	{
		m_Slots.push_back(new CItemSlot(i));
	}
}

void CInventoryTab::Release()
{
	for (auto& i : m_Slots)
	{
		Safe_Delete(i);
	}
}

int CInventoryTab::Get_Item_Count(ITEM_ID _eID)
{
	int result = 0;
	for (auto& i : m_Slots)
	{
		if (i->Get_Item_ID() == _eID)
		{
			result =  i->Get_Count();
			continue;
		}
	}
	return result;
}

bool CInventoryTab::Check_Enough_Slot(ITEM_ID _eID, int _iCount)
{

	for (auto& slot : m_Slots)
	{
		if (slot->Get_Item_ID() == ITEM_ID::END)
		{
			_iCount--;
			if (_iCount <= 0)
				return true;
		}
	}
	return false;
}

bool CStackInventoryTab::Add_Item(CItem* _pItem)
{
	return Add_Item(_pItem->m_eID);
}

bool CStackInventoryTab::Add_Item(ITEM_ID _eID)
{
	CItemSlot* pFirstEmpty = nullptr;
	for (auto& iter = m_Slots.begin(); iter != m_Slots.end(); iter++)
	{
		if ((*iter)->Get_Item_ID() == _eID)
		{
			(*iter)->Insert_Item(_eID);
			return true;
		}
		else if (pFirstEmpty == nullptr && (*iter)->Get_Item_ID() == ITEM_ID::END)
		{
			pFirstEmpty = (*iter);

		}
	}
	if (pFirstEmpty == nullptr)
		return false;

	pFirstEmpty->Insert_Item(_eID);
	return true;
}

bool CStackInventoryTab::Check_Enough_Slot(ITEM_ID _eID, int _iCount)
{
	for (auto& slot : m_Slots)
	{
		if (slot->Get_Item_ID() == _eID || slot->Get_Item_ID() == ITEM_ID::END)
			return true;
	}
	return false;
}

void CStackInventoryTab::Reserve_Slot(int _iCount)
{
	for (int i = 0; i < _iCount; i++)
	{
		m_Slots.push_back(new CStackItemSlot(i));
	}
}

//ItemSlot==========================================================
//void CItemSlot::Insert_Item(CItem* _pItem)
//{
//	m_eID = _pItem->m_eID;
//	Safe_Delete(_pItem);
//	m_iCount = 1;
//}

void CItemSlot::Insert_Item(ITEM_ID _eID)
{
	m_eID = _eID;
	m_iCount = 1;
}

ITEM_ID CItemSlot::Pop_Item()
{
	ITEM_ID eID = m_eID;
	m_eID = ITEM_ID::END;
	m_iCount = 0;
	return eID;
}

void CItemSlot::Operate()
{
	ITEM_ID eId = Get_Item_ID();
	if (eId == ITEM_ID::END)
		return;
	ITEM_TYPE eItemType = ITEMDB_INST->Get_ItemData(Get_Item_ID())->m_eType;
	switch (eItemType)
	{
	case ITEM_TYPE::EQUIP:
		ITEM_INST->Equip(this);
		break;
	case ITEM_TYPE::CONSUMABLE:
		ITEM_INST->Consume(this);
		break;
	case ITEM_TYPE::ETC:
		break;
	case ITEM_TYPE::END:
		break;
	default:
		break;
	}
}

int  CItemSlot::Get_IconOffset()
{
	return (int)m_eID;
}
//
//void CStackItemSlot::Insert_Item(CItem* _pItem)
//{
//	if (m_iCount <= 0)
//	{
//		m_eID = _pItem->m_eID;
//		m_iCount = 0;
//	}
//	m_iCount++;
//	Safe_Delete(_pItem);
//}

void CStackItemSlot::Insert_Item(ITEM_ID _eID)
{
	if (m_iCount <= 0)
	{
		m_eID = _eID;
		m_iCount = 0;
	}
	m_iCount++;
}

ITEM_ID CStackItemSlot::Pop_Item()
{
	ITEM_ID id = m_eID;
	m_iCount--;
	if (m_iCount <= 0)
	{
		m_eID = ITEM_ID::END;
		m_iCount = 0;
	}
	return id;
}

//Inventory==========================================================
CInventory::CInventory()
{
}

CInventory::~CInventory()
{
}

void CInventory::Initialize()
{
	m_pInventoryTab[(int)ITEM_TYPE::CONSUMABLE] = new CStackInventoryTab(ITEM_TYPE::CONSUMABLE);
	m_pInventoryTab[(int)ITEM_TYPE::CONSUMABLE]->Reserve_Slot(32);
	m_pInventoryTab[(int)ITEM_TYPE::EQUIP] = new CInventoryTab(ITEM_TYPE::EQUIP);
	m_pInventoryTab[(int)ITEM_TYPE::EQUIP]->Reserve_Slot(32);
	m_pInventoryTab[(int)ITEM_TYPE::ETC] = new CStackInventoryTab(ITEM_TYPE::ETC);
	m_pInventoryTab[(int)ITEM_TYPE::ETC]->Reserve_Slot(32);
}

void CInventory::Release()
{
	for (auto& i : m_pInventoryTab)
	{
		Safe_Delete(i);
	}
}

bool CInventory::Add_To_Inventory(CItem* _pItem)
{
	return m_pInventoryTab[(int)_pItem->m_eType]->Add_Item(_pItem);
}

bool CInventory::Add_To_Inventory(ITEM_ID _eID)
{
	return m_pInventoryTab[(int)ITEMDB_INST->Get_ItemData(_eID)->m_eType]->Add_Item(_eID);;
}

ITEM_ID CInventory::Remove_From_Inventory(ITEM_TYPE _eType, int _iIdx)
{
	return	m_pInventoryTab[(int)_eType]->Remove_Item(_iIdx);
}

ITEM_ID CInventory::Remove_From_Inventory(ITEM_ID _eType, int _iAmount)
{
	return m_pInventoryTab[(int)ITEM_INST->Get_Type_byID(_eType)]->Remove_Item(_eType, _iAmount);
 
}

int CInventory::Get_Item_Count(ITEM_ID _eItemID)
{
	return m_pInventoryTab[(int)ITEM_INST->Get_Type_byID(_eItemID)]->Get_Item_Count(_eItemID);
}

bool CInventory::Check_Enough_Slot(list<pair<ITEM_ID, int>>& _eItemList)
{
	for (auto& i : _eItemList)
	{
		if (false == m_pInventoryTab[(int)ITEM_INST->Get_Type_byID(i.first)]->Check_Enough_Slot(i.first, i.second))
			return false;
	}
	return true;
}
