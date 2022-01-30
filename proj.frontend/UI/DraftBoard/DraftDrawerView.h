#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "DraftBoardView.h"
#include "Model/DraftBoard.h"
#include "CustomMacros.h"

USING_NS_CC;
using namespace ui;

class DraftDrawerView : public Node
{
private:
    static const float DRAWER_TOGGLE_ANIM_LENGTH;

    DraftBoard& m_draftBoard;

    DraftBoardView* m_draftBoard_view;
    bool m_isOpen{ true };

public:
    DraftDrawerView(DraftBoard& draftBoard) : m_draftBoard{draftBoard} {}
    virtual ~DraftDrawerView();
    CREATE_FUNC_ONE_PARAM(DraftDrawerView, DraftBoard&);
    virtual bool init() override;

    void onDrawerButtonPressed(cocos2d::Ref* pSender, Widget::TouchEventType type);

};

