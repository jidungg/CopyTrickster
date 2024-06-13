#pragma once
#include "Define.h"
#include "IUsable.h"


class CCharacter;
struct CItem
{
	CItem(CItem& _Item); 
	CItem(ITEM_ID _eID);
	~CItem();

public:
	bool operator==(const CItem& other) const;
	STAT m_tStat;
	ITEM_ID m_eID;
	ITEM_TYPE m_eType;
	int m_iPrice;
	wstring m_strName;
	wstring m_strToolTip;
};

struct CConsumableItem : public CItem, public IQuickSlotRegister
{
	CConsumableItem(ITEM_ID _eID):CItem(_eID) {}
	// IUsable을(를) 통해 상속됨
	void Use(CCharacter* _pObj, CCharacter* _pSbj) override;
};
struct CEquipItem : public CItem
{
public:
	CEquipItem(ITEM_ID _eID, EQUIP_TYPE _eEType): CItem(_eID),m_eEuipType(_eEType) {}
	~CEquipItem() {}
	EQUIP_TYPE m_eEuipType;
};