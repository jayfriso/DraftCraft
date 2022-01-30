#pragma once

#include "cocos2d.h"
#include "ViewModel/IListenerView.h"
#include "DraftDeckView.h"
#include "CustomMacros.h"
#include "Model/DraftBoard.h"

USING_NS_CC;

class DraftBoardView : public Node, IListenerView<DraftBoard>
{
private:
    static const float WIDTH;

    DraftBoard& m_draftBoard;

    DraftDeckView* m_draftDeckView;

public:
    DraftBoardView(DraftBoard& draftBoard) : m_draftBoard{draftBoard} {}
    virtual ~DraftBoardView();
    CREATE_FUNC_ONE_PARAM(DraftBoardView, DraftBoard&);
    virtual bool init() override;

    virtual void update(const DraftBoard& viewModel) override;
};

