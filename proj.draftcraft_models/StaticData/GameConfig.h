#pragma once
class GameConfig
{
private:
    unsigned int m_deckSize;
    unsigned int m_landCardCount;
public:
    GameConfig(unsigned int deckSize, unsigned int landCardCount) : m_deckSize{ deckSize }, m_landCardCount{ landCardCount } {}
    unsigned int deckSize() const { return m_deckSize; }
    unsigned int landCardCount() const { return m_landCardCount; }
};

