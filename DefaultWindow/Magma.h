#pragma once
#include "Scene.h"
class CMagma :
    public CScene
{
public:
    CMagma();
    ~CMagma();
    void Start(SCENE_ID _ePrevScene)override;
};
 
