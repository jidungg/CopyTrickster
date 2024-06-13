#pragma once

#include "Character.h"

template<typename T>
class CAbstractFactory
{
public:
	CAbstractFactory(){}
	~CAbstractFactory(){}

public:
	static CObj*		Create()
	{
		CObj*		pObj = new T;
		pObj->Initialize();

		return pObj;
	}

	static CObj*		Create(float fX, float fY, DIRECTION eDir = DIR_END)
	{
		CObj*		pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(fX,fY);
		pObj->Set_Direction(eDir);

		return pObj;
	}
	static CObj* Create(INFO _tInfo, DIRECTION eDir = DIR_END)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Info(_tInfo);
		pObj->Set_Direction(eDir);

		return pObj;
	}
	static CObj* Create(POINT _tPoint)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_tPoint.x,_tPoint.y);

		return pObj;
	}
	static CCharacter* Create(POINT _tPoint ,CHARACTER_DATA* _pData)
	{
		CCharacter* pObj = new T;
		pObj->Set_Data(_pData);
		pObj->Initialize();
		pObj->Set_Pos(_tPoint.x, _tPoint.y);

		return pObj;
	}
};

