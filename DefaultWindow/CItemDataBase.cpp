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
		pItem->m_strName = L"�ܰ�";
		pItem->m_strToolTip = L"��ī�ο� �ܰ�. ���ݼӵ��� ������ ���ش�.";
		pItem->m_tStat._iAttak = 100;
		pItem->m_tStat._dwAttackDelay = 1000;
		m_ItemData.insert({ pItem->m_eID, pItem });
	}
	{
		pItem = new CEquipItem(ITEM_ID::SWORD, EQUIP_TYPE::WEAPON);
		pItem->m_eType = ITEM_TYPE::EQUIP;
		pItem->m_iPrice = 100;
		pItem->m_strName = L"��";
		pItem->m_strToolTip= L"��ī�ο� ��. ���ݷ��� ����.";
		pItem->m_tStat._iAttak = 150;
		pItem->m_tStat._fAttackRange = 32;
		m_ItemData.insert({pItem->m_eID, pItem});
	}
	{
		pItem = new CEquipItem(ITEM_ID::TURTLE_BACK, EQUIP_TYPE::SHIELD);
		pItem->m_eType = ITEM_TYPE::EQUIP;
		pItem->m_iPrice = 100;
		pItem->m_strName = L"�ź� �����";
		pItem->m_strToolTip = L"�ܴ��� �ź��� �����. ���з� �� �� �ִ�.";
		pItem->m_tStat._iDefense = 100;
		pItem->m_tStat._iMaxHP = 1000;
		m_ItemData.insert({pItem->m_eID, pItem});
	}
	{
		pItem = new CEquipItem(ITEM_ID::SHIELD, EQUIP_TYPE::SHIELD);
		pItem->m_eType = ITEM_TYPE::EQUIP;
		pItem->m_iPrice = 200;
		pItem->m_strName = L"������";
		pItem->m_strToolTip = L"���� ���� ����.";
		pItem->m_tStat._iDefense = 200;
		pItem->m_tStat._iMaxHP = 2000;
		m_ItemData.insert({ pItem->m_eID, pItem });
	}
	{
		pItem = new CEquipItem(ITEM_ID::HAT, EQUIP_TYPE::HAT);
		pItem->m_eType = ITEM_TYPE::EQUIP;
		pItem->m_iPrice = 20;
		pItem->m_strName = L"������";
		pItem->m_strToolTip = L"�Ż�� ����.";
		pItem->m_tStat._iDefense = 10;
		pItem->m_tStat._iMaxHP = 100;
		m_ItemData.insert({ pItem->m_eID, pItem });
	}
	{
		pItem = new CEquipItem(ITEM_ID::HELMET, EQUIP_TYPE::HAT);
		pItem->m_eType = ITEM_TYPE::EQUIP;
		pItem->m_iPrice = 100;
		pItem->m_strName = L"���";
		pItem->m_strToolTip = L"���� ����.";
		pItem->m_tStat._iDefense = 100;
		pItem->m_tStat._iMaxHP = 1000;
		m_ItemData.insert({ pItem->m_eID, pItem });
	}
	{
		pItem = new CEquipItem(ITEM_ID::BUNNY_EAR, EQUIP_TYPE::EAR);
		pItem->m_eType = ITEM_TYPE::EQUIP;
		pItem->m_iPrice = 300;
		pItem->m_strName = L"�䳢 �Ӹ���";
		pItem->m_strToolTip = L"�䳢 �͸� ���� �Ӹ���. �� �Ϳ�������?";
		pItem->m_tStat._iCritChance = 500;
		m_ItemData.insert({pItem->m_eID, pItem});
	}
	{
		pItem = new CEquipItem(ITEM_ID::DRILL, EQUIP_TYPE::DRILL);
		pItem->m_eType = ITEM_TYPE::EQUIP;
		pItem->m_iPrice = 300;
		pItem->m_strName = L"�� �帱 1ȣ";
		pItem->m_strToolTip = L"�����ϸ� ���� �� �� �ִ�. \n�� �������� �� �۵��Ѵ�.";
		m_ItemData.insert({ pItem->m_eID, pItem });
	}
	{
		pItem = new CConsumableItem(ITEM_ID::PINK_POTION);
		pItem->m_eType = ITEM_TYPE::CONSUMABLE;
		pItem->m_iPrice = 30;
		pItem->m_strName = L"��ũ ���� A";
		pItem->m_strToolTip = L"�ʱ� HP ȸ���� ����. ����ϸ� HP�� 150ȸ���Ѵ�.";
		pItem->m_tStat._iHP = 150;
		m_ItemData.insert({ pItem->m_eID, pItem });
	}
	{
		pItem = new CConsumableItem(ITEM_ID::BLUE_POTION);
		pItem->m_eType = ITEM_TYPE::CONSUMABLE;
		pItem->m_iPrice = 30;
		pItem->m_strName = L"��� ���� A";
		pItem->m_strToolTip = L"�ʱ� MP ȸ���� ����. ����ϸ� MP�� 75ȸ���Ѵ�.";
		pItem->m_tStat._iMP = 75;
		m_ItemData.insert({ pItem->m_eID, pItem });
	}

	{
		pItem = new CItem(ITEM_ID::LAPIS);
		pItem->m_eType = ITEM_TYPE::ETC;
		pItem->m_iPrice = 1000;
		pItem->m_strName = L"���ǽ� ���ٸ�";
		pItem->m_strToolTip = L"Ǫ���� ���� ����. ������ ��ΰ� �� �� �ִ�.";
		m_ItemData.insert({ pItem->m_eID, pItem });
	}
	{
		pItem = new CItem(ITEM_ID::SCALES);
		pItem->m_eType = ITEM_TYPE::ETC;
		pItem->m_iPrice = 20;
		pItem->m_strName = L"���";
		pItem->m_strToolTip = L"����� ���. ���� ��� ���δ�.";
		m_ItemData.insert({ pItem->m_eID, pItem });
	}
	{
		pItem = new CItem(ITEM_ID::SPOON);
		pItem->m_eType = ITEM_TYPE::ETC;
		pItem->m_iPrice = 20;
		pItem->m_strName = L"������";
		pItem->m_strToolTip = L"�콼 ������. ���̴�.";
		m_ItemData.insert({ pItem->m_eID, pItem });
	}
	{
		pItem = new CItem(ITEM_ID::VINIL);
		pItem->m_eType = ITEM_TYPE::ETC;
		pItem->m_iPrice = 20;
		pItem->m_strName = L"��� ����";
		pItem->m_strToolTip = L"������ �����սô�.";
		m_ItemData.insert({ pItem->m_eID, pItem });
	}
	{
		pItem = new CItem(ITEM_ID::SHOVEL);
		pItem->m_eType = ITEM_TYPE::ETC;
		pItem->m_iPrice = 20;
		pItem->m_strName = L"������";
		pItem->m_strToolTip = L"�콼 ������.";
		m_ItemData.insert({ pItem->m_eID, pItem });
	}
	{
		pItem = new CItem(ITEM_ID::STONE);
		pItem->m_eType = ITEM_TYPE::ETC;
		pItem->m_iPrice = 50;
		pItem->m_strName = L"ö����";
		pItem->m_strToolTip = L"ö�� ���Ե� ������.";
		m_ItemData.insert({ pItem->m_eID, pItem });
	}
	{
		pItem = new CConsumableItem(ITEM_ID::CRAB_FLESH);
		pItem->m_eType = ITEM_TYPE::CONSUMABLE;
		pItem->m_iPrice = 50;
		pItem->m_strName = L"�Ը���";
		pItem->m_strToolTip = L"�ϵ��� �� ���� �˾�?";
		pItem->m_tStat._iHP = 75;
		m_ItemData.insert({ pItem->m_eID, pItem });
	}
	{
		pItem = new CConsumableItem(ITEM_ID::OCTO_LEG);
		pItem->m_eType = ITEM_TYPE::CONSUMABLE;
		pItem->m_iPrice = 50;
		pItem->m_strName = L"���� �ٸ�";
		pItem->m_strToolTip = L"������ ���� �ٸ�. ������ �ʿ���...";
		pItem->m_tStat._iHP = 75;
		m_ItemData.insert({ pItem->m_eID, pItem });
	}
	{
		pItem = new CConsumableItem(ITEM_ID::STAR_CANDY);
		pItem->m_eType = ITEM_TYPE::CONSUMABLE;
		pItem->m_iPrice = 50;
		pItem->m_strName = L"������";
		pItem->m_strToolTip = L"�ǻ� ģ�� ������.";
		pItem->m_tStat._iHP = 35;
		m_ItemData.insert({ pItem->m_eID, pItem });
	}
	{
		pItem = new CItem(ITEM_ID::STICKER);
		pItem->m_eType = ITEM_TYPE::ETC;
		pItem->m_iPrice = 50;
		pItem->m_strName = L"�߱� ��ƼĿ";
		pItem->m_strToolTip = L"��ο� ������ ������ �ϳ��� ��.";
		m_ItemData.insert({ pItem->m_eID, pItem });
	}
	{
		pItem = new CItem(ITEM_ID::DRAGON_EGG);
		pItem->m_eType = ITEM_TYPE::ETC;
		pItem->m_iPrice = 10000;
		pItem->m_strName = L"���� ��";
		pItem->m_strToolTip = L"�����̽� �巡���� ��. ���� �̴߰�.";
		m_ItemData.insert({ pItem->m_eID, pItem });
	}
}
