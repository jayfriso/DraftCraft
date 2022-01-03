#include "MainGameScene.h"
#include "DraftBoard/DraftDrawerView.h";

USING_NS_CC;

MainGameScene::MainGameScene(IStaticDataManager& staticDataManager) : m_staticDataManager{staticDataManager}, m_gameState { staticDataManager, "player0", "player1", 0, 69 } {}

Scene* MainGameScene::createScene(IStaticDataManager& staticDataManager)
{
    return MainGameScene::create(staticDataManager);
}

MainGameScene* MainGameScene::create(IStaticDataManager& staticDataManager)
{
    MainGameScene* scene = new(std::nothrow) MainGameScene(staticDataManager);
    if (scene)
    {
        if (scene->init())
        {
            scene->autorelease();
            return scene;
        }
    }
    CC_SAFE_DELETE(scene);
    return nullptr;
}

bool MainGameScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto drawer = DraftDrawerView::create();
    addChild(drawer, 0);
    drawer->setPositionNormalized(Vec2(0, 0.5));
    return true;
}