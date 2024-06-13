#pragma once
#include "CItemMgr.h"
class CSkill;
class CSkillSlot :
	public CItemSlot
{
public:
	CSkillSlot(SKILL_ID _eID, CSkill* _pSkill);
	~CSkillSlot() { Release(); }

	void Release();
	SKILL_ID Get_Skill_ID() { return m_eSkillID; }
	void Set_Skill(CSkill* _pSkill) { m_pSkill = _pSkill; }
	CSkill* Get_Skill() { return m_pSkill; }
	int Get_IconOffset() { return (int)m_eSkillID; }
	virtual void Operate() override;
private:
	SKILL_ID m_eSkillID = SKILL_ID::END;
	CSkill* m_pSkill = nullptr;
};
