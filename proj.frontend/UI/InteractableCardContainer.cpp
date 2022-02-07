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

CardView* InteractableCardContainer::getCardViewFromPool(const Card& data)
{
    auto result = m_pooledCardViews.top();
    m_pooledCardViews.pop();
    result->setCardData(&data);
    result->setVisible(true);
    return result;
}

CardView* InteractableCardContainer::createNewCardView(const Card& data)
{
    auto result = CardView::create(&data);
    result->setMouseDownEvent(CC_CALLBACK_2(InteractableCardContainer::handleCardMouseDown, this));
    result->setMouseEnterEvent(CC_CALLBACK_2(InteractableCardContainer::handleCardMouseEnter, this));
    result->setMouseExitEvent(CC_CALLBACK_2(InteractableCardContainer::handleCardMouseExit, this));
    result->setMouseMoveOverEvent(CC_CALLBACK_2(InteractableCardContainer::handleCardMouseMoveOver, this));
    m_horizontalContainer->addChild(result);
    return result;
}

void InteractableCardContainer::moveCardViewToPool(list<CardView*>::iterator cardIterator, bool removeFromActiveViewList)
{
    auto cardView = *cardIterator;
    cardView->setVisible(false);
    cardView->setCardData(nullptr);
    cardView->setEventsEnabled(false);
    cardView->stopAllActions();

    if (removeFromActiveViewList)
        m_activeCardViews.erase(cardIterator);
    m_pooledCardViews.push(cardView);
}

bool InteractableCardContainer::init()
{
    if (!Node::init())
        return false;

    m_bgSprite = UIUtils::createGenericRoundedRect(Size(0, 0), UIConstants::COLOR_GREY);
    addChild(m_bgSprite, 0);

    m_horizontalContainer = HorizontalLayoutContainer::create(spacing(), cardHeight());
    m_horizontalContainer->setChildAnchorPoint(Vec2{ 0.5, 0.5 });
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

void InteractableCardContainer::addCard(const Card& data)
{
    CardView* cardView = nullptr;
    if (!m_pooledCardViews.empty())
    {
        cardView = getCardViewFromPool(data);
    }
    else
    {
        cardView = createNewCardView(data);
    }

    cardView->setEventsEnabled(true);
    cardView->resize(cardHeight());
    size_t index = m_activeCardViews.size();
    cardView->setLocalZOrder(index + 1); // adding 1 here because 0 makes zorder multiplication not work
    m_activeCardViews.push_back(cardView);

    redistributeCardViews();
}

void InteractableCardContainer::clearCards()
{
    for (auto it = m_activeCardViews.begin(); it != m_activeCardViews.end(); it++)
    {
        moveCardViewToPool(it, false);
    }
    m_activeCardViews.clear();
    redistributeCardViews();
}

void InteractableCardContainer::removeCard(list<CardView*>::iterator cardIterator)
{
    if (cardIterator == m_activeCardViews.end())
        return;

    moveCardViewToPool(cardIterator);

    redistributeCardViews();
}

void InteractableCardContainer::removeCardAtIndex(size_t index)
{
    auto targetIterator = m_activeCardViews.begin();
    std::advance(targetIterator, index);
    removeCard(targetIterator);
}

bool InteractableCardContainer::handleCardMouseDown(EventMouse* event, EventNode* target)
{
    if (!m_cardMouseDownCallback)
        return false;

    auto targetCardView = static_cast<CardView*>(target);
    return m_cardMouseDownCallback(event, targetCardView, this);
}

static const float HIGHLIGHT_ANIM_DURATION{ 0.25f };
static const float SCALE_AMOUNT{ 1.2f };
static const float MOVE_Y_AMOUNT{ 100 };
bool InteractableCardContainer::handleCardMouseEnter(EventMouse* event, EventNode* target)
{
    auto targetCardView = static_cast<CardView*>(target);
    m_currentHighlightedCardView = targetCardView;

    targetCardView->setLocalZOrder(targetCardView->getLocalZOrder() * 1000); // Multiply by 1000 to appear on top

    float currentScale = targetCardView->getScale();
    if (m_cardOriginalScale < 0)
        m_cardOriginalScale = currentScale;
    float scaleToValue = currentScale * SCALE_AMOUNT;
    auto scaleTo = ScaleTo::create(HIGHLIGHT_ANIM_DURATION, scaleToValue);

    Vec2 currentPosition = targetCardView->getPosition();
    if (m_cardOriginalYPosition < 0)
        m_cardOriginalYPosition = currentPosition.y;
    Vec2 targetPosition = currentPosition + Vec2{ 0, MOVE_Y_AMOUNT };
    auto moveTo = MoveTo::create(HIGHLIGHT_ANIM_DURATION, targetPosition);

    targetCardView->stopAllActions();
    targetCardView->runAction(scaleTo);
    targetCardView->runAction(moveTo);

    return true;
}
bool InteractableCardContainer::handleCardMouseExit(EventMouse* event, EventNode* target)
{
    auto targetCardView = static_cast<CardView*>(target);

    targetCardView->setLocalZOrder(targetCardView->getLocalZOrder() / 1000); // Divide by 1000 to go back to original z order

    auto scaleTo = ScaleTo::create(HIGHLIGHT_ANIM_DURATION, m_cardOriginalScale);
    auto moveTo = MoveTo::create(HIGHLIGHT_ANIM_DURATION, Vec2{ target->getPositionX(), m_cardOriginalYPosition });

    targetCardView->stopAllActions();
    targetCardView->runAction(scaleTo);
    targetCardView->runAction(moveTo);

    return true;
}

bool InteractableCardContainer::handleCardMouseMoveOver(EventMouse* event, EventNode* target)
{
    auto targetCardView = static_cast<CardView*>(target);
    // Stop propogation if card is the current highlited card. This will stop propagation to any child nodes.
    if (targetCardView == m_currentHighlightedCardView)
        return true;
    else
        return false;
}