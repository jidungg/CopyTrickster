#include "stdafx.h"
#include "Skill.h"
#include "Character.h"

CSkill::CSkill()
	:m_dwCoolTime(0) , m_dwUsedTime(0)
{
}


CSkill::~CSkill()
{
}

void CSkill::Initialize()
{
}

void CSkill::Update()
{
	
}

void CSkill::Late_Update()
{
}

void CSkill::Render(HDC hdc)
{
}

void CSkill::Release()
{
}

bool CSkill::Is_Coolling()
{
	return (m_dwUsedTime + m_dwCoolTime) > g_dwTime;
}

DWORD CSkill::Get_RemainCoolTime()
{
;
	if (((int)m_dwUsedTime + (int)m_dwCoolTime - (int)g_dwTime) > m_dwCoolTime)
		return 0;
	else
		return m_dwUsedTime + m_dwCoolTime - g_dwTime;
}

void CSkill::Use(CCharacter* _pObj, CCharacter* _pSbj)
{
	if (false == Is_Coolling() && Has_Enough_Mana(_pObj))
	{
		m_pObj = _pObj;
		m_pSbj = _pSbj;
		Func(_pObj, _pSbj);

		m_dwUsedTime = g_dwTime;
		m_bRunning = true;
		_pObj->Consume_Mana(m_iConsumptionValue);
	}
}

void CSkill::On_Motion_Func()
{
	Motion_Func();
}

void CSkill::On_Motion_End()
{
	Motion_End();
	m_pSbj = nullptr;
	m_pObj = nullptr;
	m_bRunning = false;
}

bool CSkill::Has_Enough_Mana(CCharacter* _pObj)
{
	return _pObj->Get_Stat()._iMP >= m_iConsumptionValue;
}

