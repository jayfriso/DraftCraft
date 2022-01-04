#pragma once

#include "cocos2d.h"
#include "Model/GameState.h"
#include "ViewModel/IListenerView.h"

USING_NS_CC;

class DraftBoardView : public Node, IListenerView
{
private:
    static const float WIDTH;

public:
    virtual bool init() override;
    CREATE_FUNC(DraftBoardView);

    virtual void update(const DispatcherViewModel& viewModel) override;
};
