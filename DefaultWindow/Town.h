#pragma once
#include "Scene.h"

class CTown :
    public CScene
{
public:
    CTown();
    ~CTown();

    void    Start(SCENE_ID _ePrevScene) override;
};

