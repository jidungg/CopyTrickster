#include "stdafx.h"
#include "SkillSlot.h"
#include "ObjMgr.h"
#include "Player.h"
#include "BasicAttack.h"
#include "EnergyPunch.h"
#include "Skill.h"

void CSkillSlot::Release()
{
	Safe_Delete( m_pSkill);
}

void CSkillSlot::Operate()
{
	((CPlayer*)OBJ_INST->Get_Player())->Select_Skill(Get_Skill_ID());
}

CSkillSlot::CSkillSlot(SKILL_ID _eID, CSkill* _pSkill)
{
	m_eSkillID = _eID;
	m_eSlotType = SLOT_TYPE::SKILL;
	m_pSkill = _pSkill;
}
