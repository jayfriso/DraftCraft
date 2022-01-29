#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "DraftBoardView.h"

USING_NS_CC;
using namespace ui;

class DraftDrawerView : public Node
{
private:
    static const float DRAWER_TOGGLE_ANIM_LENGTH;

    DraftBoardView* m_draftBoard;
    bool m_isOpen{ true };

public:
    virtual bool init() override;
    CREATE_FUNC(DraftDrawerView);

    void onDrawerButtonPressed(cocos2d::Ref* pSender, Widget::TouchEventType type);

};

