#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "DraftBoard.h"


USING_NS_CC;
using namespace ui;

class DraftDrawer : public Node
{
private:
    static const float WIDTH;
    static const Vec2 ARROW_POSITION;
    static const Vec2 ARROW_ANCHOR;
    static const float DRAWER_TOGGLE_ANIM_LENGTH;


    DraftBoard* m_draftBoard;
    bool m_isOpen{ true };

public:
    virtual bool init() override;
    CREATE_FUNC(DraftDrawer);

    void onDrawerButtonPressed(cocos2d::Ref* pSender, Widget::TouchEventType type);

};

