#include "DraftPileView.h"
#include "UIUtils.h"
#include "UIConstants.h"

void DraftPileView::setCards(const vector<const Card*>& cards)
{
    size_t cardIndex{ 0 };
    for (size_t i = 0; i < MAX_COLUMNS; i++)
    {
        if (cardIndex < cards.size())
        {
            size_t numCardsInColumn{ 0 };
            Node* currentColumn{ m_columns.at(i) };
            currentColumn->setVisible(true);
            Vector<Node*>& currentChildren{ currentColumn->getChildren() };
            for (size_t j = 0; j < MAX_CARDS_IN_COLUMN; j++)
            {
                Node* currentChild{ currentChildren.at(j) };
                if (cardIndex < cards.size())
                {
                    const Card* card{ cards.at(cardIndex) };
                    currentChild->setVisible(true);
                    numCardsInColumn++;
                }
                else
                {
                    currentChild->setVisible(false);
                }
                cardIndex++;
            }
            float spacing{ numCardsInColumn < 3 ? 5.0f : -85.0f };
            UIUtils::distributeChildrenVertical(currentColumn, spacing, 132);
            UIUtils::setAnchoredPosition(currentColumn, AnchorPosition::CenterCenter);
        }
        else
        {
            m_columns.at(i)->setVisible(false);
        }
    }
    UIUtils::distributeChildrenHorizontal(m_columnContainer, 10, 372);
    UIUtils::setAnchoredPosition(m_columnContainer, AnchorPosition::CenterCenter);
}

void DraftPileView::initWithModel(DraftPile& viewModel)
{
    this->setContentSize(Size(312, 412));
    auto bg = UIUtils::createGenericRoundedRect(this->getContentSize(), UIConstants::COLOR_LIGHT_ORANGE);
    this->addChild(bg, 0);
    UIUtils::setAnchoredPosition(bg, AnchorPosition::CenterCenter);

    m_columnContainer = Node::create();
    this->addChild(m_columnContainer, 1);
    for (size_t i = 0; i < MAX_COLUMNS; i++)
    {
        Node* currentColumn = Node::create();
        m_columns.at(i) = currentColumn;
        m_columnContainer->addChild(currentColumn);
        for (size_t j = 0; j < MAX_CARDS_IN_COLUMN; j++)
        {
            auto card = Sprite::create("ui/card/card_back.png");
            card->setContentSize(Size(132, 182));
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
