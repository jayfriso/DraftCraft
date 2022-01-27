#pragma once
#include <string>
#include <vector>
#include "../StaticData/Card.h"
#include "../ViewModel/DispatcherViewModel.h"

using namespace std;

class Player : public DispatcherViewModel<Player>
{
private:
    string m_id;
    unsigned int m_playerIndex;
    vector<const Card*> m_cardsInHand;
public:
    Player(string id, unsigned int playerIndex) : m_id{id}, m_playerIndex {playerIndex} {}

    const vector<const Card*>& cardsInHand() const { return m_cardsInHand; }

    void addCardToHand(const Card* card);
};

