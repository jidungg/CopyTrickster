#include "stdafx.h"
#include "Town.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Player.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "TileMgr.h"
#include "Controller.h"
#include "Monster.h"
#include "UIMgr.h"
#include "MonsterSpawner.h"
#include "CharacterDataBase.h"
#include "SoundMgr.h"
#include "AbstractFactory.h"
#include "Lava.h"

CTown::CTown()
{
	m_eID = SCENE_ID::TOWN;
	m_pMapBMPKey = L"Map_Beach";
	ENV_DATA* pEnvData;
	pEnvData = new ENV_DATA(BMP_INST->Find_Img(L"ENV_town_tree1"),277,308,0,-150);
	m_vecEnvData.push_back(pEnvData);
}

CTown::~CTown()
{
	Release();
}

void CTown::Start(SCENE_ID _ePrevScene)
{
	__super::Start(_ePrevScene);
	SOUND_INST->PlayBGM(L"001_WH_pa.mp3", 0.1);


}

