#include "stdafx.h"
#include "CItemDataBase.h"
CItemDataBase* CItemDataBase::m_pInstance = nullptr;
CItemDataBase::CItemDataBase()
{
}

CItemDataBase::~CItemDataBase()
{
}

void CItemDataBase::Initialize()
{
	CItem* pItem;

	{
		pItem = new CEquipItem(ITEM_ID::DAGGER, EQUIP_TYPE::WEAPON);
		pItem->m_eType = ITEM_TYPE::EQUIP;
		pItem->m_iPrice = 100;
		pItem->m_strName = L"단검";
		pItem->m_strToolTip = L"날카로운 단검. 공격속도를 빠르게 해준다.";
		pItem->m_tStat._iAttak = 100;
		pItem->m_tStat._dwAttackDelay = 1000;
		m_ItemData.insert({ pItem->m_eID, pItem });
	}
	{
		pItem = new CEquipItem(ITEM_ID::SWORD, EQUIP_TYPE::WEAPON);
		pItem->m_eType = ITEM_TYPE::EQUIP;
		pItem->m_iPrice = 100;
		pItem->m_strName = L"검";
		pItem->m_strToolTip= L"날카로운 검. 공격력이 높다.";
		pItem->m_tStat._iAttak = 150;
		pItem->m_tStat._fAttackRange = 32;
		m_ItemData.insert({pItem->m_eID, pItem});
	}
	{
		pItem = new CEquipItem(ITEM_ID::TURTLE_BACK, EQUIP_TYPE::SHIELD);
		pItem->m_eType = ITEM_TYPE::EQUIP;
		pItem->m_iPrice = 100;
		pItem->m_strName = L"거북 등딱지";
		pItem->m_strToolTip = L"단단한 거북이 등딱지. 방패로 쓸 수 있다.";
		pItem->m_tStat._iDefense = 100;
		pItem->m_tStat._iMaxHP = 1000;
		m_ItemData.insert({pItem->m_eID, pItem});
	}
	{
		pItem = new CEquipItem(ITEM_ID::SHIELD, EQUIP_TYPE::SHIELD);
		pItem->m_eType = ITEM_TYPE::EQUIP;
		pItem->m_iPrice = 200;
		pItem->m_strName = L"은방패";
		pItem->m_strToolTip = L"멋진 은색 방패.";
		pItem->m_tStat._iDefense = 200;
		pItem->m_tStat._iMaxHP = 2000;
		m_ItemData.insert({ pItem->m_eID, pItem });
	}
	{
		pItem = new CEquipItem(ITEM_ID::HAT, EQUIP_TYPE::HAT);
		pItem->m_eType = ITEM_TYPE::EQUIP;
		pItem->m_iPrice = 20;
		pItem->m_strName = L"중절모";
		pItem->m_strToolTip = L"신사용 모자.";
		pItem->m_tStat._iDefense = 10;
		pItem->m_tStat._iMaxHP = 100;
		m_ItemData.insert({ pItem->m_eID, pItem });
	}
	{
		pItem = new CEquipItem(ITEM_ID::HELMET, EQUIP_TYPE::HAT);
		pItem->m_eType = ITEM_TYPE::EQUIP;
		pItem->m_iPrice = 100;
		pItem->m_strName = L"헬멧";
		pItem->m_strToolTip = L"안전 제일.";
		pItem->m_tStat._iDefense = 100;
		pItem->m_tStat._iMaxHP = 1000;
		m_ItemData.insert({ pItem->m_eID, pItem });
	}
	{
		pItem = new CEquipItem(ITEM_ID::BUNNY_EAR, EQUIP_TYPE::EAR);
		pItem->m_eType = ITEM_TYPE::EQUIP;
		pItem->m_iPrice = 300;
		pItem->m_strName = L"토끼 머리띠";
		pItem->m_strToolTip = L"토끼 귀를 닮은 머리띠. 꽤 귀여울지도?";
		pItem->m_tStat._iCritChance = 500;
		m_ItemData.insert({pItem->m_eID, pItem});
	}
	{
		pItem = new CEquipItem(ITEM_ID::DRILL, EQUIP_TYPE::DRILL);
		pItem->m_eType = ITEM_TYPE::EQUIP;
		pItem->m_iPrice = 300;
		pItem->m_strName = L"모래 드릴 1호";
		pItem->m_strToolTip = L"장착하면 땅을 팔 수 있다. \n모래 지형에서 잘 작동한다.";
		m_ItemData.insert({ pItem->m_eID, pItem });
	}
	{
		pItem = new CConsumableItem(ITEM_ID::PINK_POTION);
		pItem->m_eType = ITEM_TYPE::CONSUMABLE;
		pItem->m_iPrice = 30;
		pItem->m_strName = L"핑크 포션 A";
		pItem->m_strToolTip = L"초급 HP 회복용 포션. 사용하면 HP를 150회복한다.";
		pItem->m_tStat._iHP = 150;
		m_ItemData.insert({ pItem->m_eID, pItem });
	}
	{
		pItem = new CConsumableItem(ITEM_ID::BLUE_POTION);
		pItem->m_eType = ITEM_TYPE::CONSUMABLE;
		pItem->m_iPrice = 30;
		pItem->m_strName = L"블루 포션 A";
		pItem->m_strToolTip = L"초급 MP 회복용 포션. 사용하면 MP를 75회복한다.";
		pItem->m_tStat._iMP = 75;
		m_ItemData.insert({ pItem->m_eID, pItem });
	}

	{
		pItem = new CItem(ITEM_ID::LAPIS);
		pItem->m_eType = ITEM_TYPE::ETC;
		pItem->m_iPrice = 1000;
		pItem->m_strName = L"라피스 라줄리";
		pItem->m_strToolTip = L"푸른색 예쁜 보석. 상점에 비싸게 팔 수 있다.";
		m_ItemData.insert({ pItem->m_eID, pItem });
	}
	{
		pItem = new CItem(ITEM_ID::SCALES);
		pItem->m_eType = ITEM_TYPE::ETC;
		pItem->m_iPrice = 20;
		pItem->m_strName = L"비늘";
		pItem->m_strToolTip = L"물고기 비늘. 여러 모로 쓰인다.";
		m_ItemData.insert({ pItem->m_eID, pItem });
	}
	{
		pItem = new CItem(ITEM_ID::SPOON);
		pItem->m_eType = ITEM_TYPE::ETC;
		pItem->m_iPrice = 20;
		pItem->m_strName = L"숟가락";
		pItem->m_strToolTip = L"녹슨 숟가락. 고물이다.";
		m_ItemData.insert({ pItem->m_eID, pItem });
	}
	{
		pItem = new CItem(ITEM_ID::VINIL);
		pItem->m_eType = ITEM_TYPE::ETC;
		pItem->m_iPrice = 20;
		pItem->m_strName = L"비닐 봉지";
		pItem->m_strToolTip = L"지구를 생각합시다.";
		m_ItemData.insert({ pItem->m_eID, pItem });
	}
	{
		pItem = new CItem(ITEM_ID::SHOVEL);
		pItem->m_eType = ITEM_TYPE::ETC;
		pItem->m_iPrice = 20;
		pItem->m_strName = L"모종삽";
		pItem->m_strToolTip = L"녹슨 모종삽.";
		m_ItemData.insert({ pItem->m_eID, pItem });
	}
	{
		pItem = new CItem(ITEM_ID::STONE);
		pItem->m_eType = ITEM_TYPE::ETC;
		pItem->m_iPrice = 50;
		pItem->m_strName = L"철광석";
		pItem->m_strToolTip = L"철이 포함된 돌멩이.";
		m_ItemData.insert({ pItem->m_eID, pItem });
	}
	{
		pItem = new CConsumableItem(ITEM_ID::CRAB_FLESH);
		pItem->m_eType = ITEM_TYPE::CONSUMABLE;
		pItem->m_iPrice = 50;
		pItem->m_strName = L"게맛살";
		pItem->m_strToolTip = L"니들이 게 맛을 알어?";
		pItem->m_tStat._iHP = 75;
		m_ItemData.insert({ pItem->m_eID, pItem });
	}
	{
		pItem = new CConsumableItem(ITEM_ID::OCTO_LEG);
		pItem->m_eType = ITEM_TYPE::CONSUMABLE;
		pItem->m_iPrice = 50;
		pItem->m_strName = L"문어 다리";
		pItem->m_strToolTip = L"통통한 문어 다리. 초장이 필요해...";
		pItem->m_tStat._iHP = 75;
		m_ItemData.insert({ pItem->m_eID, pItem });
	}
	{
		pItem = new CConsumableItem(ITEM_ID::STAR_CANDY);
		pItem->m_eType = ITEM_TYPE::CONSUMABLE;
		pItem->m_iPrice = 50;
		pItem->m_strName = L"별사탕";
		pItem->m_strToolTip = L"건빵 친구 별사탕.";
		pItem->m_tStat._iHP = 35;
		m_ItemData.insert({ pItem->m_eID, pItem });
	}
	{
		pItem = new CItem(ITEM_ID::STICKER);
		pItem->m_eType = ITEM_TYPE::ETC;
		pItem->m_iPrice = 50;
		pItem->m_strName = L"야광 스티커";
		pItem->m_strToolTip = L"어두운 곳에서 빛나는 하나의 별.";
		m_ItemData.insert({ pItem->m_eID, pItem });
	}
	{
		pItem = new CItem(ITEM_ID::DRAGON_EGG);
		pItem->m_eType = ITEM_TYPE::ETC;
		pItem->m_iPrice = 10000;
		pItem->m_strName = L"뇽의 알";
		pItem->m_strToolTip = L"스파이시 드래곤의 알. 조금 뜨겁다.";
		m_ItemData.insert({ pItem->m_eID, pItem });
	}
}
