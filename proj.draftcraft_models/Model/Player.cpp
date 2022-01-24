#include "Player.h"

void Player::addCardToHand(const Card& card)
{
    m_cardsInHand.push_back(card);
    notifyToUpdate();
}