#include "DraftDrawer.h"
#include <iostream>

using namespace ui;

bool DraftDrawer::init()
{
    if (!Node::init())
        return false;
    this->setContentSize(Size(120, 1000));
    this->setAnchorPoint(Vec2(0, 0.5f));

    auto draftDrawerBg = Sprite::create("ui/draft_board/draft_drawer_bg.png");
    draftDrawerBg->setAnchorPoint(Vec2(0, 0.5f));
    this->addChild(draftDrawerBg, 0);
    draftDrawerBg->setPositionNormalized(Vec2(0, 0.5f));

    auto button = Button::create("ui/draft_board/draft_drawer_triangle.png");
    this->addChild(button, 1);
    button->setAnchorPoint(Vec2(0.4f, 0.5f));
    button->setPosition(Vec2(65, 500));
    button->addTouchEventListener(CC_CALLBACK_2(DraftDrawer::onDrawerButtonPressed, this));

    return true;
}

void DraftDrawer::onDrawerButtonPressed(cocos2d::Ref* pSender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        auto button = static_cast<Button*>(pSender);
        button->setScaleX(button->getScaleX() * -1);
    }
}
