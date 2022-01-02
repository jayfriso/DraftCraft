#include "MainGameScene.h"
#include "DraftBoard/DraftDrawer.h";

USING_NS_CC;

Scene* MainGameScene::createScene()
{
    return MainGameScene::create();
}

bool MainGameScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto drawer = DraftDrawer::create();
    addChild(drawer, 0);
    drawer->setPositionNormalized(Vec2(0, 0.5));
    return true;
}