#pragma once
#include "Define.h"

class CDropMgr
{
#pragma region Singleton
private:
	CDropMgr();
	~CDropMgr();

public:
	static CDropMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CDropMgr;

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
	static CDropMgr* m_pInstance;

#pragma endregion
public:
	void Initialize();
	void Release();
	ITEM_ID Get_Drop_Item(MONSTER_ID _eMonID );
	ITEM_ID Get_Digging_Item();
	void Drop_Item(ITEM_ID, POINT _pt);
	int Get_Total_Weight(vector<pair<ITEM_ID, int>>* _pList);
private:
	map < MONSTER_ID, vector<pair<ITEM_ID, int>>*> m_DropTable;
};

#define DROP_INST CDropMgr::Get_Instance()
