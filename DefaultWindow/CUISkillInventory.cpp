#include "stdafx.h"
#include "CUISkillInventory.h"
#include "ObjMgr.h"
#include "Character.h"

CUISkillInventory::CUISkillInventory(int _iXPos, int _iYPos, int _iXSize, int _iYSize, HDC hActive, HDC hDeactive, HDC hMinActive, HDC hMinDeactive)
	:CWindow(WINDOW_ID::SKILL, _iXPos, _iYPos, _iXSize, _iYSize, hActive, hDeactive, hMinActive, hMinDeactive)
{
	m_pSkillInven = static_cast<CCharacter*>( OBJ_INST->Get_Player())->Get_Skill_Inven();

	m_vecSlots.resize(21);
	for (int i = 0; i < 3; i++)
	{ 
		for (int j = 0; j < 7; j++)
		{
			m_vecSlots[i*7 + j].Initialize();
			m_vecSlots[i*7 + j].Set_IconDC(BMP_INST->Find_Img(L"UI_Icon_Skill"));
			m_vecSlots[i*7 + j].Set_Parent(this);
			m_vecSlots[i*7 + j].Set_Position({m_iFirstIconX +m_iGap*j, m_iFirstIconY + m_iGap*i});
			m_vecSlots[i*7 + j].Set_XSize(SKILL_SLOT_CX);
			m_vecSlots[i*7 + j].Set_YSize(SKILL_SLOT_CY);
			m_vecSlots[i * 7 + j].Set_Slot(nullptr);
			m_vecComponents.push_back(&m_vecSlots[i * j + j]);
		}
	}
	int iIdx = 0;
	for (auto& i : *m_pSkillInven)
	{
		m_vecSlots[iIdx++].Set_Slot(i.second);

	}
}
