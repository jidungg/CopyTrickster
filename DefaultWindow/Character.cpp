#include "stdafx.h"
#include "Character.h"
#include "TileMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "SkillInventory.h"
#include "SkillSlot.h"

CCharacter::CCharacter()
{

}

CCharacter::~CCharacter()
{
}

int CCharacter::Update()
{
	if (m_tStat._iHP <= 0)
	{
		Set_Common_Motion(COMMON_STATE::DEAD);

		return m_bDead ? OBJ_DEAD : OBJ_NOEVENT;
	}
	//현재 스킬 실행중
	if (m_SkillInven[m_eCurSkill]->Get_Skill()->Is_Running())
	{
		m_bPrevSkillRunning = true;
		m_SkillInven[m_eCurSkill]->Get_Skill()->Update();
		__super::Update_Rect();
		return m_bDead ? OBJ_DEAD : OBJ_NOEVENT;
	}
	//현재 스킬 안실행중인데 이전에 실행중이었음(지금 막 끝나)
	else if(m_bPrevSkillRunning)
	{
		Set_Common_Motion(COMMON_STATE::IDLE);
		m_bPrevSkillRunning = false;
	}
	//현재 스킬 안실행중이고 이전에도 실행중이지 않았음(대기상태)
	else
	{
		m_bPrevSkillRunning = false;
	}

	//타겟이 있을 떄
	if (m_pTarget != nullptr && m_pTarget->Get_Dead() == false)
	{
		m_tDest = m_pTarget->Get_Point();
		float fRange = m_fRange;
		if (m_pTarget->Get_ID() == OBJ_MONSTER)
			fRange = Get_CurRange();
		//타겟이 공격 범위 내에 있을 떄
		if (Is_In_Range(m_pTarget->Get_Info(), fRange))
		{
			On_Range();

		}
		//타겟이 공격 범위 밖에 있을 때
		else
		{
			//이동
			Update_Move(m_pTarget->Get_Point());
		}
	}
	//타겟은 없지만 m_tDest까지의 거리가 멀 때.(이동해야 할 때)
	else if (Is_In_Range(m_tDest, m_tStat._fSpeed) == false)
	{
		//이동
		m_pTarget = nullptr;
		

		Update_Move(m_tDest);
	}
	//타겟도 없고, 이동도 안할 떄
	else
	{
		m_pTarget = nullptr;
		On_Noting();
	}
	__super::Update_Rect();

	return m_bDead ? OBJ_DEAD : OBJ_NOEVENT;
}


void CCharacter::Update_Move(POINT _pt)
{
	Set_Common_Motion(COMMON_STATE::MOVE);
	On_Move();
	Fit_Direction(_pt);

	float fXSpd = Get_X_Speed();
	float fYSpd = Get_Y_Speed();

	INFO tInfo = m_tInfo;
	tInfo.fX += fXSpd;
	tInfo.fY += fYSpd;

	if (TILE_INST->Collision_Block_Tile(tInfo)
		|| m_tDest.x <= 0 || m_tDest.y <= 0
		|| m_tDest.x >= TILE_INST->Get_MAP_Width()
		|| m_tDest.y >= TILE_INST->Get_MAP_Height())
	{
		m_tDest = { (int)m_tInfo.fX, (int)m_tInfo.fY };
		//m_bMove = false;
		On_Move_End();
	}
	else if (false == m_tFrame.bMotionCancelable && false == m_bMotionEnded)
	{

	}
	else
	{
 		m_tInfo.fX += fXSpd;
		m_tInfo.fY += fYSpd;
	}
}



void CCharacter::On_Hit(CCharacter* _pObj, int _iDamage)
{

}

void CCharacter::On_Kill(CCharacter* _pObj)
{
}

void CCharacter::On_Dead(CCharacter* _pObj)
{
	Set_Dead();
}

void CCharacter::Make_Stop()
{
	m_tDest = { (int)m_tInfo.fX,(int)m_tInfo.fY };
	m_pTarget = nullptr;
}

//bCancelable이면 중간에 바뀔 수 없음.
void CCharacter::Change_Motion()
{
	//상태가 바뀌었는지.
	if ((m_ePreState != m_eCurState) || (m_eCurDir != m_ePrevDir))
	{

		//캔슬 불가능한 모션인지
		if (false == m_tFrame.bMotionCancelable )
		{
			//모션이 안끝났는지
			if (false == m_bMotionEnded)
			{
				m_eCurState = m_ePreState;
				return;
			}
		}
		//if (false == m_SkillInven[m_eCurSkill]->Is_Running())
		//	return;
		m_tFrame = (*m_vecAnimData)[m_eCurState].second;

		m_bMotionEnded = false;
		switch ((*m_vecAnimData)[m_eCurState].first)
		{
		case ANIM_TYPE::EIGHT_DIR:
			m_tFrame.iMotion += m_eCurDir;
			break;
		case ANIM_TYPE::FOUR_DIR:
			m_tFrame.iMotion += FDir_To_Motion_Idx(EDir_To_FDir(m_eCurDir));
			break;
		case ANIM_TYPE::TWO_DIR:
			m_tFrame.iMotion += TDir_To_Motion_Idx(EDir_To_TDir(m_eCurDir));
			break;
		case ANIM_TYPE::ONE_DIR:
		default:
			break;
		}

		m_tFrame.dwTime = g_dwTime;
		m_ePreState = m_eCurState;
		m_ePrevDir = m_eCurDir;
	}
}

void CCharacter::Set_Data(CHARACTER_DATA* _tData)
{
	m_tStat = _tData->tStat;
	m_tInfo = _tData->tInfo;
	m_vecAnimData = _tData->vecAnimData;
	m_iRenderOffsetX = _tData->iRenderOffsetX;
	m_iRenderOffsetY = _tData->iRenderOffsetY;
	m_fRange = m_tInfo.fCX;
	m_pName = _tData->pName;
}


void CCharacter::Set_Dest(POINT _tP)
{
	m_tDest = _tP;
	
}

void CCharacter::Select_Skill(SKILL_ID _eSkill)
{
	if (m_eCurSkill != _eSkill)
	{
		m_SkillInven[_eSkill]->Get_Skill()->StopRunning();
		m_eCurSkill = _eSkill; 
	}
}

float CCharacter::Get_CurRange()
{
	return m_SkillInven[m_eCurSkill]->Get_Skill()->Get_Range();
}

bool CCharacter::TryCritical()
{
	int iRand = rand() % 1000;
	return (iRand <= m_tStat._iCritChance);

}


float CCharacter::Get_X_Speed()
{
	float fXSpd = 0.f;

	switch (m_eCurDir)
	{
	case DIR_UP:
		fXSpd = 0.f;
		break;
	case DIR_LU:
		fXSpd = m_tStat._fSpeed * cosf(-135.f * PI / 180);
		break;
	case DIR_LEFT:
		fXSpd = -m_tStat._fSpeed;
		break;
	case DIR_LD:
		fXSpd = m_tStat._fSpeed * cosf(135.f * PI / 180);
		break;
	case DIR_DOWN:
		fXSpd = 0.f;
		break;
	case DIR_RD:
		fXSpd = m_tStat._fSpeed * cosf(45.f * PI / 180);
		break;
	case DIR_RIGHT:
		fXSpd = +m_tStat._fSpeed;
		break;
	case DIR_RU:
		fXSpd = m_tStat._fSpeed * cosf(-45.f * PI / 180);
		break;
	case DIR_END:
		break;
	default:
		break;
	}
	return fXSpd;
}

float CCharacter::Get_Y_Speed()
{
	float fYSpd = 0.f;

	switch (m_eCurDir)
	{
	case DIR_UP:
		fYSpd = -m_tStat._fSpeed;
		break;
	case DIR_LU:
		fYSpd = m_tStat._fSpeed * sinf(-135.f * PI / 180);
		break;
	case DIR_LEFT:
		fYSpd = 0;
		break;
	case DIR_LD:
		fYSpd = m_tStat._fSpeed * sinf(135.f * PI / 180);
		break;
	case DIR_DOWN:
		fYSpd = m_tStat._fSpeed;
		break;
	case DIR_RD:
		fYSpd = m_tStat._fSpeed * sinf(45.f * PI / 180);
		break;
	case DIR_RIGHT:
		fYSpd = 0;
		break;
	case DIR_RU:
		fYSpd = m_tStat._fSpeed * sinf(-45.f * PI / 180);
		break;
	case DIR_END:
		break;
	default:
		break;
	}
	return fYSpd;
}



void CCharacter::Fit_Direction(POINT _tp)
{
	float fDestRad = Calc_Radius(_tp);
	float fRadDiff = abs(fDestRad - Get_Current_Radius());
	if (fRadDiff > (PI / 4))
		m_eCurDir = Calc_Dir(fDestRad);
}

bool CCharacter::Is_In_Range(POINT _pt, float _iRange)
{
	POINT p = _pt;
	float fDX = p.x - m_tInfo.fX;
	float fDY = p.y - m_tInfo.fY;
	float fDist = sqrtf(fDX * fDX + fDY * fDY);
	
	return fDist < _iRange;
}

bool CCharacter::Is_In_Range(INFO _tInfo, float _iRange)
{
	POINT p = { _tInfo.fX, _tInfo.fY};
	float fDX = p.x - m_tInfo.fX;
	float fDY = p.y - m_tInfo.fY;
	float fDist = sqrtf(fDX * fDX + fDY * fDY);

	return fDist < (_iRange+ _tInfo.fCX);
}


void CCharacter::Use_Skill(SKILL_ID _eID)
{
	if (m_SkillInven.find(_eID) == m_SkillInven.end())
		return;

	m_SkillInven[_eID]->Get_Skill()->Use(this,(CCharacter*)m_pTarget); 
}

void CCharacter::Consume_Mana(int _iVal)
{
	m_tStat._iMP -= _iVal;
}

void CCharacter::Recover_HP(int _iVal)
{
	m_tStat._iHP += _iVal; if (m_tStat._iHP > m_tStat._iMaxHP) m_tStat._iHP = m_tStat._iMaxHP;
}

void CCharacter::Recover_MP(int _iVal)
{
	m_tStat._iMP += _iVal; if (m_tStat._iMP > m_tStat._iMaxMP) m_tStat._iMP = m_tStat._iMaxMP;
}

void CCharacter::AddStat(STAT _tStat)
{
	m_tStat._dwAttackDelay -= _tStat._dwAttackDelay;
	m_tStat._fAttackRange += _tStat._fAttackRange;
	m_tStat._fCritMultiplier += _tStat._fCritMultiplier;
	m_tStat._fSpeed += _tStat._fSpeed;
	m_tStat._iAttak += _tStat._iAttak;
	m_tStat._iCritChance += _tStat._iCritChance;
	m_tStat._iDefense += _tStat._iDefense;
	m_tStat._iDodgeChance += _tStat._iDodgeChance;
	m_tStat._iHP += _tStat._iHP;
	m_tStat._iMP += _tStat._iMP;
	m_tStat._iMaxHP += _tStat._iMaxHP;
	m_tStat._iMaxMP += _tStat._iMaxMP;
	m_tStat._iMagicAttack += _tStat._iMagicAttack;
}

void CCharacter::SubStat(STAT _tStat)
{
	m_tStat._dwAttackDelay += _tStat._dwAttackDelay;
	m_tStat._fAttackRange -= _tStat._fAttackRange;
	m_tStat._fCritMultiplier -= _tStat._fCritMultiplier;
	m_tStat._fSpeed -= _tStat._fSpeed;
	m_tStat._iAttak -= _tStat._iAttak;
	m_tStat._iCritChance -= _tStat._iCritChance;
	m_tStat._iDefense -= _tStat._iDefense;
	m_tStat._iDodgeChance -= _tStat._iDodgeChance;
	m_tStat._iHP -= _tStat._iHP;
	m_tStat._iMP -= _tStat._iMP;
	m_tStat._iMaxHP -= _tStat._iMaxHP;
	m_tStat._iMaxMP -= _tStat._iMaxMP;
	m_tStat._iMagicAttack -= _tStat._iMagicAttack;
}
