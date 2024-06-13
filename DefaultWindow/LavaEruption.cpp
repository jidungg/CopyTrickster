#include "stdafx.h"
#include "LavaEruption.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "Lava.h"
#include "Character.h"

CLavaEruption::CLavaEruption()
{
	m_dwCoolTime = 60000;
	m_fRange = 10000000;
}

void CLavaEruption::Func(CCharacter* _pObj, CCharacter* _pSbj)
{

	(_pObj)->Set_Common_Motion(COMMON_STATE::STRONG_ATTACK);
}

void CLavaEruption::Motion_Func()
{

}

void CLavaEruption::Motion_End()
{
	for (int i = 0; i < 10; i++)
	{
		int iRX = rand() % 1000 - 500;
		int iRY = rand() % 1000 - 500;
		OBJ_INST->Add_Object(OBJ_M_BULLET, CAbstractFactory<CLava>::Create(POINT{ m_pObj->Get_Point().x + iRX,m_pObj->Get_Point().y + iRY}));
	}
}
