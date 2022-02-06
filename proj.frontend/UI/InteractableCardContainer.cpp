#include "InteractableCardContainer.h"
#include "UIUtils.h"
#include "UIConstants.h"
#include <iostream>

using namespace std::placeholders;

int InteractableCardContainer::spacing() const
{
    if (m_activeCardViews.size() == 0)
        return m_maxSpacing;

    float widthOfCard = m_activeCardViews.front()->getBoundingBox().size.width;
    int numCards = m_activeCardViews.size();
    float totalWidthWithMaxSpacing = (widthOfCard * numCards) + (m_maxSpacing * numCards - 1);
    if (totalWidthWithMaxSpacing <= _contentSize.width)
        return m_maxSpacing;
    else
        return (_contentSize.width - (widthOfCard * numCards)) / (numCards - 1);
}

void InteractableCardContainer::redistributeCardViews()
{
    m_horizontalContainer->setSpace(spacing(), true);
    UIUtils::setAnchoredPosition(m_horizontalContainer, AnchorPosition::CenterCenter);
}

bool InteractableCardContainer::init()
{
    if (!Node::init())
        return false;

    m_bgSprite = UIUtils::createGenericRoundedRect(Size(0, 0), UIConstants::COLOR_GREY);
    addChild(m_bgSprite, 0);

    m_horizontalContainer = HorizontalLayoutContainer::create(spacing(), cardHeight());
    addChild(m_horizontalContainer, 1);

    return true;
}

void InteractableCardContainer::setContentSize(const Size& contentSize)
{
    Node::setContentSize(contentSize);

    m_bgSprite->setContentSize(contentSize);
    UIUtils::setAnchoredPosition(m_bgSprite, AnchorPosition::CenterCenter);

    for (auto cardView : m_activeCardViews)
    {
        cardView->resize(cardHeight());
    }
    
    redistributeCardViews();
}

void InteractableCardContainer::addCard(const Card& card)
{
    CardView* cardView = nullptr;
    if (!m_cardViewPool.empty())
    {
        cardView = m_cardViewPool.top();
        m_cardViewPool.pop();
        cardView->setCardData(&card);
    }
    else
    {
        cardView = CardView::create(&card);
    }

    auto eventNodeTest = EventNode::create(true);
    eventNodeTest->setMouseDownEvent(CC_CALLBACK_2(InteractableCardContainer::handleCardMouseDown, this));
    eventNodeTest->setContentSize(Size{ 200,200 });
    auto bg = UIUtils::createGenericRoundedRect(Size{ 200,200 }, Color3B::YELLOW);
    UIUtils::setAnchoredPosition(bg, AnchorPosition::CenterCenter);
    eventNodeTest->addChild(bg);
    UIUtils::setAnchoredPosition(eventNodeTest, AnchorPosition::CenterCenter);
    addChild(eventNodeTest);

    cardView->resize(cardHeight());
    m_activeCardViews.push_back(cardView);
    m_horizontalContainer->addChild(cardView);
    redistributeCardViews();
}

void InteractableCardContainer::clearCards()
{
}

void InteractableCardContainer::removeCardAtIndex()
{
}

bool InteractableCardContainer::handleCardMouseDown(EventMouse* event, EventNode* target)
{
    CCLOG("Position : %f %f", event->getCursorX(), event->getCursorY());
    return true;
}
