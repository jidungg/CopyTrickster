#include "stdafx.h"
#include "MainGame.h"

#include "SceneMgr.h"

#include "AbstractFactory.h"
#include "CollisionMgr.h"
#include "Mouse.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "TileMgr.h"
#include "Controller.h"
#include "Mouse.h"
#include "EventMgr.h"
#include "UIMgr.h"
#include "CharacterDataBase.h"
#include "EffectMgr.h"
#include "SoundMgr.h"
#include "CItemDataBase.h"
#include "CItemMgr.h"
#include "QuestMgr.h"
#include "DropManager.h"


CMainGame::CMainGame() :m_dwTime(GetTickCount()), m_iFps(0)
{
	ZeroMemory(m_szFPS, sizeof(m_szFPS));
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	srand(unsigned(time(NULL)));

	m_DC = GetDC(g_hWnd);
	
	Load_Resources();
	CHARDB_INST->Initialize();
	EFFECT_INST->Initialize();
	SOUND_INST->Initialize();
	ITEMDB_INST->Initialize();

	CPlayer* pPlayer = static_cast<CPlayer*>(CAbstractFactory<CPlayer>::Create({ WINCX / 2, WINCY / 2 }, CHARDB_INST->Get_Player_Data()));
	OBJ_INST->Add_Object(OBJ_PLAYER, pPlayer);
	ITEM_INST->Initialize();
	CONTROLLER_INST->Set_Player(pPlayer);
	UI_INST->Initialize();
	SCENE_INST->Initialize();
	CONTROLLER_INST->Initialize();
	QUEST_INST->Initialize();
	DROP_INST->Initialize();

	SCENE_INST->Scene_Change(SCENE_ID::TOWN);
#ifdef _DEBUG

	if (::AllocConsole() == TRUE)
	{
		FILE* nfp[3];
		freopen_s(nfp + 0, "CONOUT$", "rb", stdin);
		freopen_s(nfp + 1, "CONOUT$", "wb", stdout);
		freopen_s(nfp + 2, "CONOUT$", "wb", stderr);
		std::ios::sync_with_stdio();
	}

#endif // _DEBUG

	ShowCursor(false);
}

void CMainGame::Update()
{
	SCENE_INST->Update();
	CONTROLLER_INST->Update();
	UI_INST->Update();
}

void CMainGame::Late_Update()
{

	EVENT_INST->Proc_Event();
	EFFECT_INST->Late_Update();
	SCENE_INST->Late_Update();	
	KEY_INST->Key_Update();
	CONTROLLER_INST->Late_Update();
	UI_INST->Late_Update();
	SCROLL_INST->Scroll_Lock();
}

void CMainGame::Render()
{

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Back");
	SCENE_INST->Render(hMemDC);
	CONTROLLER_INST->Render(hMemDC);
	BitBlt(m_DC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
		


	++m_iFps;
	if (m_dwTime + 1000 < g_dwTime)
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFps);
		SetWindowText(g_hWnd, m_szFPS);

		m_iFps = 0;
		m_dwTime = g_dwTime;
	}
}

void CMainGame::Release()
{
#ifdef  DEBUG
		FreeConsole();
#endif //  DEBUG

	CTileMgr::Destroy_Instance();
	CBmpMgr::Destroy_Instance();
	CScrollMgr::Destroy_Instance();
	CKeyMgr::Destroy_Instance();
	CLineMgr::Destroy_Instance();
	CSceneMgr::Destroy_Instance();
	CObjMgr::Destroy_Instance();
	CController::Destroy_Instance();
	CUIMgr::Destroy_Instance();
	CCharacterDataBase::Destroy_Instance();
	CEffectMgr::Destroy_Instance();
	CSoundMgr::Destroy_Instance();
	CController::Destroy_Instance();
	CEventMgr::Destroy_Instance();
	CItemDataBase::Destroy_Instance();
	CItemMgr::Destroy_Instance();
	CQuestMgr::Destroy_Instance();
	CDropMgr::Destroy_Instance();

	ReleaseDC(g_hWnd, m_DC);	
}

void CMainGame::Load_Resources()
{
	BMP_INST->Insert_Bmp(L"../Image/Back.bmp", L"Back");
	BMP_INST->Insert_Bmp(L"../Image/Map/beach-Sheet.bmp", L"Map_Beach");
	BMP_INST->Insert_Bmp(L"../Image/Map/magma-Sheet.bmp", L"Map_Magma");
	BMP_INST->Insert_Bmp(L"../Image/Map/road-Sheet.bmp", L"Map_Road");

	BMP_INST->Insert_Bmp(L"../Image/NPC/Maid-Sheet.bmp", L"NPC_Maid");
	BMP_INST->Insert_Bmp(L"../Image/NPC/bunny_main_ilu.bmp", L"NPC_Maid_Ilust");
	BMP_INST->Insert_Bmp(L"../Image/NPC/hunter_girl.bmp", L"NPC_Hunter");
	BMP_INST->Insert_Bmp(L"../Image/NPC/hunter_girl_ilu.bmp", L"NPC_Hunter_Ilust");

#pragma region PlayerBMP

	BMP_INST->Insert_Bmp(L"../Image/Player/bunny_arm_idle_sheet.bmp",	L"Player_Arm_Idle");
	BMP_INST->Insert_Bmp(L"../Image/Player/bunny_arm_walk_sheet.bmp",	L"Player_Arm_Walk");
	BMP_INST->Insert_Bmp(L"../Image/Player/bunny_arm_run_sheet.bmp",	L"Player_Arm_Run");
	BMP_INST->Insert_Bmp(L"../Image/Player/bunny_arm_drill_sheet.bmp",	L"Player_Arm_Drill");
	
	
	BMP_INST->Insert_Bmp(L"../Image/Player/bunny_body_drill_sheet.bmp", L"Player_Body_Drill");
	BMP_INST->Insert_Bmp(L"../Image/Player/bunny_body_run_sheet.bmp",	L"Player_Body_Run");
	BMP_INST->Insert_Bmp(L"../Image/Player/bunny_body_walk_sheet.bmp",	L"Player_Body_Walk");
	BMP_INST->Insert_Bmp(L"../Image/Player/bunny_body_idle_sheet.bmp",	L"Player_Body_Idle");
	BMP_INST->Insert_Bmp(L"../Image/Player/bunny_body_attack_critical_sheet.bmp",	L"Player_Body_CritAttack");
	BMP_INST->Insert_Bmp(L"../Image/Player/bunny_body_attack_snap_sheet.bmp",	L"Player_Body_SnapAttack");
	BMP_INST->Insert_Bmp(L"../Image/Player/bunny_body_attack_normal_sheet.bmp",	L"Player_Body_NormalAttack");
	BMP_INST->Insert_Bmp(L"../Image/Player/charge_attack-Sheet.bmp",	L"Player_Charge_Attack");
	BMP_INST->Insert_Bmp(L"../Image/Player/bunny_body_battle_idle.bmp",	L"Player_Body_Battle");
	BMP_INST->Insert_Bmp(L"../Image/Player/bunny_body_drill_sheet.bmp",	L"Player_Body_Drill");
	BMP_INST->Insert_Bmp(L"../Image/Player/bunny_body_hit_sheet.bmp",	L"Player_Body_Hit");
	BMP_INST->Insert_Bmp(L"../Image/Player/grooming.bmp",	L"Player_Body_Grooming");

	BMP_INST->Insert_Bmp(L"../Image/Equip/battle_idle-Sheet.bmp",	L"Ear_Battle_Idle");
	BMP_INST->Insert_Bmp(L"../Image/Equip/equip_bunny_ear_idle_sheet.bmp",	L"Ear_Idle");
	BMP_INST->Insert_Bmp(L"../Image/Equip/equip_bunny_ear_attack_critical_sheet.bmp",	L"Ear_Critical");
	BMP_INST->Insert_Bmp(L"../Image/Equip/equip_bunny_ear_attack_normal_sheet.bmp",	L"Ear_Normal");
	BMP_INST->Insert_Bmp(L"../Image/Equip/equip_bunny_ear_attack_snap_sheet.bmp",	L"Ear_Snap");
	BMP_INST->Insert_Bmp(L"../Image/Equip/equip_bunny_ear_drill_sheet-Sheet.bmp",	L"Ear_Drill");
	BMP_INST->Insert_Bmp(L"../Image/Equip/equip_bunny_ear_run_sheet.bmp",	L"Ear_Run");
	BMP_INST->Insert_Bmp(L"../Image/Equip/equip_bunny_ear_walk_sheet.bmp",	L"Ear_Walk");
	BMP_INST->Insert_Bmp(L"../Image/Equip/equip_bunny_hit_sheet.bmp",	L"Ear_Hit");
	BMP_INST->Insert_Bmp(L"../Image/Equip/charge_attack_ear.bmp",	L"Ear_Charge");


	BMP_INST->Insert_Bmp(L"../Image/Equip/equip_drill_sheet.bmp",	L"Equip_Drill");
#pragma endregion


	BMP_INST->Insert_Bmp(L"../Image/Monster/monster_mummy_sheet.bmp",	L"Monster_Mummy");
	BMP_INST->Insert_Bmp(L"../Image/Monster/dragon_armored-Sheet.bmp",	L"Monster_Dragon_Armored");
	BMP_INST->Insert_Bmp(L"../Image/Monster/dragon_unarmored1.bmp",	L"Monster_Dragon_Unarmored1");
	BMP_INST->Insert_Bmp(L"../Image/Monster/dragon_attack.bmp",	L"Monster_Dragon_Attack");
	BMP_INST->Insert_Bmp(L"../Image/Monster/dragon_dead.bmp",	L"Monster_Dragon_Dead");
	BMP_INST->Insert_Bmp(L"../Image/Monster/octopus_sheet.bmp",	L"Monster_Octopus");


	
	BMP_INST->Insert_Bmp(L"../Image/Portal/portal.bmp",	L"Portal");
	
#pragma region UIBMP
	BMP_INST->Insert_Bmp(L"../Image/UI/start_button.bmp", L"UI_GameStart");

	BMP_INST->Insert_Bmp(L"../Image/UI/Window/Inventory_template_active.bmp", L"UI_Inventory_Active");
	BMP_INST->Insert_Bmp(L"../Image/UI/Window/Inventory_template_deactive.bmp", L"UI_Inventory_Deactive");
	BMP_INST->Insert_Bmp(L"../Image/UI/Window/equip_template_active.bmp", L"UI_EquipInven_Active");
	BMP_INST->Insert_Bmp(L"../Image/UI/Window/equip_template_deactive.bmp", L"UI_EquipInven_Deactive");
	BMP_INST->Insert_Bmp(L"../Image/UI/Window/skill_template_active.bmp", L"UI_SkillInven_Active");
	BMP_INST->Insert_Bmp(L"../Image/UI/Window/skill_template_deactive.bmp", L"UI_SkillInven_Deactive");
	BMP_INST->Insert_Bmp(L"../Image/UI/Quickslot/quick_slot.bmp", L"UI_QuickSlot");
	BMP_INST->Insert_Bmp(L"../Image/UI/Window/quest_template_active.bmp", L"UI_Quest_Active");
	BMP_INST->Insert_Bmp(L"../Image/UI/WIndow/quest_template_deactive.bmp", L"UI_Quest_Deactive");
	BMP_INST->Insert_Bmp(L"../Image/UI/WIndow/quest_side.bmp", L"UI_Quest_Side");
	BMP_INST->Insert_Bmp(L"../Image/UI/WIndow/quest_row_active.bmp", L"UI_Quest_Row_Active");
	BMP_INST->Insert_Bmp(L"../Image/UI/WIndow/quest_row_button.bmp", L"UI_Quest_Row_Button");

	BMP_INST->Insert_Bmp(L"../Image/UI/Window/window_minimal_deactive.bmp", L"UI_WIndow_Minimal_Deactive");
	BMP_INST->Insert_Bmp(L"../Image/UI/Window/window_minimal_active.bmp", L"UI_WIndow_Minimal_Active");

	BMP_INST->Insert_Bmp(L"../Image/UI/Icon/menu_icon_sheet.bmp", L"UI_Icon_Menu");
	BMP_INST->Insert_Bmp(L"../Image/Skill/skill_sheet.bmp", L"UI_Icon_Skill");
	BMP_INST->Insert_Bmp(L"../Image/Skill/skill_cooltime.bmp", L"UI_Skill_Cooltime");
	BMP_INST->Insert_Bmp(L"../Image/UI/Icon/window_button_icon_sheet.bmp", L"UI_Icon_WinButton");
	BMP_INST->Insert_Bmp(L"../Image/UI/Window/Inventory_slot.bmp", L"UI_Inven_Slot");
	BMP_INST->Insert_Bmp(L"../Image/Item/item_icons-Sheet.bmp", L"UI_Item_Icon");
	BMP_INST->Insert_Bmp(L"../Image/UI/Window/tab_indicator_left.bmp", L"UI_Tab_Indicator_Left");
	BMP_INST->Insert_Bmp(L"../Image/UI/Window/tab_indicator_right.bmp", L"UI_Tab_Indicator_Right");
	BMP_INST->Insert_Bmp(L"../Image/UI/Window/tab_indicator_mid.bmp", L"UI_Tab_Indicator_Mid");

	BMP_INST->Insert_Bmp(L"../Image/UI/HUD/player_gauge_left.bmp", L"UI_Player_Gauge_Left");
	BMP_INST->Insert_Bmp(L"../Image/UI/HUD/player_gauge_mid.bmp", L"UI_Player_Gauge_Mid");
	BMP_INST->Insert_Bmp(L"../Image/UI/HUD/player_gauge_right.bmp", L"UI_Player_Gauge_Right");
	BMP_INST->Insert_Bmp(L"../Image/UI/HUD/player_gauge_hp.bmp", L"UI_Player_Gauge_Hp");
	BMP_INST->Insert_Bmp(L"../Image/UI/HUD/player_gauge_mp.bmp", L"UI_Player_Gauge_Mp");
	BMP_INST->Insert_Bmp(L"../Image/UI/MonsterHP/frame_left.bmp", L"UI_MonsterHP_frame_Left");
	BMP_INST->Insert_Bmp(L"../Image/UI/MonsterHP/frame_mid.bmp", L"UI_MonsterHP_frame_Mid");
	BMP_INST->Insert_Bmp(L"../Image/UI/MonsterHP/frame_right.bmp", L"UI_MonsterHP_frame_Right");
	BMP_INST->Insert_Bmp(L"../Image/UI/MonsterHP/fill_01.bmp", L"UI_MonsterHP_Fill_01");

	BMP_INST->Insert_Bmp(L"../Image/UI/NPC/balloon.bmp", L"UI_NPC_Balloon");

	BMP_INST->Insert_Bmp(L"../Image/UI/drill_frame.bmp",	L"UI_Drill");
	BMP_INST->Insert_Bmp(L"../Image/UI/drill_fill.bmp",	L"UI_Drill_Fill");
	BMP_INST->Insert_Bmp(L"../Image/UI/drill_indicator.bmp",	L"UI_Drill_Indicator");

	BMP_INST->Insert_Bmp(L"../Image/UI/Minimap/frame.bmp",	L"UI_Minimap_Frame");
	BMP_INST->Insert_Bmp(L"../Image/UI/Minimap/magma.bmp",	L"UI_Minimap_Magma");
	BMP_INST->Insert_Bmp(L"../Image/UI/Minimap/road.bmp",	L"UI_Minimap_Road");
	BMP_INST->Insert_Bmp(L"../Image/UI/Minimap/beach.bmp",	L"UI_Minimap_Town");
	BMP_INST->Insert_Bmp(L"../Image/UI/Minimap/portal.bmp",	L"UI_Minimap_Portal");
	BMP_INST->Insert_Bmp(L"../Image/UI/Minimap/player.bmp",	L"UI_Minimap_Player");

	BMP_INST->Insert_Bmp(L"../Image/UI/intro_base800.nri_0.bmp",	L"UI_Loading_Ilu1");
	BMP_INST->Insert_Bmp(L"../Image/UI/LoadingImg_1.bmp",			L"UI_Loading_Ilu2");
	BMP_INST->Insert_Bmp(L"../Image/UI/LoadingImg_4.bmp",			L"UI_Loading_Ilu3");
#pragma endregion

	BMP_INST->Insert_Bmp(L"../Image/Effect/lava.bmp",	L"OBJ_Lava");
	BMP_INST->Insert_Bmp(L"../Image/cursor_sheet.bmp",	L"UI_Cursor");


	BMP_INST->Insert_Bmp(L"../Image/ENV/road_tree1.bmp",	L"ENV_road_tree1");
	BMP_INST->Insert_Bmp(L"../Image/ENV/town_tree1.bmp",	L"ENV_town_tree1");

	BMP_INST->Insert_Bmp(L"../Image/Rythm/back.bmp",	L"RYTHM_Back");
	BMP_INST->Insert_Bmp(L"../Image/Rythm/frame.bmp",	L"RYTHM_Frame");
	BMP_INST->Insert_Bmp(L"../Image/Rythm/normal_buttons.bmp",	L"RYTHM_Normal_Buttons");
	BMP_INST->Insert_Bmp(L"../Image/Rythm/click_buttons.bmp",	L"RYTHM_Click_Buttons");
	BMP_INST->Insert_Bmp(L"../Image/Rythm/note.bmp",	L"RYTHM_Note");
	BMP_INST->Insert_Bmp(L"../Image/Rythm/d.bmp",	L"RYTHM_Ilu");

}
