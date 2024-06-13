#pragma once
#include "Define.h"
#include "Character.h"
class IQuickSlotRegister
{
public:
	virtual void Use(CCharacter* _pObj, CCharacter* _pSbj) PURE;
};