#pragma once
#include "Skill.h"
#include "Obj.h"

#include <unordered_map>
class CSkillInventory
{
public:
	CSkillInventory();
	~CSkillInventory();

	void Initialize();
	void Update();
	void Release();

	void Use_Skill(SKILL_ID _eID, CCharacter* _pObj, CCharacter* _pSbj);

private:
	unordered_map<SKILL_ID, CSkill*> m_Skills;
};

