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
    typedef std::function<bool(EventMouse* mouseEvent, CardView* cardView, size_t cardIndex)> CardMouseDownCallback;

    static constexpr int DEFAULT_MAX_SPACING = 40;

    HorizontalLayoutContainer* m_horizontalContainer;
    Sprite* m_bgSprite;
    list<CardView*> m_activeCardViews;
    vector<CardView*> m_pooledCardViews;
    Sequence* m_hoverOverSequence;
    CardView* m_currentHighlightedCardView;
    CardMouseDownCallback m_cardMouseClickCallback;

    int m_maxSpacing;
    float m_cardOriginalYPosition;
    float m_cardOriginalScale;

    bool m_isEventsEnabled;

    int inline cardHeight() const { return _contentSize.height; }
    int spacing() const;

    void redistributeCardViews();
    CardView* getCardViewFromPool(const Card* data);
    CardView* createNewCardView(const Card* data);
    void moveCardViewToPool(list<CardView*>::iterator cardIterator, bool removeFromActiveViewList = true);
    void setEventsEnabledForCardView(CardView* cardView, bool enabled);

public:
    InteractableCardContainer() :
        m_maxSpacing{ DEFAULT_MAX_SPACING },
        m_activeCardViews{},
        m_pooledCardViews{},
        m_cardOriginalYPosition{ -1 },
        m_cardOriginalScale{ -1 },
        m_cardMouseClickCallback{ nullptr },
        m_isEventsEnabled{ true }{}

    CREATE_FUNC(InteractableCardContainer);
    virtual bool init() override;

    virtual void setContentSize(const Size& contentSize) override;

    void addCard(const Card* card, bool shouldRedistribute = true);
    void addCards(const vector<const Card*>& cards);
    void clearCards();
    void removeCard(list<CardView*>::iterator cardIterator);
    void removeCardAtIndex(size_t index);

    void setEventsEnabled(bool enabled);

    bool handleCardMouseClick(EventMouse* event, EventNode* target);
    bool handleCardMouseEnter(EventMouse* event, EventNode* target);
    bool handleCardMouseExit(EventMouse* event, EventNode* target);
    bool handleCardMouseMoveOver(EventMouse* event, EventNode* target);

    void setCardMouseClickCallback(CardMouseDownCallback callback) { m_cardMouseClickCallback = callback; }
    void clearCardMouseClickCallback() { m_cardMouseClickCallback = nullptr; }
};