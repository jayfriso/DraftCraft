#pragma once

#include "cocos2d.h"
#include "ViewModel/AbstractListenerView.h"
#include "Model/Player.h"
#include "../InteractableCardContainer.h"

USING_NS_CC;

class LocalPlayerBoardView : public Node, AbstractListenerView<Player>
{
private:
    InteractableCardContainer* m_interactableCardContainer;

public:
    CREATE_FUNC(LocalPlayerBoardView);
    virtual void initWithModel(Player& viewModel) override;
    virtual void update(const Player& viewModel) override;
};

