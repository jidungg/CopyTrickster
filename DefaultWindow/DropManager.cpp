#include "stdafx.h"
#include "DropManager.h"
#include "Item.h"
#include "ObjItem.h"
#include "ObjMgr.h"

CDropMgr* CDropMgr::m_pInstance = nullptr;
CDropMgr::CDropMgr()
{
}

CDropMgr::~CDropMgr()
{
}

void CDropMgr::Initialize()
{
	MONSTER_ID eMonID;
	vector<pair<ITEM_ID, int>>* pData;

	eMonID = MONSTER_ID::MUMMY;
	pData = new vector<pair<ITEM_ID, int>>;
	pData->push_back({ITEM_ID::BLUE_POTION, 100});
	pData->push_back({ITEM_ID::LAPIS, 30});
	pData->push_back({ITEM_ID::SPOON, 500});
	pData->push_back({ ITEM_ID::END, 200 });
	m_DropTable.insert({ eMonID, pData });

	eMonID = MONSTER_ID::OCTOPUS;
	pData = new vector<pair<ITEM_ID, int>>;
	pData->push_back({ ITEM_ID::PINK_POTION, 400 });
	pData->push_back({ ITEM_ID::STAR_CANDY,400 });
	pData->push_back({ ITEM_ID::OCTO_LEG, 500 });
	pData->push_back({ ITEM_ID::END, 200 });
	m_DropTable.insert({ eMonID, pData });

	eMonID = MONSTER_ID::ARMORED_DRAGON;
	pData = new vector<pair<ITEM_ID, int>>;
	pData->push_back({ ITEM_ID::END, 200 });
	m_DropTable.insert({ eMonID, pData });

	eMonID = MONSTER_ID::UNARMORED_DRAGON;
	pData = new vector<pair<ITEM_ID, int>>;
	pData->push_back({ ITEM_ID::DRAGON_EGG, 500 });
	m_DropTable.insert({ eMonID, pData });

}

void CDropMgr::Release()
{
	for (auto& i : m_DropTable)
	{
		Safe_Delete(i.second);
	}
	m_DropTable.clear();
}

ITEM_ID CDropMgr::Get_Drop_Item(MONSTER_ID _eMonID)
{
	auto pData = m_DropTable[_eMonID];
	int iTotalWeight  = Get_Total_Weight(pData);
	int iRand = rand() % iTotalWeight;
	int iCurWeight = 0;
	for (auto& i : *pData)
	{
		if ( iRand <iCurWeight+ i.second)
		{
			return i.first;
		}
		iCurWeight += i.second;
	}

	return ITEM_ID::END;
}

ITEM_ID CDropMgr::Get_Digging_Item()
{
	int r = rand() % 8;
	switch (r)
	{
	case 0:
		return ITEM_ID::LAPIS;
	case 1:
		return ITEM_ID::SCALES;
	case 2:
		return ITEM_ID::VINIL;
	case 3:
		return ITEM_ID::SHOVEL;
	case 4:
		return ITEM_ID::STONE;
	default:
		return ITEM_ID::VINIL;
		break;
	}
}

void CDropMgr::Drop_Item(ITEM_ID _eID, POINT _pt)
{
	CObjItem* pNewItem = new CObjItem(_eID,_pt);
	OBJ_INST->Add_Object(OBJ_ITEM, pNewItem);
}

int CDropMgr::Get_Total_Weight(vector<pair<ITEM_ID, int>>* _pList)
{
	int result = 0;
	for (auto& i : *_pList)
	{
		result += i.second;
	}
	return result;
}
