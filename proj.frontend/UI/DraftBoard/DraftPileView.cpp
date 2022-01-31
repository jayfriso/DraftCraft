#include "DraftPileView.h"
#include "UIUtils.h"
#include "UIConstants.h"
#include "../CardView.h"

void DraftPileView::setCards(const vector<const Card*>& cards)
{
    size_t cardIndex{ 0 };
    float space{ cards.size() < 3 ? 5.0f : -85.0f }; // 3 cards onwards, we show stacked up
    for (size_t i = 0; i < MAX_COLUMNS; i++)
    {
        if (cardIndex < cards.size())
        {
            size_t numCardsInColumn{ 0 };
            VerticalLayoutContainer* currentColumn{ m_columns.at(i) };
            currentColumn->setVisible(true);
            Vector<Node*>& currentChildren{ currentColumn->getChildren() };
            for (size_t j = 0; j < MAX_CARDS_IN_COLUMN; j++)
            {
                CardView* currentChild{ static_cast<CardView*>(currentChildren.at(j)) };
                if (cardIndex < cards.size())
                {
                    const Card* card{ cards.at(cardIndex) };
                    currentChild->setVisible(true);
                    currentChild->setCardData(card);
                    numCardsInColumn++;
                }
                else
                {
                    currentChild->setVisible(false);
                }
                cardIndex++;
            }
            currentColumn->setSpace(space);
            currentColumn->redistribute();
        }
        else
        {
            m_columns.at(i)->setVisible(false);
        }
    }
    m_columnContainer->redistribute();
    UIUtils::setAnchoredPosition(m_columnContainer, AnchorPosition::CenterCenter);
}

void DraftPileView::initWithModel(DraftPile& viewModel)
{
    this->setContentSize(Size(312, 412));
    auto bg = UIUtils::createGenericRoundedRect(this->getContentSize(), UIConstants::COLOR_LIGHT_ORANGE);
    this->addChild(bg, 0);
    UIUtils::setAnchoredPosition(bg, AnchorPosition::CenterCenter);

    m_columnContainer = HorizontalLayoutContainer::create(10, 372);
    m_columnContainer->setAnchorType(HorizontalAnchorType::Top);
    this->addChild(m_columnContainer, 1);
    for (size_t i = 0; i < MAX_COLUMNS; i++)
    {
        VerticalLayoutContainer* currentColumn = VerticalLayoutContainer::create(5.0f, 132);
        m_columns.at(i) = currentColumn;
        m_columnContainer->addChild(currentColumn);
        for (size_t j = 0; j < MAX_CARDS_IN_COLUMN; j++)
        {
            auto card = CardView::create(nullptr);
            card->resize(182);
            card->flip(false);
            currentColumn->addChild(card);
        }
    }
    UIUtils::setAnchoredPosition(m_columnContainer, AnchorPosition::CenterCenter);
    setCards(viewModel.cardsInPile());
}

void DraftPileView::update(const DraftPile& viewModel)
{
    setCards(viewModel.cardsInPile());
}
