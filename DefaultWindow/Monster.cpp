#include "stdafx.h"
#include "Monster.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "EventMgr.h"
#include "TileMgr.h"
#include "MonsterSpawner.h"
#include "BasicAttack.h"
#include "SkillSlot.h"

CMonster::CMonster()
{
}

CMonster::~CMonster()
{
	Release();
}

void CMonster::Initialize()
{
	m_dwLastAttackTime = g_dwTime;
	m_ePreState = (int)MONSTER_STATE::ST_END;
	m_eCurState = (int)MONSTER_STATE::IDLE;
	m_eCurDir = DIR_LD;
	m_eRender = RENDER_GAMEOBJECT;
	m_eObjID = OBJ_MONSTER; 
	m_dwRandomDestDelay = rand() % 6000 + 2000;
	m_SkillInven.insert({ SKILL_ID::BASIC_ATTACK, new CSkillSlot(SKILL_ID::BASIC_ATTACK, new CBasicAttack(m_tStat._dwAttackDelay,m_tStat._fAttackRange)) });
	//m_SkillInven.insert({ SKILL_ID::BASIC_ATTACK, new CBasicAttack(m_tStat._dwAttackDelay,m_tStat._fAttackRange) });
}

int CMonster::Update()
{
	if (m_eCurState != (int)MONSTER_STATE::DEAD)
	{
		if ((m_dwRandomDestTime + m_dwRandomDestDelay) < g_dwTime)
		{
			Set_Random_Dest();
			m_dwRandomDestTime = g_dwTime;
		}
		return __super::Update();

	}
	return m_bDead ? OBJ_DEAD : OBJ_NOEVENT;
}

void CMonster::Late_Update()
{
	Change_Motion();

	__super::Move_Frame();
}




void CMonster::Release()
{
}
void CMonster::Interaction(CObj* _pObj)
{
}



void CMonster::On_Range()
{
	if (m_tFrame.bMotionCancelable == false && false == m_bMotionEnded)
		return;
	m_eCurDir = Calc_FDir(m_pTarget->Get_Point());
	Use_Skill(m_eCurSkill);
	
}
void CMonster::Set_Common_Motion(COMMON_STATE _eState)
{
	switch (_eState)
	{
	case COMMON_STATE::IDLE:
	case COMMON_STATE::BATTLE:
	case COMMON_STATE::DODGE:
	case COMMON_STATE::DRILL:
		m_eCurState = (int)MONSTER_STATE::IDLE;
		break;
	case COMMON_STATE::MOVE:
		m_eCurState = (int)MONSTER_STATE::WALK;
		break;
	case COMMON_STATE::CRITICAL_ATTACK:
	case COMMON_STATE::BASIC_ATTACK:
	case COMMON_STATE::STRONG_ATTACK:
		m_eCurState = (int)MONSTER_STATE::ATTACK;
		break;
	case COMMON_STATE::HIT:
		m_eCurState = (int)MONSTER_STATE::HIT;
		break;
	case COMMON_STATE::DEAD:
		m_eCurState = (int)MONSTER_STATE::DEAD;
		break;
	case COMMON_STATE::END:
		break;
	default:
		break;
	}
}
void CMonster::Set_Data(CHARACTER_DATA* _tData)
{
	CCharacter::Set_Data(_tData);
	m_eMonID = (MONSTER_ID)_tData->m_eID;
}
void CMonster::Motion_Func()
{
	m_SkillInven[m_eCurSkill]->Get_Skill()->On_Motion_Func();
}
void CMonster::Set_Random_Dest()
{

	int iRX = rand() % 300 - 150;
	int iRY = rand() % 300 - 150;
	Set_Dest({ m_tDest.x + iRX, m_tDest.y  + iRY});
}
void CMonster::On_Motion_End()
{
	switch ((MONSTER_STATE)m_eCurState)
	{
	case MONSTER_STATE::ATTACK:
	case MONSTER_STATE::HIT:
		m_eCurState = (int)MONSTER_STATE::IDLE;
		break;
	case MONSTER_STATE::DEAD:
		EVENT_INST->Push_Event(new CDeadEvent((CCharacter*)m_pTarget, this ));
		return;
	default:
		break;
	}
	if (m_tStat._iHP <= 0)
	{
		Set_Common_Motion(COMMON_STATE::DEAD);
		return;
	}
	m_SkillInven[m_eCurSkill]->Get_Skill()->On_Motion_End();
}
void CMonster::On_Hit(CCharacter* _pObj, int _iDamage)
{
	if(m_eCurState == (int)MONSTER_STATE::IDLE)
		m_eCurState = (int)MONSTER_STATE::HIT;
	if (m_pTarget == nullptr || m_pTarget->Get_Dead())
		m_pTarget = _pObj;
	m_tStat._iHP -= _iDamage;
	if (m_tStat._iHP <= 0)
	{
		m_eCurState = (int)MONSTER_STATE::DEAD;
		return;
	}
}

void CMonster::On_Kill(CCharacter* _pObj)
{
	m_pTarget = nullptr;
	Make_Stop();
}

void CMonster::On_Dead(CCharacter* _pObj)
{
	__super::On_Dead(_pObj);
	if(m_pSpawner)
		m_pSpawner->ResetTime();
}

void CMonster::On_Move()
{
}

void CMonster::On_Move_End()
{

	m_eCurState = (int)MONSTER_STATE::IDLE;
}
void CMonster::On_Noting()
{
	m_eCurState = (int)MONSTER_STATE::IDLE;
}


