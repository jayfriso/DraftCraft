#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

class DraftDrawer : public Node
{
public:
    virtual bool init() override;
    CREATE_FUNC(DraftDrawer);

    void onDrawerButtonPressed(cocos2d::Ref* pSender, Widget::TouchEventType type);

};

