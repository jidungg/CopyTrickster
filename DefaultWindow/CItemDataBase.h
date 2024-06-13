#pragma once
#include "Define.h"
#include "Item.h"

class CItemDataBase
{
private:
	CItemDataBase();
	~CItemDataBase();
#pragma region Singleton
public:
	static CItemDataBase* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CItemDataBase;

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
	static CItemDataBase* m_pInstance;
#pragma endregion
public:
	void Initialize();
	CItem* Get_ItemData(ITEM_ID _eID) { return m_ItemData[_eID]; }
private:
	map<ITEM_ID, CItem*> m_ItemData;
};
#define ITEMDB_INST CItemDataBase::Get_Instance()
