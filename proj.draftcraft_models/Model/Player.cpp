#include "Player.h"

void Player::AddCardToHand(const Card* card)
{
    m_cardsInHand.push_back(card);
    flagViewDirty();
}