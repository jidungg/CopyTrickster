#include "stdafx.h"
#include "Dragon.h"
#include "MonsterSpawner.h"
#include "EventMgr.h"
#include "EffectMgr.h"
#include "UnarmoredDragon.h"
#include "ObjMgr.h"
#include "CharacterDataBase.h"
#include "SkillSlot.h"

CDragon::CDragon()
{
}

CDragon::~CDragon()
{
}

void CDragon::On_Move()
{
	//m_eCurState = (int)DRAGON_STATE::WALK;
}

void CDragon::On_Noting()
{
	//m_eCurState = (int)DRAGON_STATE::IDLE;
}

void CDragon::On_Move_End()
{

	//m_eCurState = (int)DRAGON_STATE::IDLE;
}

void CDragon::On_Hit(CCharacter* _pObj, int _iDamage)
{
	m_tStat._iHP -= _iDamage;
	if (m_tStat._iHP <= 0)
	{
		m_eCurState = (int)DRAGON_STATE::BREAK;
		return;
	}
	if (m_pTarget == nullptr || m_pTarget->Get_Dead())
		m_pTarget = _pObj;
}

void CDragon::On_Kill(CCharacter* _pObj)
{
	m_pTarget = nullptr;
	Make_Stop();
}

void CDragon::On_Dead(CCharacter* _pObj)
{
	__super::On_Dead(_pObj);
	if(m_pSpawner)
		m_pSpawner->ResetTime();
}


void CDragon::Motion_Func()
{
	m_SkillInven[m_eCurSkill]->Get_Skill()->On_Motion_Func();
}

void CDragon::On_Motion_End()
{
	switch ((DRAGON_STATE)m_eCurState)
	{
	case DRAGON_STATE::ATTACK:
		m_eCurState = (int)DRAGON_STATE::IDLE;
		break;
	case DRAGON_STATE::BREAK:
	{
		EVENT_INST->Push_Event(new CDeadEvent((CCharacter*)m_pTarget, this));
		CUnarmoredDragon* pUnArmDragon = new CUnarmoredDragon();
		pUnArmDragon->Set_Data(CHARDB_INST->Get_Monster_Data(MONSTER_ID::UNARMORED_DRAGON));
		pUnArmDragon->Make_Stop();
		pUnArmDragon->Initialize();
		pUnArmDragon->Set_Pos(m_tInfo.fX, m_tInfo.fY);
		OBJ_INST->Add_Object(OBJ_MONSTER, pUnArmDragon);
	}
		return;
	default:
		break;
	}
	if (m_tStat._iHP <= 0)
	{
		m_eCurState = (int)DRAGON_STATE::BREAK;
		return;
	}
	m_SkillInven[m_eCurSkill]->Get_Skill()->On_Motion_End();
}
void CDragon::Set_Common_Motion(COMMON_STATE _eState)
{
	switch (_eState)
	{
	case COMMON_STATE::IDLE:
	case COMMON_STATE::BATTLE:
		m_eCurState = (int)DRAGON_STATE::IDLE;
		break;
	case COMMON_STATE::MOVE:
		m_eCurState = (int)DRAGON_STATE::WALK;
		break;
	case COMMON_STATE::BASIC_ATTACK:
	case COMMON_STATE::CRITICAL_ATTACK:
	case COMMON_STATE::STRONG_ATTACK:
		m_eCurState = (int)DRAGON_STATE::ATTACK;
		break;
	case COMMON_STATE::HIT:
	case COMMON_STATE::DODGE:
		m_eCurState = (int)DRAGON_STATE::IDLE;
		break;
	case COMMON_STATE::DEAD:
		m_eCurState = (int)DRAGON_STATE::BREAK;
		break;
	case COMMON_STATE::END:
		break;
	default:
		break;
	}
}

void CDragon::Interaction(CObj* _pObj)
{
}

