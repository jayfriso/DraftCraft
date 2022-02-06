#pragma once

#include "cocos2d.h"
#include "HorizontalLayoutContainer.h"
#include "CardView.h"
#include <list>
#include <stack>
#include "EventNode.h";

USING_NS_CC;
using namespace std;

class InteractableCardContainer : public Node
{
private:
    static constexpr int DEFAULT_MAX_SPACING = 15;

    HorizontalLayoutContainer* m_horizontalContainer;
    Sprite* m_bgSprite;
    list<CardView*> m_activeCardViews;
    stack<CardView*> m_cardViewPool;

    int m_maxSpacing;

    int inline cardHeight() const { return _contentSize.height; }
    int spacing() const;

    void redistributeCardViews();

public:
    InteractableCardContainer() : m_maxSpacing{ DEFAULT_MAX_SPACING } {}
    CREATE_FUNC(InteractableCardContainer);
    virtual bool init() override;

    virtual void setContentSize(const Size& contentSize) override;

    void addCard(const Card& card);
    void clearCards();
    void removeCardAtIndex();

    bool handleCardMouseDown(EventMouse* event, EventNode* target);
};