#include "Player.h"

void Player::addCardToHand(const Card* card)
{
    m_cardsInHand.push_back(card);
    m_tempViewData.hasCardBeenAdded = true;
    notifyToUpdate();
}

void Player::removeCardFromHand(size_t index)
{
    m_cardsInHand.erase(m_cardsInHand.begin() + index);
    m_tempViewData.removedCardIndex = index;
    notifyToUpdate();
}

void Player::notifyToUpdate()
{
    DispatcherViewModel<Player>::notifyToUpdate();
    m_tempViewData.resetData();
}
