#include <sstream>
#include "DraftDeckView.h"
#include "../../Utils/UIUtils.h"
#include "UIConstants.h"

const string DraftDeckView::CARDS_LEFT_TEXT{ " Cards Left" };

DraftDeckView::~DraftDeckView()
{
    m_draftDeck.removeListener(*this);
}

bool DraftDeckView::init()
{
    if (!Node::init())
        return false;
    this->setContentSize(Size(250, 400));

    auto deckSprite = Sprite::create("ui/draft_board/draft_deck.png");
    UIUtils::setAnchoredPosition(deckSprite, AnchorPosition::TopCenter);
    this->addChild(deckSprite);

    auto cardCountLabelBg = UIUtils::createGenericRoundedRect(Size(202, 54), Color3B::WHITE);
    UIUtils::setAnchoredPosition(cardCountLabelBg, AnchorPosition::BottomCenter);
    this->addChild(cardCountLabelBg);

    string cardCountText = std::to_string(m_draftDeck.cardsLeft()) + CARDS_LEFT_TEXT;
    auto cardCountLabel = Label::createWithTTF(cardCountText, UIConstants::FONT_FREDOKA_ONE_REGULAR, 26);
    UIUtils::setAnchoredPosition(cardCountLabel, AnchorPosition::CenterCenter);
    cardCountLabelBg->addChild(cardCountLabel);

    m_draftDeck.addListener(*this);

    return true;
}

void DraftDeckView::update(const DraftDeck& viewModel)
{
}
