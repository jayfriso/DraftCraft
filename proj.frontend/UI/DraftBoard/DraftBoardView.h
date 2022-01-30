#pragma once

#include "cocos2d.h"
#include "ViewModel/AbstractListenerView.h"
#include "DraftDeckView.h"
#include "CustomMacros.h"
#include "Model/DraftBoard.h"

USING_NS_CC;

class DraftBoardView : public Node, AbstractListenerView<DraftBoard>
{
private:
    static const float WIDTH;

    DraftDeckView* m_draftDeckView;

public:
    virtual void initWithModel(DraftBoard& viewModel) override;
    CREATE_FUNC(DraftBoardView);

    virtual void update(const DraftBoard& viewModel) override;
};

