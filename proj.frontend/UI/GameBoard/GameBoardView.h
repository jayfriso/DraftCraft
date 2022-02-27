#pragma once

#include "cocos2d.h"
#include "../InteractableCardContainer.h"
#include "CommandSystem/AbstractCommandProcessor.h"
#include "LocalPlayerBoardView.h"
#include "CustomMacros.h"

USING_NS_CC;

class GameBoardView : public Node
{
private:
    GameState& m_gameState;
    AbstractCommandProcessor& m_AbstractCommandProcessor;

    LocalPlayerBoardView* m_localPlayerView;

public:
    GameBoardView(GameState& gameState, AbstractCommandProcessor& commandProcesser): m_gameState{gameState}, m_AbstractCommandProcessor{commandProcesser} {}

    CREATE_FUNC_TWO_PARAM(GameBoardView, GameState&, AbstractCommandProcessor&);
    virtual bool init() override;
};

