#pragma once
#include "CharacterHPBar.h"
class CCharacterMPBar :
    public CCharacterHPBar
{
public:
    CCharacterMPBar(int _iXPos, int _iYPos, int _iXSize, int _iYSize, int _iBorderX, int _iBorderY);
    ~CCharacterMPBar();
public:
    void Update() override;
};

