#pragma once

#include "cocos2d.h"
#include "CommandSystem/AbstractCommandProcessor.h"
#include "ViewModel/AbstractListenerView.h"
#include "DraftDeckView.h"
#include "CustomMacros.h"
#include "Model/DraftBoard.h"
#include "HorizontalLayoutContainer.h"
#include "../InteractableCardContainer.h"
#include <array>
#include "DraftPileView.h"
#include "EventSprite.h"

USING_NS_CC;

class DraftBoardView : public Node, AbstractListenerView<DraftBoard>
{
private:
    static const float WIDTH;

    AbstractCommandProcessor& m_AbstractCommandProcessor;

    DraftDeckView* m_draftDeckView;
    Node* m_localPlayerContainer;
    InteractableCardContainer* m_draftOptionsContainer;
    Node* m_opponentPlayerContainer;
    std::array<DraftPileView*, DraftBoard::NUM_PILES> m_draftPileViews;

    EventSprite* m_skipButton;
    Sprite* m_skipButtonIcon;
    Label* m_skipButtonLabel;

    unsigned int m_localPlayerIndex;

public:
    DraftBoardView(AbstractCommandProcessor& AbstractCommandProcessor, unsigned int localPlayerIndex): 
        m_AbstractCommandProcessor{AbstractCommandProcessor},
        m_localPlayerIndex{localPlayerIndex}{}
    virtual void initWithModel(DraftBoard& viewModel) override;
    CREATE_FUNC_TWO_PARAM(DraftBoardView, AbstractCommandProcessor&, unsigned int);

    virtual void update(const DraftBoard& viewModel) override;

    bool onCardClicked(EventMouse* mouseEvent, CardView* cardView, size_t index);
    bool onSkipButtonClicked(Ref* buttonRef);
};

