#include "MainGameScene.h"
#include "DraftBoard/DraftDrawerView.h";
#include "GameBoard/GameBoardView.h"
#include "Debug/DebugMenu.h"
#include "UIUtils.h"

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

    auto drawer = DraftDrawerView::create();
    drawer->initWithModel(m_gameState.draftBoard(), m_commandProcessor, m_gameState.localPlayerIndex());
    addChild(drawer, 1);
    UIUtils::setAnchoredPosition(drawer, AnchorPosition::CenterLeft);

    auto boardView = GameBoardView::create(m_gameState, m_commandProcessor);
    addChild(boardView, 0);
    UIUtils::setAnchoredPosition(boardView, AnchorPosition::BottomCenter);

#if _DEBUG
    auto debugMenu = DebugMenu::create(m_gameState, m_commandProcessor);
    addChild(debugMenu, 2);
    UIUtils::setAnchoredPosition(debugMenu, AnchorPosition::CenterCenter);
#endif

    return true;
}