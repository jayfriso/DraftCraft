#pragma once
#include "cocos2d.h"
#include "ViewModel/IListenerView.h"
#include "Model/DraftDeck.h"
#include "CustomMacros.h"

USING_NS_CC;

class DraftDeckView : public Node, IListenerView<DraftDeck>
{
private:
    static const string CARDS_LEFT_TEXT;

    DraftDeck& m_draftDeck;

public:
    DraftDeckView(DraftDeck& draftDeck) : m_draftDeck{ draftDeck } {}
    virtual ~DraftDeckView();
    virtual bool init() override;
    CREATE_FUNC_ONE_PARAM(DraftDeckView, DraftDeck&);
    virtual void update(const DraftDeck& viewModel) override;
};

