#pragma once
class GameConfig
{
private:
    static const unsigned int DEFAULT_STARTING_HAND_SIZE{ 7 };

    unsigned int m_deckSize;
    unsigned int m_landCardCount;
    unsigned int m_startingHandSize;
public:
    GameConfig(unsigned int deckSize, unsigned int landCardCount) : m_deckSize{ deckSize }, m_landCardCount{ landCardCount }, m_startingHandSize{ DEFAULT_STARTING_HAND_SIZE } {}
    unsigned int deckSize() const { return m_deckSize; }
    unsigned int landCardCount() const { return m_landCardCount; }
    unsigned int startingHandSize() const { return m_startingHandSize; }
};

