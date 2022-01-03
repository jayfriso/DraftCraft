#pragma once

#include "cocos2d.h"
#include "../proj.draftcraft_models/Model/GameState.h"

class MainGameScene : public cocos2d::Scene
{
private:
    IStaticDataManager& m_staticDataManager;
    GameState m_gameState;

public:
    MainGameScene(IStaticDataManager& staticDataManager);

    static cocos2d::Scene* createScene(IStaticDataManager& staticDataManager);
    static MainGameScene* create(IStaticDataManager& staticDataManager);

    virtual bool init() override;
};

