#pragma once

#include "cocos2d.h"
#include "Model/GameState.h"
#include "../AppLifetimeResources.h"
#include "CustomMacros.h"
#include "CommandSystem/CommandProcessor.h"

class MainGameScene : public cocos2d::Scene
{
private:
    AppLifetimeResources& m_appLifetimeResources;
    GameState m_gameState;
    CommandProcessor m_commandProcessor;

public:
    MainGameScene(AppLifetimeResources& appLifetimeResources);

    static cocos2d::Scene* createScene(AppLifetimeResources& appLifetimeResources);
    CREATE_FUNC_ONE_PARAM(MainGameScene, AppLifetimeResources&);

    virtual bool init() override;
};

