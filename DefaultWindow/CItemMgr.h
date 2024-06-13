#pragma once
#include "EquipInventory.h"
#include "Quest.h"

class CItem;
class CItemSlot
{
public:
	CItemSlot() = default;
	CItemSlot(int _iIdx): m_iIdx(_iIdx){}
	virtual ~CItemSlot() { Release(); }

	//virtual void Insert_Item(CItem* _pItem);
	virtual void Insert_Item(ITEM_ID _eID);
	virtual ITEM_ID Pop_Item();
	ITEM_ID Get_Item_ID() { return m_eID; }
	int		Get_Idx() { return m_iIdx; }
	void Release() {}
	int Get_Count() { return m_iCount; }
	SLOT_TYPE Get_Slot_Type() { return m_eSlotType; }
	virtual void Operate();
	virtual int Get_IconOffset();
protected:
	SLOT_TYPE m_eSlotType = SLOT_TYPE::END;
	ITEM_ID m_eID = ITEM_ID::END;
	int m_iIdx;
	int m_iCount = 0;
public:

};


class CStackItemSlot : public CItemSlot
{
public:
	CStackItemSlot(int _iIdx) : CItemSlot(_iIdx) { m_eSlotType = SLOT_TYPE::INVEN; }
	~CStackItemSlot() { Release(); }
	void Release() {}

	//void Insert_Item(CItem* _pItem) override;
	void Insert_Item(ITEM_ID _eID) override;
	ITEM_ID Pop_Item();
	
protected:

};
class CInventoryTab
{
public:
	CInventoryTab(ITEM_TYPE _eType) : m_eType(_eType){}
	virtual ~CInventoryTab() { Release(); }

	virtual bool Add_Item(CItem* _pItem);
	virtual bool Add_Item(ITEM_ID _eID);
	virtual ITEM_ID Remove_Item(int _idx);
	virtual ITEM_ID Remove_Item(ITEM_ID _idx, int _iAmount);
	virtual void Reserve_Slot(int _iCount);
	void Release();
	int Get_Slot_Count() { return m_Slots.size(); }
	CItemSlot* Get_Nth_Slot(int _iIdx) { return m_Slots[_iIdx]; }
	int Get_Item_Count(ITEM_ID _eID);
	virtual bool Check_Enough_Slot(ITEM_ID _eID, int _iCount);
protected:
	ITEM_TYPE m_eType;
	vector< CItemSlot*> m_Slots;
};

class CStackInventoryTab : public CInventoryTab
{
public:
	CStackInventoryTab(ITEM_TYPE _eType) : CInventoryTab(_eType) {}
	bool Add_Item(CItem* _pItem) override;
	bool Add_Item(ITEM_ID _eID)override;
	virtual bool Check_Enough_Slot(ITEM_ID _eID, int _iCount);
	virtual void Reserve_Slot(int _iCount) override;
};

class CInventory
{
public:
	CInventory();
	~CInventory();
	void Initialize();
	void Release();

	bool Add_To_Inventory(CItem* _pItem);
	bool Add_To_Inventory(ITEM_ID _eID);
	ITEM_ID Remove_From_Inventory(ITEM_TYPE _eType, int _iIdx);
	ITEM_ID Remove_From_Inventory(ITEM_ID _eType, int _iAmount);
	int Get_Slot_Count() { return m_pInventoryTab[0]->Get_Slot_Count(); }
	int Get_Item_Count(ITEM_ID _eItemID);
	CInventoryTab* Get_Inventory_Tab(ITEM_TYPE _etype) { return m_pInventoryTab[(int)_etype]; }
	bool Check_Enough_Slot(list<pair<ITEM_ID, int>>& _eItemList);
private:
	CInventoryTab* m_pInventoryTab[(int)ITEM_TYPE::END];
};
class CItemMgr
{
private:
	CItemMgr();
	~CItemMgr();
#pragma region Singleton
public:
	static CItemMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CItemMgr;

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

private:
	static CItemMgr* m_pInstance;
#pragma endregion
public:
	void Initialize();
	void Release();

	CInventory* Get_Inventory() { return &m_Inventory; }
	CEquipInventory* Get_Equip_Inventory() { return &m_EquipInventory; }

	CItem* Create_Item(ITEM_ID _eID);
	bool Add_To_Inventory(CItem* _pItem);
	bool Add_To_Inventory(ITEM_ID _eID);
	ITEM_ID Remove_From_Inventory(ITEM_TYPE _eType, int _iIdx);
	ITEM_ID Remove_From_Inventory(ITEM_ID _eID, int iAmount);
	//_pSlot : 장착할 아이템이 있는 인벤토리의 슬롯
	void Equip(CItemSlot* _pSlot);
	bool Unequip(EQUIP_TYPE _eEtype);
	void Consume(CItemSlot* _pSlot);
	ITEM_TYPE Get_Type_byID(ITEM_ID);
	EQUIP_TYPE Get_EquipType_byID(ITEM_ID _eType);
	int Get_Item_Count(ITEM_ID);
	void Gain_Gold(int _iGelder) { m_iGelder += _iGelder; }
	bool Check_Enough_Inventory(list<pair<ITEM_ID, int>>& _eItemList);
	bool Is_Equiped(EQUIP_TYPE _eEqType) {return m_EquipInventory.Is_Equiped(_eEqType); }
private:
	CInventory m_Inventory;
	CEquipInventory m_EquipInventory;
	int m_iGelder;
};

#define ITEM_INST CItemMgr:: Get_Instance()