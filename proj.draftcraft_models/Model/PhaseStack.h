#pragma once

#include <vector>
#include "../StaticData/GameConfig.h"

using namespace std;

enum class PhaseType
{
   Draft,
   Untap,
   FirstMain,
   DeclareAttackers,
   DeclareBlockers,
   Combat,
   SecondMain
};

struct Phase
{
    PhaseType phaseType;
    unsigned int playerIndex;
};

// Forward Declaration
class GameState;

class PhaseStack
{
private:
    const GameConfig& m_gameConfig;
    GameState& m_gameState;

    int m_turnPlayerIndex{-1}; // What players turn is it
    unsigned int m_startingPlayerIndex;
    vector<Phase> m_phaseStack;

    // Fill the stack with the first draft phases
    void fillStartingDraftPhases();
    // Fill the stack with phases for a players turn
    void fillGenericTurnPhases();
    // Modify the gamestate based on entering the given phase
    void modifyGSUponPhaseOnset(const Phase& phase);

public:
    PhaseStack(const GameConfig& gameConfig, GameState& gameState, unsigned int startingPlayerIndex);

    const Phase& getCurrentPhase() const;
    const Phase& proceedToNextPhase();


};

