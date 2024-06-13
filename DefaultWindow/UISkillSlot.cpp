#include "stdafx.h"
#include "UISkillSlot.h"
#include "ObjMgr.h"
#include "Player.h"

CUISkillSlot::CUISkillSlot(POINT _pt)
{
	m_eSlotType = SLOT_TYPE::SKILL;
}

void CUISkillSlot::Render(HDC hdc)
{
	if (m_pCurSlot == nullptr)
		return;
	//Rectangle(hdc, m_tDraw.x, m_tDraw.y, m_tDraw.x + SKILL_SLOT_CX, m_tDraw.y + SKILL_SLOT_CY);
	if (Get_SKILL_ID() == SKILL_ID::END)
		return;
	GdiTransparentBlt(hdc, m_tDraw.x, m_tDraw.y, SKILL_SLOT_CX, SKILL_SLOT_CY,
		m_hIconDC, SKILL_SLOT_CX * (int)Get_SKILL_ID(), 0, SKILL_SLOT_CY, SKILL_SLOT_CY,
		MAGENTA);
}

CUI* CUISkillSlot::On_Drop(CUI* _pt)
{
	m_bDrag = false;
	return nullptr;
}

void CUISkillSlot::Operate()
{
	((CPlayer*)OBJ_INST->Get_Player())->Select_Skill(((CSkillSlot*)m_pCurSlot)->Get_Skill_ID());
}

int CUISkillSlot::Get_IconOffset()
{
	return (int)((CSkillSlot*)m_pCurSlot)->Get_Skill_ID();
}

void CUISkillSlot::Late_Update()
{
}

void CUISkillSlot::Release()
{
}
