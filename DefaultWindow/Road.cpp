#include "stdafx.h"
#include "Road.h"
#include "BmpMgr.h"
#include "SoundMgr.h"

CRoad::CRoad()
{
	m_eID = SCENE_ID::ROAD;
	m_pMapBMPKey = L"Map_Road";
	ENV_DATA* pEnvData;
	pEnvData = new ENV_DATA(BMP_INST->Find_Img(L"ENV_road_tree1"), 250, 300, 0, -100);
	m_vecEnvData.push_back(pEnvData);
	
}

CRoad::~CRoad()
{
	Release();
}

void CRoad::Start(SCENE_ID _ePrevScene)
{
	__super::Start(_ePrevScene);
	SOUND_INST->PlayBGM(L"002_MP_fd.mp3", 0.5);
}
