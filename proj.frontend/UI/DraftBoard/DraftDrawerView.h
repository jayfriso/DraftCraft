#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "DraftBoardView.h"
#include "Model/DraftBoard.h"
#include "CustomMacros.h"
#include "CommandSystem/CommandProcessor.h"

USING_NS_CC;
using namespace ui;

class DraftDrawerView : public Node
{
private:
    static const float DRAWER_TOGGLE_ANIM_LENGTH;

    DraftBoardView* m_draftBoardView;
    bool m_isOpen{ true };

public:
    CREATE_FUNC(DraftDrawerView);
    void initWithModel(DraftBoard& draftBoard, CommandProcessor& commandProcessor, unsigned int localPlayerIndex);

    void onDrawerButtonPressed(cocos2d::Ref* pSender, Widget::TouchEventType type);
};

