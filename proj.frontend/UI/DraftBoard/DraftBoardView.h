#pragma once

#include "cocos2d.h"
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

    DraftDeckView* m_draftDeckView;
    Node* m_localPlayerContainer;
    InteractableCardContainer* m_draftOptionsContainer;
    Node* m_opponentPlayerContainer;

    unsigned int m_localPlayerIndex;

    void updateDraftingState(const DraftBoard& viewModel);

public:
    virtual void initWithModel(DraftBoard& viewModel) override;
    CREATE_FUNC(DraftBoardView);
    void setLocalPlayerIndex(unsigned int index) { m_localPlayerIndex = index; }

    virtual void update(const DraftBoard& viewModel) override;
};

