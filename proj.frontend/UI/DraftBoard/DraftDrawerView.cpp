#include "DraftDrawerView.h"
#include "UIConstants.h"
#include <iostream>

using namespace ui;

const float DraftDrawerView::DRAWER_TOGGLE_ANIM_LENGTH{ 0.3 };

void DraftDrawerView::initWithModel(DraftBoard& draftBoard, CommandProcessor& commandProcessor, unsigned int localPlayerIndex)
{
    this->setContentSize(Size(120, UIConstants::DRAFT_BOARD_HEIGHT));
    this->setAnchorPoint(Vec2(0, 0.5f));

    m_draftBoardView = DraftBoardView::create(commandProcessor, localPlayerIndex);
    m_draftBoardView->initWithModel(draftBoard);
    m_draftBoardView->setAnchorPoint(Vec2(0, 0.5f));
    m_draftBoardView->setPositionNormalized(Vec2(0, 0.5f));
    this->addChild(m_draftBoardView, 0);

    auto draftDrawerBg = Sprite::create("ui/draft_board/draft_drawer_bg.png");
    draftDrawerBg->setAnchorPoint(Vec2(0, 0.5f));
    draftDrawerBg->setPositionNormalized(Vec2(0, 0.5f));
    this->addChild(draftDrawerBg, 1);

    auto button = Button::create("ui/draft_board/draft_drawer_triangle.png");
    button->setAnchorPoint(Vec2(0.4f, 0.5f));
    button->setPosition(Vec2(65, 500));
    button->addTouchEventListener(CC_CALLBACK_2(DraftDrawerView::onDrawerButtonPressed, this));
    this->addChild(button, 2);
}

void DraftDrawerView::onDrawerButtonPressed(cocos2d::Ref* pSender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        m_isOpen = !m_isOpen;
        auto button = static_cast<Button*>(pSender);
        button->setScaleX(button->getScaleX() * -1);
        
        m_draftBoardView->stopAllActions();
        float moveToXPos = m_isOpen ? 0 : -(m_draftBoardView->getContentSize().width);
        auto moveToAction = MoveTo::create(DRAWER_TOGGLE_ANIM_LENGTH, Vec2(moveToXPos, m_draftBoardView->getPositionY()));
        m_draftBoardView->runAction(moveToAction);
    }
}
