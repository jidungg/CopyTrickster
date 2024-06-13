#include "stdafx.h"
#include "SceneMgr.h"
#include "Town.h"
#include "UIMgr.h"
#include "Road.h"
#include "Magma.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "RythmGame.h"
#include "Player.h"
#include "Intro.h"
#include "SoundMgr.h"



CSceneMgr*	CSceneMgr::m_pInstance = nullptr;

CSceneMgr::CSceneMgr() : m_pScene(nullptr), m_ePreScene(SCENE_ID::END), m_eCurScene(SCENE_ID::TOWN)
{
}

CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::Initialize()
{
	CScene* pScene;
	pScene = new CIntro();
	pScene->Initialize();
	m_vecScene.insert({SCENE_ID::INTRO ,pScene });
	pScene = new CRythmGame();
	pScene->Initialize();
	m_vecScene.insert({ SCENE_ID::RYTHM,pScene });
	pScene= new CTown;
	pScene->Initialize();
	m_vecScene.insert({ SCENE_ID::TOWN, pScene });
	pScene = new CRoad;
	pScene->Initialize();
	m_vecScene.insert({ SCENE_ID::ROAD,pScene });
	pScene = new CMagma;
	pScene->Initialize();
	m_vecScene.insert({ SCENE_ID::MAGMA, pScene });
	m_pScene = m_vecScene[SCENE_ID::RYTHM];
}

void CSceneMgr::Scene_Change(SCENE_ID eScene)
{
	m_pScene->End();
	SCENE_ID ePrevScene = m_pScene->Get_Scene_ID();
	m_pScene = m_vecScene[eScene];
	m_pScene->Start(ePrevScene);
	
}

void CSceneMgr::Update()
{

	m_pScene->Update();
}

void CSceneMgr::Late_Update()
{
	m_pScene->Late_Update();
}

void CSceneMgr::Render(HDC hDC)
{
	m_pScene->Render(hDC);
	
}

void CSceneMgr::Release()
{
	Safe_Delete(m_pScene);
}

void CSceneMgr::Revive()
{
	auto pPlayer = (CPlayer*)OBJ_INST->Get_Player();

	pPlayer->Revive();
}
