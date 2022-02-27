#pragma once

#include "cocos2d.h"
#include "DraftBoardView.h"
#include "Model/DraftBoard.h"
#include "CustomMacros.h"
#include "CommandSystem/AbstractCommandProcessor.h"
#include "EventSprite.h"

USING_NS_CC;

class DraftDrawerView : public Node
{
private:
    static const float DRAWER_TOGGLE_ANIM_LENGTH;

    DraftBoardView* m_draftBoardView;
    bool m_isOpen{ true };

public:
    CREATE_FUNC(DraftDrawerView);
    void initWithModel(DraftBoard& draftBoard, AbstractCommandProcessor& AbstractCommandProcessor, unsigned int localPlayerIndex);

    bool onDrawerButtonPressed(EventMouse* event, EventNode* target);
};

