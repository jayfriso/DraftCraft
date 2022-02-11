#pragma once

#include "cocos2d.h"
#include "CommandSystem/CommandProcessor.h"
#include "ViewModel/AbstractListenerView.h"
#include "DraftDeckView.h"
#include "CustomMacros.h"
#include "Model/DraftBoard.h"
#include "HorizontalLayoutContainer.h"
#include "../InteractableCardContainer.h"

USING_NS_CC;

class DraftBoardView : public Node, AbstractListenerView<DraftBoard>
{
private:
    static const float WIDTH;

    CommandProcessor& m_commandProcessor;

    DraftDeckView* m_draftDeckView;
    Node* m_localPlayerContainer;
    InteractableCardContainer* m_draftOptionsContainer;
    Node* m_opponentPlayerContainer;

    Button* m_skipButton;
    Sprite* m_skipButtonIcon;
    Label* m_skipButtonLabel;

    unsigned int m_localPlayerIndex;

public:
    DraftBoardView(CommandProcessor& commandProcessor, unsigned int localPlayerIndex): 
        m_commandProcessor{commandProcessor},
        m_localPlayerIndex{localPlayerIndex}{}
    virtual void initWithModel(DraftBoard& viewModel) override;
    CREATE_FUNC_TWO_PARAM(DraftBoardView, CommandProcessor&, unsigned int);

    virtual void update(const DraftBoard& viewModel) override;

    bool onCardMouseDown(EventMouse* mouseEvent, CardView* cardView, size_t index);
    bool onSkipButtonDown(Ref* buttonRef);
};

