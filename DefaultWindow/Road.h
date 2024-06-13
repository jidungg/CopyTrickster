#pragma once
#include "Scene.h"
class CRoad :
    public CScene
{
public:
    CRoad();
    ~CRoad();

    void    Start(SCENE_ID _ePrevScene) override;
};

