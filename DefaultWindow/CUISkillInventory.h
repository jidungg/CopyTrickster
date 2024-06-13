#pragma once
#include "Window.h"
#include "UISkillSlot.h"

class CSkill;
class CUISkillInventory :
    public CWindow
{
public:
    CUISkillInventory(int _iXPos, int _iYPos, int _iXSize, int _iYSize, HDC hActive, HDC hDeactive, HDC hMinActive, HDC hMinDeactive);
    
    void Set_Skill_Inven(map<SKILL_ID, CSkillSlot*>* _pInven) { m_pSkillInven = _pInven; }
private:
    int m_iFirstIconX = 18;
    int m_iFirstIconY = 94;
    int m_iGap = 38;
    map<SKILL_ID, CSkillSlot*>* m_pSkillInven;
    vector<CUISkillSlot> m_vecSlots;
};

