#include "DraftDrawerView.h"
#include "UIConstants.h"
#include <iostream>
#include "UIUtils.h"

const float DraftDrawerView::DRAWER_TOGGLE_ANIM_LENGTH{ 0.3 };

void DraftDrawerView::initWithModel(DraftBoard& draftBoard, AbstractCommandProcessor& AbstractCommandProcessor, unsigned int localPlayerIndex)
{
    this->setContentSize(Size(120, UIConstants::DRAFT_BOARD_HEIGHT));
    this->setAnchorPoint(Vec2(0, 0.5f));

    m_draftBoardView = DraftBoardView::create(AbstractCommandProcessor, localPlayerIndex);
    this->addChild(m_draftBoardView, 0);
    m_draftBoardView->initWithModel(draftBoard);
    ui_utils::setAnchoredPosition(m_draftBoardView, AnchorPosition::CenterLeft);

    auto draftDrawerBg = Sprite::create("ui/draft_board/draft_drawer_bg.png");
    this->addChild(draftDrawerBg, 1);
    ui_utils::setAnchoredPosition(draftDrawerBg, AnchorPosition::CenterLeft);

    auto button = EventSprite::create("ui/draft_board/draft_drawer_triangle.png", "");
    button->setAnchorPoint(Vec2(0.4f, 0.5f));
    button->setPosition(Vec2(65, 500));
    button->setMouseClickEvent(CC_CALLBACK_2(DraftDrawerView::onDrawerButtonPressed, this));
    this->addChild(button, 2);
}

bool DraftDrawerView::onDrawerButtonPressed(EventMouse* event, EventNode* target)
{
    m_isOpen = !m_isOpen;
    auto button = static_cast<EventSprite*>(target);
    button->setScaleX(button->getScaleX() * -1);
        
    m_draftBoardView->stopAllActions();
    float moveToXPos = m_isOpen ? 0 : -(m_draftBoardView->getContentSize().width);
    auto moveToAction = MoveTo::create(DRAWER_TOGGLE_ANIM_LENGTH, Vec2(moveToXPos, m_draftBoardView->getPositionY()));
    m_draftBoardView->runAction(moveToAction);
    return true;
}
