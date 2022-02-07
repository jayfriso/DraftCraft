#pragma once
#include "cocos2d.h"
#include "ViewModel/AbstractListenerView.h"
#include "Model/DraftDeck.h"
#include "CustomMacros.h"

USING_NS_CC;

class DraftDeckView : public Node, AbstractListenerView<DraftDeck>
{
private:
    static const string CARDS_LEFT_TEXT;

    Label* m_cardsLeftLabel;

    void setNumCardsLeft(int numCardsLeft);

public:
    virtual void initWithModel(DraftDeck& viewModel) override;
    CREATE_FUNC(DraftDeckView);
    virtual void update(const DraftDeck& viewModel) override;
};

