#pragma once

#include "cocos2d.h"

class MainGameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    CREATE_FUNC(MainGameScene);

    virtual bool init() override;
};

