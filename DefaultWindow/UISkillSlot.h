#pragma once
#include "UISlot.h"
#include "SkillSlot.h"

class CUISkillSlot :
    public CUISlot
{
public:
    CUISkillSlot() { m_eSlotType = SLOT_TYPE::SKILL; }
    CUISkillSlot(POINT _pt);
    void Late_Update() override;
    void Release() override;
    void Render(HDC hdc)override;
    int Get_IconOffset() override;
    //void Set_SkillSLot(CSkillSlot* _pSkill) { m_pSlot = _pSkill; }
    SKILL_ID Get_SKILL_ID() { return ((CSkillSlot*)m_pCurSlot)->Get_Skill_ID(); }
    void Operate() override;

    CUI* On_Drop(CUI* _pt) override;
private:
    //CSkillSlot* m_pSlot = nullptr;
};

