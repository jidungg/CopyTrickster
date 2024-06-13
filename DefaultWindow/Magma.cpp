#include "stdafx.h"
#include "Magma.h"
#include "SoundMgr.h"
#include "Dragon.h"
#include "CharacterDataBase.h"
#include "ObjMgr.h"

CMagma::CMagma()
{
	m_eID = SCENE_ID::MAGMA;
	m_pMapBMPKey = L"Map_Magma";
}

CMagma::~CMagma()
{
}

void CMagma::Start(SCENE_ID _ePrevScene)
{
	__super::Start(_ePrevScene);
	SOUND_INST->PlayBGM(L"Boss_Monster.mp3", 0.5);

	CDragon* pDragon = new CDragon();
	pDragon->Set_Data(CHARDB_INST->Get_Monster_Data(MONSTER_ID::ARMORED_DRAGON));
	pDragon->Initialize();
	pDragon->Set_Pos(300,300);
	pDragon->Make_Stop();
	OBJ_INST->Add_Object(OBJ_MONSTER, pDragon);
}
