#include "DraftDrawerView.h"
#include "../UIConstants.h"
#include <iostream>

using namespace ui;

const float DraftDrawerView::WIDTH{ 120 };
const Vec2 DraftDrawerView::ARROW_POSITION{ 65, 500 };
const Vec2 DraftDrawerView::ARROW_ANCHOR{ 0.4f, 0.5f };
const float DraftDrawerView::DRAWER_TOGGLE_ANIM_LENGTH{ 0.3 };


bool DraftDrawerView::init()
{
    if (!Node::init())
        return false;
    this->setContentSize(Size(WIDTH, UIConstants::DRAFT_BOARD_HEIGHT));
    this->setAnchorPoint(Vec2(0, 0.5f));

    m_draftBoard = DraftBoardView::create();
    m_draftBoard->setAnchorPoint(Vec2(0, 0.5f));
    m_draftBoard->setPositionNormalized(Vec2(0, 0.5f));
    this->addChild(m_draftBoard, 0);

    auto draftDrawerBg = Sprite::create("ui/draft_board/draft_drawer_bg.png");
    draftDrawerBg->setAnchorPoint(Vec2(0, 0.5f));
    draftDrawerBg->setPositionNormalized(Vec2(0, 0.5f));
    this->addChild(draftDrawerBg, 1);

    auto button = Button::create("ui/draft_board/draft_drawer_triangle.png");
    button->setAnchorPoint(ARROW_ANCHOR);
    button->setPosition(ARROW_POSITION);
    button->addTouchEventListener(CC_CALLBACK_2(DraftDrawerView::onDrawerButtonPressed, this));
    this->addChild(button, 2);

    return true;
}

void DraftDrawerView::onDrawerButtonPressed(cocos2d::Ref* pSender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        m_isOpen = !m_isOpen;
        auto button = static_cast<Button*>(pSender);
        button->setScaleX(button->getScaleX() * -1);
        
        m_draftBoard->stopAllActions();
        float moveToXPos = m_isOpen ? 0 : -(m_draftBoard->getContentSize().width);
        auto moveToAction = MoveTo::create(DRAWER_TOGGLE_ANIM_LENGTH, Vec2(moveToXPos, m_draftBoard->getPositionY()));
        m_draftBoard->runAction(moveToAction);
    }
}
