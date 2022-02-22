#pragma once
#include <string>
#include <vector>
#include "../StaticData/Card.h"
#include "../ViewModel/DispatcherViewModel.h"

using namespace std;

class Player : public DispatcherViewModel<Player>
{
public:
    struct TempViewData
    {
        bool hasCardBeenAdded{ false };

        int removedCardIndex{ -1 };
        inline bool hasCardBeenRemoved() const { return removedCardIndex > -1; }

        void resetData()
        {
            hasCardBeenAdded = false;
            removedCardIndex = -1;
        }
    };

private:
    string m_id;
    unsigned int m_playerIndex;
    vector<const Card*> m_cardsInHand;

    TempViewData m_tempViewData;

public:
    Player(string id, unsigned int playerIndex) : m_id{id}, m_playerIndex {playerIndex} {}

    const vector<const Card*>& cardsInHand() const { return m_cardsInHand; }
    const TempViewData& tempViewData() const { return m_tempViewData; }

    void addCardToHand(const Card* card);
    void removeCardFromHand(size_t index);

    virtual void notifyToUpdate() override;
};

