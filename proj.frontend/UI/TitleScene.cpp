#include "TitleScene.h"
#include "StaticData/TestStaticDataManager.h"
#include "ui/CocosGUI.h"
#include <iostream>

USING_NS_CC;
using namespace ui;

bool TitleScene::loadResources()
{
    if (m_appLifetimeResources.loadResources())
    {
        showMenu();
        return true;
    }
    else
    {
        return false;
    }
}

void TitleScene::showMenu()
{
    auto testGameLabel = Label::createWithTTF("Test Game", "fonts/FredokaOne-Regular.ttf", 40);
    auto testGameButton = MenuItemLabel::create(testGameLabel, CC_CALLBACK_0(TitleScene::onTestGameButtonPressed, this));

    auto menu = Menu::createWithItem(testGameButton);

    this->addChild(menu, 0);
}

void TitleScene::onTestGameButtonPressed()
{
    // TODO : Load the game
}

cocos2d::Scene* TitleScene::createScene(AppLifetimeResources& appLifetimeResources, bool shouldLoadResources)
{
    return TitleScene::create(appLifetimeResources, shouldLoadResources);
}

void TitleScene::setResources(IStaticDataManager* staticDataManager)
{
}

bool TitleScene::init()
{
    if (m_shouldLoadResources)
        return loadResources();
    else
        showMenu();
    return true;
}
