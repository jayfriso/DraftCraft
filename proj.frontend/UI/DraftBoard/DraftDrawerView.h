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

    DraftBoardView* m_draftBoard_view;
    bool m_isOpen{ true };

public:
    virtual ~DraftDrawerView() = default;
    CREATE_FUNC(DraftDrawerView);
    void initWithModel(DraftBoard& draftBoard);

    void onDrawerButtonPressed(cocos2d::Ref* pSender, Widget::TouchEventType type);

};

