#include "stdafx.h"
#include "Player.h"
#include "AbstractFactory.h"
#include "ScrewBullet.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "LineMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "TileMgr.h"
#include "EventMgr.h"
#include "EffectMgr.h"
#include "BasicAttack.h"
#include "EnergyPunch.h"
#include "TrippleAttack.h"
#include <string>
#include "DropManager.h"
#include "CItemMgr.h"
#include "SkillSlot.h"
#include "SoundMgr.h"
#include "ThunderPunch.h"
CPlayer::CPlayer() : m_bRun(false)

{
}


CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_ePreState = (int)PLAYER_STATE::ST_END;
	m_eCurState = (int)PLAYER_STATE::IDLE;
	m_eCurDir = DIR_DOWN;
	m_eRender = RENDER_GAMEOBJECT;
	m_eObjID = OBJ_PLAYER;

	m_SkillInven.insert({SKILL_ID::BASIC_ATTACK, new CSkillSlot(SKILL_ID::BASIC_ATTACK,new CBasicAttack(m_tStat._dwAttackDelay, m_tStat._fAttackRange))});
	m_SkillInven.insert({SKILL_ID::ENERGY_PUNCH,  new CSkillSlot(SKILL_ID::ENERGY_PUNCH,new CEnergyPunch())});
	m_SkillInven.insert({SKILL_ID::THUNDER_PUNCH, new CSkillSlot(SKILL_ID::THUNDER_PUNCH,new CThunderPunch())});
	m_hDrillDC = BMP_INST->Find_Img(L"Equip_Drill");
	m_hDrillUIDC = BMP_INST->Find_Img(L"UI_Drill");
	m_hDrillGuageFillDC = BMP_INST->Find_Img(L"UI_Drill_Fill");
	m_hDrillIndicatorDC= BMP_INST->Find_Img(L"UI_Drill_Indicator");

	m_tDrillFrame.iFrameEnd = 3;
	m_tDrillFrame.iFrameStart= 0;
	m_tDrillFrame.dwSpeed= 200;
	m_tDrillFrame.dwTime= 0;
	m_tDrillFrame.bRepeat= true;
	m_tDrillFrame.bMotionCancelable= true;
}
int CPlayer::Update()
{
	if (m_eCurState != (int)PLAYER_STATE::DEAD)
	{
		if (m_bRenderDrill)
		{
			Update_Drill_Guage();
		}
		return __super::Update();
	}
	return OBJ_NOEVENT;
}
void CPlayer::Late_Update()
{
	if(g_bEditMode == false)
		Offset();
	Change_Motion();

	__super::Move_Frame();
	if(m_bRenderDrill)
		Update_Drill_Frame();
	//TMP
	if(m_SkillInven[m_eCurSkill]->Get_Skill()->Is_Running())
		m_SkillInven[m_eCurSkill]->Get_Skill()->Late_Update();
}
void CPlayer::Offset()
{
	int	iOffSetminX = WINCX/2 - 10;
	int	iOffSetmaxX = WINCX/2 + 10;

	int	iOffSetminY = WINCY/2 - 10;
	int	iOffSetmaxY = WINCY/2 + 10;

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//왼쪽으로 넘어감
	if (iOffSetminX > m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Move_ScrollX(abs(Get_X_Speed()));
	//오른쪽으로 넘어감
	if (iOffSetmaxX < m_tInfo.fX + iScrollX)
		CScrollMgr::Get_Instance()->Move_ScrollX(-abs(Get_X_Speed()));
	//위쪽으로 넘어감
	if (iOffSetminY > m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Instance()->Move_ScrollY(abs(Get_Y_Speed()));
	//아래쪽으로 넘어감
	if (iOffSetmaxY < m_tInfo.fY + iScrollY)
		CScrollMgr::Get_Instance()->Move_ScrollY(-abs(Get_Y_Speed()));
}
void CPlayer::Render(HDC hDC)
{
	CCharacter::Render(hDC);
	if(m_bRenderArm)
		RenderArm(hDC);
	if (m_bRenderDrill)
		RenderDrill(hDC);
	if (ITEM_INST->Is_Equiped(EQUIP_TYPE::EAR))
		RenderEar(hDC);

	//TMP
	if (m_SkillInven[m_eCurSkill]->Get_Skill()->Is_Running())
		m_SkillInven[m_eCurSkill]->Get_Skill()->Render(hDC);
}
void CPlayer::RenderArm(HDC hdc)
{
	//if (m_bAttack)
	//	return;
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pArmFrameKey);

	GdiTransparentBlt(hdc,
		m_tRenderRect.left + iScrollX,
		m_tRenderRect.top + iScrollY,
		(int)m_tInfo.fRX,
		(int)m_tInfo.fRY,
		hMemDC,
		(int)m_tInfo.fRX * m_tFrame.iFrameStart,
		(int)m_tInfo.fRY * m_tFrame.iMotion,
		(int)m_tInfo.fRX,
		(int)m_tInfo.fRY,
		MAGENTA);
}

void CPlayer::RenderEar(HDC hdc)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Img(m_pEarFrameKey);

	GdiTransparentBlt(hdc,
		m_tRenderRect.left + iScrollX,
		m_tRenderRect.top + iScrollY,
		(int)m_tInfo.fRX,
		(int)m_tInfo.fRY,
		hMemDC,
		(int)m_tInfo.fRX * m_tFrame.iFrameStart,
		(int)m_tInfo.fRY * m_tFrame.iMotion,
		(int)m_tInfo.fRX,
		(int)m_tInfo.fRY,
		MAGENTA);
}

void CPlayer::Release()
{
	for (auto& i : m_SkillInven)
	{
		Safe_Delete(i.second);
	}
	m_SkillInven.clear();
}

float CPlayer::Get_X_Speed()
{
	float fSpd = CCharacter::Get_X_Speed();
	return  m_bRun? fSpd*1.5f : fSpd;
}
float CPlayer::Get_Y_Speed()
{
	float fSpd = CCharacter::Get_Y_Speed();
	return  m_bRun ? fSpd * 1.5f : fSpd;
}

void CPlayer::Revive()
{
	Recover_HP(999999);
	Recover_MP(999999);
	Set_Common_Motion(COMMON_STATE::IDLE);
	for (auto& i : m_SkillInven)
	{
		i.second->Get_Skill()->On_Motion_End();
	}
	m_bDead = false;
}

float CPlayer::Get_CooltimeRatio(SKILL_ID _eID)
{
	DWORD dwRemain = m_SkillInven[_eID]->Get_Skill()->Get_RemainCoolTime();
	DWORD dwCool = m_SkillInven[_eID]->Get_Skill()->Get_CoolTime();

	return  (float)dwRemain/ (float)dwCool;
}



void CPlayer::On_Range()
{
	if (m_pTarget == nullptr || m_pTarget->Get_Dead())
		return;
	if (m_pTarget->Get_ID() == OBJ_MONSTER)
	{
		if (m_tDrillFrame.bMotionCancelable == false && false == m_bMotionEnded)
			return;
		m_eCurState = (int)PLAYER_STATE::BATTLE;


		Use_Skill(m_eCurSkill);

	}
	else
	{
		m_pTarget->Interaction(this);
		Make_Stop();
	}
}
void CPlayer::Interaction(CObj* _pObj)
{
}

void CPlayer::On_Move()
{
	m_eCurState = m_bRun ? (int)PLAYER_STATE::RUN : (int)PLAYER_STATE::WALK;
}
void CPlayer::On_Noting()
{
	if (m_bDrillMode)
	{
		if (m_bRenderDrill == false)
		{
			//SOUND_INST->StopSound(CHANNELID::SOUND_DRILL);
			SOUND_INST->PlayLoop(L"etc_drill_sand.wav",1,SOUND_DRILL);
		}

		m_eCurState = (int)PLAYER_STATE::DRILL;
		m_bRenderDrill = true;
	}
	else if (m_eCurState != (int)PLAYER_STATE::HIT)
		m_eCurState = (int)PLAYER_STATE::IDLE;
}
void CPlayer::On_Move_End()
{
	m_eCurState = (int)PLAYER_STATE::IDLE;
}

void CPlayer::Set_Common_Motion(COMMON_STATE _eState)
{
	switch (_eState)
	{
	case COMMON_STATE::IDLE:
		m_eCurState = (int)PLAYER_STATE::IDLE;
		break;
	case COMMON_STATE::MOVE:
		m_eCurState = m_bRun? (int)PLAYER_STATE::RUN : (int)PLAYER_STATE::WALK;
		break;
	case COMMON_STATE::BATTLE:
		m_eCurState = (int)PLAYER_STATE::BATTLE;
		break;
	case COMMON_STATE::BASIC_ATTACK:
		m_eCurState = (int)PLAYER_STATE::NORMAL_ATTACK;
		break;
	case COMMON_STATE::CRITICAL_ATTACK:
		m_eCurState = (int)PLAYER_STATE::CRITICAL_ATTACK;
		break;
	case COMMON_STATE::STRONG_ATTACK:
		m_eCurState = (int)PLAYER_STATE::CHARGE_ATTACK;
		break;
	case COMMON_STATE::HIT:
		m_eCurState = (int)PLAYER_STATE::HIT;
		break;
	case COMMON_STATE::DODGE:
		m_eCurState = (int)PLAYER_STATE::DODGE;
		break;
	case COMMON_STATE::DEAD:
		m_eCurState = (int)PLAYER_STATE::DEAD;
		break;
	case COMMON_STATE::END:
		break;
	default:
		break;
	}
}


void CPlayer::Change_Motion()
{
	CCharacter::Change_Motion();
	switch (m_eCurState)
	{
	case (int)PLAYER_STATE::IDLE:
		m_bRenderArm = true;
		m_bRenderDrill = false;
		m_pArmFrameKey = L"Player_Arm_Idle";
		m_pEarFrameKey = L"Ear_Idle";
		break;
	case (int)PLAYER_STATE::WALK:
		m_bRenderArm = true;
		m_bRenderDrill = false;
		m_pArmFrameKey = L"Player_Arm_Walk";
		m_pEarFrameKey = L"Ear_Walk";
		break;
	case (int)PLAYER_STATE::RUN:
		m_bRenderArm = true;
		m_bRenderDrill = false;
		m_pArmFrameKey = L"Player_Arm_Run";
		m_pEarFrameKey = L"Ear_Run";
		break;
	case (int)PLAYER_STATE::DRILL:
		m_bRenderArm = true;
		m_bRenderDrill = true;
		m_pArmFrameKey = L"Player_Arm_Drill";
		m_pEarFrameKey = L"Ear_Drill";
		break;
	case (int)PLAYER_STATE::CRITICAL_ATTACK :
		m_bRenderArm = false;
		m_bRenderDrill = false;
		m_pEarFrameKey =L"Ear_Critical";
		break;
	case (int)PLAYER_STATE::NORMAL_ATTACK:
		m_bRenderArm = false;
		m_bRenderDrill = false;
		m_pEarFrameKey = L"Ear_Normal";
		break;
	case (int)PLAYER_STATE::DEAD:
	case (int)PLAYER_STATE::DODGE:
	case (int)PLAYER_STATE::HIT:
		m_bRenderArm = false;
		m_bRenderDrill = false;
		m_pEarFrameKey = L"Ear_Hit";
		break;
	case (int)PLAYER_STATE::SNAP_ATTACK:
		m_bRenderArm = false;
		m_bRenderDrill = false;
		m_pEarFrameKey =L"Ear_Snap";
		break;
	case (int)PLAYER_STATE::CHARGE_ATTACK:
		m_bRenderArm = false;
		m_bRenderDrill = false;
		m_pEarFrameKey = L"Ear_Charge";
		break;
	case (int)PLAYER_STATE::BATTLE:
		m_bRenderArm = false;
		m_bRenderDrill = false;
		m_pEarFrameKey = L"Ear_Battle_Idle";
		break;
	default:
		m_bRenderArm = false;
		m_bRenderDrill = false;
		break;
	}

}
void CPlayer::Motion_Func()
{

	if(m_SkillInven[m_eCurSkill]->Get_Skill()->Is_Running())
		m_SkillInven[m_eCurSkill]->Get_Skill()->On_Motion_Func();

}
void CPlayer::On_Motion_End()
{
	switch (m_eCurState)
	{
	
	case (int)PLAYER_STATE::CRITICAL_ATTACK:
	case (int)PLAYER_STATE::NORMAL_ATTACK:
	case (int)PLAYER_STATE::SNAP_ATTACK:
	case (int)PLAYER_STATE::CHARGE_ATTACK:
	case (int)PLAYER_STATE::HIT:
	case (int)PLAYER_STATE::DODGE:
		m_eCurDir = Calc_FDir(m_tDest);
		if (m_pTarget == nullptr || m_pTarget->Get_Dead())
		{
			//m_bAttack = false;
			m_eCurState = (int)PLAYER_STATE::IDLE;
			break;
		}
		m_eCurState = (int)PLAYER_STATE::BATTLE;
		break;
	case (int)PLAYER_STATE::DRILL:
		m_eCurState = (int)PLAYER_STATE::IDLE;
		break;
	default:
		break;
	}
	
	if (m_tStat._iHP <= 0)
	{
		Set_Common_Motion(COMMON_STATE::DEAD);
		return;
	}
	m_SkillInven[m_eCurSkill]->Get_Skill()->On_Motion_End();
	if (m_SkillInven[m_eCurSkill]->Get_Skill()->Is_Coolling() &&
		m_SkillInven[m_eCurSkill]->Get_Skill()->Is_Running() == false)
		Select_Skill(SKILL_ID::BASIC_ATTACK);

}

void CPlayer::On_Hit(CCharacter* _pObj, int _iDamage)
{

	m_eCurState = (int)PLAYER_STATE::HIT;
	m_tStat._iHP -= _iDamage;
	if (m_tStat._iHP <= 0)
	{
		m_eCurState = (int)PLAYER_STATE::DEAD;
		_pObj->Set_Target(nullptr);
		return;
	}
}

void CPlayer::On_Kill(CCharacter* _pObj)
{
	Set_Target(nullptr);
	Make_Stop();
}

void CPlayer::On_Dead(CCharacter* _pObj)
{

}

void CPlayer::Update_Drill_Frame()
{
	if (m_tDrillFrame.dwTime + m_tDrillFrame.dwSpeed < g_dwTime)
	{
		++m_tDrillFrame.iFrameStart;
		if (m_iDrillGaugeVal > m_iDrillIndicatorPos)
			m_iDrillDepth++;
		if (m_tDrillFrame.iFrameStart > m_tDrillFrame.iFrameEnd)
		{
			m_tDrillFrame.iFrameStart = 0;
		}

		m_tDrillFrame.dwTime = g_dwTime;
	}
}

void CPlayer::Update_Drill_Guage()
{
 		
	if (KEY_INST->Key_Pressing(VK_SPACE))
	{
		m_iDrillGaugeVal += 25;
		if (m_iDrillGaugeVal >= m_iDrillGaugeMax)
		{
			m_iDrillGaugeVal = 0;
			m_bDrillMode = false;
			m_bRenderDrill = false;
			m_eCurState = (int)PLAYER_STATE::DODGE;
		}
	}


	m_iDrillGaugeVal -= 10;
	if (m_iDrillGaugeVal <= 0)
		m_iDrillGaugeVal = 0;
	if (m_iDrillDepth > m_iDrillMaxDepth)
	{
		Success_Drill();
	}
 	m_fDrillGuageRatio = (m_iDrillGaugeVal / (float)m_iDrillGaugeMax);
	m_tDrillFrame.dwSpeed = m_dwMinDrillAnimSpeed + (m_dwMaxDrillAnimSpeed - m_dwMinDrillAnimSpeed) * (1-m_fDrillGuageRatio);
}

void CPlayer::RenderDrill(HDC hdc)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//드릴
	GdiTransparentBlt(hdc,
		m_tRenderRect.left + iScrollX,
		m_tRenderRect.top + iScrollY,
		(int)m_tInfo.fRX,
		(int)m_tInfo.fRY,
		m_hDrillDC,
		(int)m_tInfo.fRX * m_tDrillFrame.iFrameStart,
		0,
		(int)m_tInfo.fRX,
		(int)m_tInfo.fRY,
		MAGENTA);
	//드릴 UI
	GdiTransparentBlt(hdc,
		m_tCollisionRect.left - m_iDrillUIX/2 + iScrollX,
		m_tCollisionRect.top - 10 + iScrollY,
		m_iDrillUIX,
		m_iDrillUIY,
		m_hDrillUIDC,
		m_iDrillUIX * m_tDrillFrame.iFrameStart,
		0,
		m_iDrillUIX,
		m_iDrillUIY,
		MAGENTA);
	//드릴 게이지
	GdiTransparentBlt(hdc,
		m_tCollisionRect.left - m_iDrillUIX / 2 + iScrollX + 32,
		m_tCollisionRect.top - 10 + iScrollY + 50,
		m_iDriilGuageWidth * (m_iDrillGaugeVal/(float)m_iDrillGaugeMax),
		m_iDrillFillUIY,
		m_hDrillGuageFillDC,
		0,
		0,
		m_iDrillFillUIX,
		m_iDrillFillUIY,
		MAGENTA);
	//드릴 게이지 표시
	GdiTransparentBlt(hdc,
		m_tCollisionRect.left - m_iDrillUIX / 2 + iScrollX + 32 -4 +(114 * (m_iDrillIndicatorPos / (float)m_iDrillGaugeMax)),
		m_tCollisionRect.top - 10 + iScrollY + 40,
		9,
		16,
		m_hDrillIndicatorDC,
		0,
		0,
		9,
		16,
		MAGENTA);
	wstring str = to_wstring(m_iDrillDepth);
	TextOut(hdc, m_tCollisionRect.left - m_iDrillUIX / 2 + iScrollX + 20, m_tCollisionRect.top - 10 + iScrollY + 3, str.c_str(),str.length());
}

void CPlayer::End_Drill()
{
	m_iDrillDepth = 0;
	m_iDrillGaugeVal = 0;
	m_bDrillMode = false;
	m_bRenderDrill = false;
	SOUND_INST->StopSound(SOUND_DRILL);
}

void CPlayer::Success_Drill()
{
	End_Drill();
	ITEM_ID eId =  DROP_INST->Get_Digging_Item();
	if (eId != ITEM_ID::END)
		DROP_INST->Drop_Item(eId, Get_Point());
}
