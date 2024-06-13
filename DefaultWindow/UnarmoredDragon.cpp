#include "stdafx.h"
#include "UnarmoredDragon.h"
#include "BasicAttack.h"
#include "ObjMgr.h"
#include "SkillCrossBomb.h"
#include "LavaEruption.h"
#include "TileMgr.h"
#include "Portal.h"
#include "AbstractFactory.h"
#include "SkillSlot.h"

void CUnarmoredDragon::Set_Common_Motion(COMMON_STATE _eState)
{
	switch (_eState)
	{
	case COMMON_STATE::IDLE:
	case COMMON_STATE::BATTLE:
	case COMMON_STATE::DODGE:
	case COMMON_STATE::DRILL:
		m_eCurState = (int)UNARMORED_DRAGON_STATE::IDLE;
		break;
	case COMMON_STATE::MOVE:
		m_eCurState =(int)UNARMORED_DRAGON_STATE::WALK;
		break;
	case COMMON_STATE::CRITICAL_ATTACK:
	case COMMON_STATE::BASIC_ATTACK:
	case COMMON_STATE::STRONG_ATTACK:
		m_eCurState = (int)UNARMORED_DRAGON_STATE::ATTACK;
		break;
	case COMMON_STATE::HIT:
		m_eCurState = (int)UNARMORED_DRAGON_STATE::IDLE;
		break;
	case COMMON_STATE::DEAD:
		m_eCurState = (int)UNARMORED_DRAGON_STATE::DEAD;
		break;
	case COMMON_STATE::END:
		break;
	default:
		break;
	}
}

void CUnarmoredDragon::Select_Skill()
{
	int iMaxCooltime = 0;
	SKILL_ID eSkId = SKILL_ID::BASIC_ATTACK;
	for (auto& i : m_SkillInven)
	{
		if (i.first == SKILL_ID::BASIC_ATTACK)
			continue;
		if (i.second->Get_Skill()->Is_Coolling())
			continue;
		if (i.second->Get_Skill()->Get_CoolTime() > iMaxCooltime)
		{
			eSkId = i.first;
			iMaxCooltime = i.second->Get_Skill()->Get_CoolTime();
		}
	}
	CCharacter::Select_Skill(eSkId) ;
}
void CUnarmoredDragon::Interaction(CObj* _pObj)
{
}





void CUnarmoredDragon::Initialize()
{
	m_dwLastAttackTime = g_dwTime;
	m_ePreState = (int)MONSTER_STATE::ST_END;
	m_eCurState = (int)MONSTER_STATE::IDLE;
	m_eCurDir = DIR_LD;
	m_eRender = RENDER_GAMEOBJECT;
	m_eObjID = OBJ_MONSTER;
	m_dwRandomDestDelay = rand() % 6000 + 2000;
	m_SkillInven.insert({ SKILL_ID::BASIC_ATTACK,new CSkillSlot(SKILL_ID::BASIC_ATTACK, new CBasicAttack(m_tStat._dwAttackDelay,m_tStat._fAttackRange)) });
	m_SkillInven.insert({ SKILL_ID::CROSS_BOMB, new CSkillSlot(SKILL_ID::CROSS_BOMB,new CSkillCrossBomb()) });
	m_SkillInven.insert({ SKILL_ID::LAVA_ERUPTION,new CSkillSlot(SKILL_ID::LAVA_ERUPTION, new CLavaEruption()) });
	m_pTarget = OBJ_INST->Get_Player();
}

void CUnarmoredDragon::On_Range()
{

	Select_Skill();
	Use_Skill(m_eCurSkill);


}

void CUnarmoredDragon::On_Move()
{
}

void CUnarmoredDragon::On_Noting()
{
}

void CUnarmoredDragon::On_Move_End()
{
	m_eCurState = (int)UNARMORED_DRAGON_STATE::IDLE;
}
void CUnarmoredDragon::On_Motion_End()
{
	switch ((UNARMORED_DRAGON_STATE)m_eCurState)
	{
	case UNARMORED_DRAGON_STATE::ATTACK:
		break;
	case UNARMORED_DRAGON_STATE::DEAD:
	{
		EVENT_INST->Push_Event(new CDeadEvent((CCharacter*)m_pTarget, this));
		CPortal* pPortal = (CPortal*)CAbstractFactory<CPortal>::Create(this->Get_Point());
		pPortal->Set_Scene(SCENE_ID::RYTHM);
		OBJ_INST->Add_Object(OBJ_ID::OBJ_PORTAL, pPortal);
	}
		break;
	default:
		break;
	}

	m_SkillInven[m_eCurSkill]->Get_Skill()->On_Motion_End();
}




void CUnarmoredDragon::On_Hit(CCharacter* _pObj, int _iDamage)
{
	if (m_pTarget == nullptr || m_pTarget->Get_Dead())
		m_pTarget = _pObj;
	m_tStat._iHP -= _iDamage;

}

void CUnarmoredDragon::On_Kill(CCharacter* _pObj)
{
}

void CUnarmoredDragon::On_Dead(CCharacter* _pObj)
{
	Set_Dead();
}
