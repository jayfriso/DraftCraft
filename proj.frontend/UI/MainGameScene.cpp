#include "MainGameScene.h"
#include "DraftBoard/DraftDrawerView.h";

USING_NS_CC;

MainGameScene::MainGameScene(AppLifetimeResources& appLifetimeResources) : 
    m_appLifetimeResources{ appLifetimeResources }, 
    m_gameState { m_appLifetimeResources.staticDataManager(), *(m_appLifetimeResources.matchMaker().currentMatch())},
    m_commandProcessor{m_gameState}
{}

Scene* MainGameScene::createScene(AppLifetimeResources& appLifetimeResources)
{
    return MainGameScene::create(appLifetimeResources);
}

bool MainGameScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto drawer = DraftDrawerView::create(m_gameState.draftBoard());
    addChild(drawer, 0);
    drawer->setPositionNormalized(Vec2(0, 0.5));
    return true;
}