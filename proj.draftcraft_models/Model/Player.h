#pragma once
#include <string>
#include <vector>
#include "../StaticData/Card.h"
#include "../ViewModel/DispatcherViewModel.h"

using namespace std;

class Player : public DispatcherViewModel
{
private:
    string m_userName;
    unsigned int m_playerIndex;
    vector<const Card*> m_cardsInHand;
public:
    Player(string userName, unsigned int playerIndex) : m_userName{userName}, m_playerIndex {playerIndex} {}

    const vector<const Card*>& cardsInHand() const { return m_cardsInHand; }

    void AddCardToHand(const Card* card);
};

