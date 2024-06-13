#include "stdafx.h"
#include "SkillInventory.h"
#include "Obj.h"


CSkillInventory::CSkillInventory()
{
}

CSkillInventory::~CSkillInventory()
{
	Release();
}

void CSkillInventory::Initialize()
{

}

void CSkillInventory::Update()
{
	for (auto& i : m_Skills)
	{
		i.second->Update();
	}
}

void CSkillInventory::Release()
{
}

void CSkillInventory::Use_Skill(SKILL_ID _eID, CCharacter* _pObj, CCharacter* _pSbj)
{
	auto skill = m_Skills.find(_eID);
	if ( skill == m_Skills.end())
		return;

	skill->second->Use(_pObj, _pSbj);
}
