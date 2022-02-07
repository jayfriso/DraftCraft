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
    typedef std::function<bool(EventMouse* mouseEvent, CardView* cardView, InteractableCardContainer* cardContainer)> CardMouseDownCallback;

    static constexpr int DEFAULT_MAX_SPACING = 15;

    HorizontalLayoutContainer* m_horizontalContainer;
    Sprite* m_bgSprite;
    list<CardView*> m_activeCardViews;
    stack<CardView*> m_pooledCardViews;
    Sequence* m_hoverOverSequence;
    CardView* m_currentHighlightedCardView;
    CardMouseDownCallback m_cardMouseDownCallback;

    int m_maxSpacing;
    float m_cardOriginalYPosition;
    float m_cardOriginalScale;

    int inline cardHeight() const { return _contentSize.height; }
    int spacing() const;

    void redistributeCardViews();
    CardView* getCardViewFromPool(const Card& data);
    CardView* createNewCardView(const Card& data);
    void moveCardViewToPool(list<CardView*>::iterator cardIterator, bool removeFromActiveViewList = true);

public:
    InteractableCardContainer() :
        m_maxSpacing{ DEFAULT_MAX_SPACING },
        m_activeCardViews{},
        m_pooledCardViews{},
        m_cardOriginalYPosition{ -1 },
        m_cardOriginalScale{ -1 },
        m_cardMouseDownCallback{ nullptr }{}

    CREATE_FUNC(InteractableCardContainer);
    virtual bool init() override;

    virtual void setContentSize(const Size& contentSize) override;

    void addCard(const Card& card);
    void clearCards();
    void removeCard(list<CardView*>::iterator cardIterator);
    void removeCardAtIndex(size_t index);

    bool handleCardMouseDown(EventMouse* event, EventNode* target);
    bool handleCardMouseEnter(EventMouse* event, EventNode* target);
    bool handleCardMouseExit(EventMouse* event, EventNode* target);
    bool handleCardMouseMoveOver(EventMouse* event, EventNode* target);

    void setCardMouseDownCallback(CardMouseDownCallback callback) { m_cardMouseDownCallback = callback; }
    void clearCardMouseDownCallback() { m_cardMouseDownCallback = nullptr; }
};