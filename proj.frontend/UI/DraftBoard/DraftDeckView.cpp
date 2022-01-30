#include <sstream>
#include "DraftDeckView.h"
#include "../../Utils/UIUtils.h"
#include "UIConstants.h"

const string DraftDeckView::CARDS_LEFT_TEXT{ " Cards Left" };

void DraftDeckView::setNumCardsLeft(int numCardsLeft)
{
    m_cardsLeftLabel->setString(std::to_string(numCardsLeft) + CARDS_LEFT_TEXT);
}

void DraftDeckView::initWithModel(DraftDeck& viewModel)
{
    IListenerView::initWithModel(viewModel);

    this->setContentSize(Size(250, 400));

    auto deckSprite = Sprite::create("ui/draft_board/draft_deck.png");
    UIUtils::setAnchoredPosition(deckSprite, AnchorPosition::TopCenter);
    this->addChild(deckSprite);

    auto cardCountLabelBg = UIUtils::createGenericRoundedRect(Size(202, 54), Color3B::WHITE);
    UIUtils::setAnchoredPosition(cardCountLabelBg, AnchorPosition::BottomCenter);
    this->addChild(cardCountLabelBg);

    string numCardsLeftString = std::to_string(viewModel.cardsLeft()) + CARDS_LEFT_TEXT;
    m_cardsLeftLabel = Label::createWithTTF(numCardsLeftString, UIConstants::FONT_FREDOKA_ONE_REGULAR, 26);
    UIUtils::setAnchoredPosition(m_cardsLeftLabel, AnchorPosition::CenterCenter);
    cardCountLabelBg->addChild(m_cardsLeftLabel);
}

void DraftDeckView::update(const DraftDeck& viewModel)
{
    setNumCardsLeft(viewModel.cardsLeft());
}


