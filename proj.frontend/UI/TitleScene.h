#pragma once

#include "cocos2d.h"
#include "Model/GameState.h"
#include "../Utils/CustomMacros.h"
#include "../AppLifetimeResources.h"

class TitleScene : public cocos2d::Scene
{
private:
    AppLifetimeResources& m_appLifetimeResources;
    bool m_shouldLoadResources;

    bool loadResources();
    void showMenu();

    void onTestGameButtonPressed();

public:
    TitleScene(AppLifetimeResources& appLifetimeResources, bool shouldLoadResources) : m_appLifetimeResources{appLifetimeResources}, m_shouldLoadResources { shouldLoadResources } {};
    static cocos2d::Scene* createScene(AppLifetimeResources& appLifetimeResources, bool shouldLoadResources);
    CREATE_FUNC_TWO_PARAM_CONSTRUCTOR(TitleScene, AppLifetimeResources&, bool);

    void setResources(IStaticDataManager* staticDataManager); // rename to transfer resources and change to r-ref move semantics

    virtual bool init() override;
};

