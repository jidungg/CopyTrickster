#pragma once
#include "Define.h"
class CPlayer;
class CItemSlot;
class CEquipInventory
{
public:
	CEquipInventory();
	~CEquipInventory();
	void Release();
	
	CItemSlot* Get_Slot(EQUIP_TYPE _eEType) { return m_pEquipSlots[(int)_eEType]; }
	//이미 장착돼있던 아이템 ID 반환. 
	ITEM_ID Equip(ITEM_ID _eID);
	ITEM_ID Unequip(EQUIP_TYPE _eEType);
	bool Is_Equiped(EQUIP_TYPE _eEqType);
private:
	CItemSlot* m_pEquipSlots[(int)EQUIP_TYPE::END];
	CPlayer* m_pPlayer;
};

