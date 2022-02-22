#pragma once

#include "cocos2d.h"
#include "../InteractableCardContainer.h"
#include "CommandSystem/CommandProcessor.h"
#include "LocalPlayerBoardView.h"
#include "CustomMacros.h"

USING_NS_CC;

class GameBoardView : public Node
{
private:
    GameState& m_gameState;
    CommandProcessor& m_commandProcessor;

    LocalPlayerBoardView* m_localPlayerView;

public:
    GameBoardView(GameState& gameState, CommandProcessor& commandProcesser): m_gameState{gameState}, m_commandProcessor{commandProcesser} {}

    CREATE_FUNC_TWO_PARAM(GameBoardView, GameState&, CommandProcessor&);
    virtual bool init() override;
};

