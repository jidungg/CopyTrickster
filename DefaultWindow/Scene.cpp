#include "stdafx.h"
#include "Scene.h"
#include "BmpMgr.h"
#include "TileMgr.h"
#include "MonsterSpawner.h"
#include "AbstractFactory.h"
#include "Portal.h"
#include "ObjMgr.h"
#include "NPC.h"
#include "CharacterDataBase.h"
#include "ScrollMgr.h"
#include "UIMgr.h"
#include "EffectMgr.h"
#include "SoundMgr.h"
#include "EnvObj.h"

CScene::CScene()
{
}


CScene::~CScene()
{
}

void CScene::Initialize()
{
	m_hMapDC = BMP_INST->Find_Img(m_pMapBMPKey);

	HBITMAP hBitMap = CBmpMgr::Get_Instance()->Find_BITMAP(m_pMapBMPKey);
	BITMAP bit;
	GetObject(hBitMap, sizeof(BITMAP), &bit);
	m_iMapX = bit.bmWidth;
	m_iMapY = bit.bmHeight;
	
}

void CScene::Start(SCENE_ID _ePrevScene)
{

	TILE_INST->Load_Tile(m_eID);

	auto vecMonsterTile = TILE_INST->Get_Tiles(TILE_TYPE::MONSTER);
	for (auto& tile : *vecMonsterTile)
	{
		int opt = tile->Get_Tile_Data().iOption;
		if (opt < 0 || opt >=(int)MONSTER_ID::END)
			continue;
		auto pSpawner = new CMonsterSpawner(10000, tile->Get_Pos(), (MONSTER_ID)opt);
		m_vecMonSpawner.push_back(pSpawner);
		pSpawner->Initialize();
	}
	Safe_Delete(vecMonsterTile);

	auto vecNPCTile = TILE_INST->Get_Tiles(TILE_TYPE::NPC);
	for (auto& tile : *vecNPCTile)
	{
		int opt = tile->Get_Tile_Data().iOption;
		if (opt <0 || opt >=(int) NPC_ID::END)
			continue;
		CCharacter* pNPC = (CCharacter*)CAbstractFactory<CNPC>::Create(tile->Get_Pos());
		pNPC->Initialize();
		pNPC->Set_Data(CHARDB_INST->Get_NPC_Data((NPC_ID)opt));
		pNPC->Set_Pos(tile->Get_Pos().x, tile->Get_Pos().y);
		pNPC->Make_Stop();
		OBJ_INST->Add_Object(OBJ_ID::OBJ_NPC, pNPC);
	}
	Safe_Delete(vecNPCTile);

	auto vecPortalTile = TILE_INST->Get_Tiles(TILE_TYPE::PORTAL);
	for (auto& tile : *vecPortalTile)
	{
		int opt = tile->Get_Tile_Data().iOption;
		CPortal* pPortal = (CPortal*)CAbstractFactory<CPortal>::Create(tile->Get_Pos());
		pPortal->Set_Scene((SCENE_ID)opt);
		OBJ_INST->Add_Object(OBJ_ID::OBJ_PORTAL, pPortal);
		if (pPortal->Get_Scene() == _ePrevScene )
		{
			CObj* pPlayer = OBJ_INST->Get_Player();
			pPlayer->Set_Pos(pPortal->Get_Point().x, pPortal->Get_Point().y);
			SCROLL_INST->Set_ScrollX(-(pPlayer->Get_Point().x -WINCX/2));
			SCROLL_INST->Set_ScrollY(-(pPlayer->Get_Point().y -WINCY/2));
		}
	}
	if (_ePrevScene == SCENE_ID::RYTHM)
	{
		POINT tPortalPos = (*vecPortalTile->begin())->Get_Pos();
		CObj* pPlayer = OBJ_INST->Get_Player();
		pPlayer->Set_Pos(tPortalPos.x, tPortalPos.y);
		SCROLL_INST->Set_ScrollX(-(pPlayer->Get_Point().x - WINCX / 2));
		SCROLL_INST->Set_ScrollY(-(pPlayer->Get_Point().y - WINCY / 2));
	}
	Safe_Delete(vecPortalTile);

	auto vecEnvTile = TILE_INST->Get_Tiles(TILE_TYPE::ENV);
	for (auto& tile : *vecEnvTile)
	{
		int opt = tile->Get_Tile_Data().iOption;
		if (opt < 0 || opt >= m_vecEnvData.size())
			continue;
		CEnvObj* pEnv = new CEnvObj(*m_vecEnvData[opt],tile->Get_Pos());
		OBJ_INST->Add_Object(OBJ_ENV,pEnv);
	}
	Safe_Delete(vecEnvTile);


}

int CScene::Update()
{
	OBJ_INST->Update();
	//TILE_INST->Update();
	for (auto& i : m_vecMonSpawner)
	{
		i->Update();
	}
	return 0;
}

void CScene::Late_Update()
{
	OBJ_INST->Late_Update();
}

void CScene::Render(HDC hDC)
{

	int	iScrollX = (int)SCROLL_INST->Get_ScrollX();
	int	iScrollY = (int)SCROLL_INST->Get_ScrollY();

	BitBlt(hDC, 
		0, 0, WINCX, WINCY,
		m_hMapDC,
		-iScrollX, -iScrollY,
		SRCCOPY);
	if (g_bEditMode) TILE_INST->Render(hDC);
	OBJ_INST->Render(hDC);
	EFFECT_INST->Render(hDC);
	UI_INST->Render(hDC);
}

void CScene::End()
{
	OBJ_INST->ResetObjList();
	for (auto& i : m_vecMonSpawner)
	{
		Safe_Delete(i);
	}
	m_vecMonSpawner.clear();
	SOUND_INST->StopSound(CHANNELID::SOUND_BGM);
}

void CScene::Release()
{
	for (auto& i : m_vecMonSpawner)
	{
		Safe_Delete(i);
	}
	m_vecMonSpawner.clear();
}

void CScene::Revive()
{
}
