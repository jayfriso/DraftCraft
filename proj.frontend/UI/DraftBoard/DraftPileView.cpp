#include "DraftPileView.h"
#include "UIUtils.h"
#include "UIConstants.h"

void DraftPileView::setCards(const vector<const Card*>& cards)
{
    size_t cardIndex{ 0 };
    size_t cardCount{ cards.size() };
    bool isOverMaxCards = cardCount > MAX_CARDS_SHOWN;

    m_columnContainer->setVisible(!isOverMaxCards);
    m_overMaxViewContainer->setVisible(isOverMaxCards);

    if (cardCount <= MAX_CARDS_SHOWN)
    {
        float space{ cardCount < 3 ? 5.0f : -85.0f }; // 3 cards onwards, we show stacked up
        for (size_t i = 0; i < MAX_COLUMNS; i++)
        {
            if (cardIndex < cards.size())
            {
                size_t numCardsInColumn{ 0 };
                VerticalLayoutContainer* currentColumn{ m_columns.at(i) };
                currentColumn->setVisible(true);
                for (size_t j = 0; j < MAX_CARDS_IN_COLUMN; j++)
                {
                    auto currentChild = m_cardViews.at(cardIndex);
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
    else
    {
        m_overMaxLabel->setString(std::to_string(cardCount));
    }
}

void DraftPileView::initWithModel(DraftPile& viewModel)
{
    AbstractListenerView::initWithModel(viewModel);

    Size contentSize{ 312, 412 };
    this->setContentSize(contentSize);
    auto bg = UIUtils::createGenericRoundedRect(contentSize, UIConstants::COLOR_LIGHT_ORANGE);
    this->addChild(bg, 0);
    UIUtils::setAnchoredPosition(bg, AnchorPosition::CenterCenter);

    auto selectedOutline = UIUtils::createGenericRoundedRectOutline(contentSize, UIConstants::COLOR_ORANGE);
    this->addChild(selectedOutline, -1);
    UIUtils::setAnchoredPosition(selectedOutline, AnchorPosition::CenterCenter);
    m_nodesToShowWhenSelected.push_back(selectedOutline);

    auto selectedArrow = Sprite::create("ui/draft_board/arrow.png");
    this->addChild(selectedArrow, 2);
    UIUtils::setAnchoredPosition(selectedArrow, AnchorPosition::TopLeft, Vec2::ZERO, std::tuple<bool, Vec2>{true, Vec2{0.5,0.5}});
    m_nodesToShowWhenSelected.push_back(selectedArrow);

    m_columnContainer = HorizontalLayoutContainer::create(10, 372);
    m_columnContainer->setChildAnchorPoint(Vec2(0, 1));
    this->addChild(m_columnContainer, 1);
    UIUtils::setAnchoredPosition(m_columnContainer, AnchorPosition::CenterCenter);
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
            m_cardViews.at(i * MAX_CARDS_IN_COLUMN + j) = card;
        }
    }

    m_overMaxViewContainer = Node::create();
    m_overMaxViewContainer->setContentSize(Size{ 272, 354 });
    this->addChild(m_overMaxViewContainer);
    UIUtils::setAnchoredPosition(m_overMaxViewContainer, AnchorPosition::CenterCenter);
    auto overMaxSprite = Sprite::create("ui/draft_board/over_max_pile.png");
    m_overMaxViewContainer->addChild(overMaxSprite, 0);
    UIUtils::setAnchoredPosition(overMaxSprite, AnchorPosition::TopCenter);
    auto overMaxLabelBg = UIUtils::createGenericRoundedRect(Size{ 140, 104 }, Color3B::WHITE);
    m_overMaxViewContainer->addChild(overMaxLabelBg, 1);
    UIUtils::setAnchoredPosition(overMaxLabelBg, AnchorPosition::BottomRight);
    m_overMaxLabel = Label::createWithTTF("0", UIConstants::FONT_FREDOKA_ONE_REGULAR, 80);
    m_overMaxLabel->setTextColor(Color4B::BLACK);
    overMaxLabelBg->addChild(m_overMaxLabel);
    UIUtils::setAnchoredPosition(m_overMaxLabel, AnchorPosition::CenterCenter);

    setCards(viewModel.cardsInPile());
    toggleSelected(false);
}

void DraftPileView::update(const DraftPile& viewModel)
{
    setCards(viewModel.cardsInPile());
}

void DraftPileView::toggleSelected(bool isSelected)
{
    for (auto nodeToChangeVis : m_nodesToShowWhenSelected)
    {
        nodeToChangeVis->setVisible(isSelected);
    }
}

void DraftPileView::toggleFlipped(bool isFlipped)
{
    size_t cardCount = getViewModel()->cardsInPile().size();

    if (cardCount > MAX_CARDS_SHOWN)
        return;

    for (size_t i = 0; i < cardCount; i++)
    {
        m_cardViews.at(i)->flip(isFlipped);
    }
}
