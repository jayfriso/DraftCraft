#include "DraftBoardView.h"
#include "UIConstants.h"
#include "UIUtils.h"
#include "HorizontalLayoutContainer.h"
#include "../CardView.h"
#include "CommandSystem/Commands/DraftAtIndexCommand.h"
#include "CommandSystem/Commands/DraftSkipPileCommand.h"
#include "ViewLogicError.h"

USING_NS_CC;
using namespace ui;

const float DraftBoardView::WIDTH{ 1880 };

void DraftBoardView::initWithModel(DraftBoard& viewModel)
{
    AbstractListenerView::initWithModel(viewModel);

    this->setContentSize(Size(WIDTH, UIConstants::DRAFT_BOARD_HEIGHT));

    auto draftBoardBg = UIUtils::createGenericRoundedRect(Size(WIDTH, UIConstants::DRAFT_BOARD_HEIGHT), UIConstants::COLOR_LIGHT_BLUE);
    draftBoardBg->setPositionNormalized(Vec2(0.5f, 0.5f));
    this->addChild(draftBoardBg, 0);

    // Container for deck and piles
    auto topContainer = HorizontalLayoutContainer::create(100, 435);
    this->addChild(topContainer, 1);
    m_draftDeckView = DraftDeckView::create();
    m_draftDeckView->initWithModel(viewModel.deck());
    topContainer->addChild(m_draftDeckView);
    for (size_t i = 0; i < DraftBoard::NUM_PILES; i++)
    {
        auto pile = DraftPileView::create();
        pile->initWithModel(viewModel.piles().at(i));
        topContainer->addChild(pile);
        m_draftPileViews.at(i) = pile;
    }
    UIUtils::setAnchoredPosition(topContainer, AnchorPosition::TopCenter, Vec2(0, -40));

    m_localPlayerContainer = UIUtils::createGenericRoundedRect(Size{ 1750, 490 }, UIConstants::COLOR_GREY);
    this->addChild(m_localPlayerContainer, 2);
    UIUtils::setAnchoredPosition(m_localPlayerContainer, AnchorPosition::BottomRight, Vec2{ -20, 20 });
    m_draftOptionsContainer = InteractableCardContainer::create();
    m_draftOptionsContainer->setContentSize(Size{ 1275, 430 });
    m_localPlayerContainer->addChild(m_draftOptionsContainer);
    UIUtils::setAnchoredPosition(m_draftOptionsContainer, AnchorPosition::CenterLeft, Vec2{ 20, 0 });
    m_draftOptionsContainer->setCardMouseClickCallback(CC_CALLBACK_3(DraftBoardView::onCardClicked, this));

    m_skipButton = UIUtils::createGenericOrangeButton(Size{ 321, 289 });
    m_localPlayerContainer->addChild(m_skipButton);
    UIUtils::setAnchoredPosition(m_skipButton, AnchorPosition::CenterRight, Vec2{ -50, 0 });
    m_skipButtonIcon = Sprite::create("ui/draft_board/take_from_top.png");
    m_skipButton->addChild(m_skipButtonIcon);
    UIUtils::setAnchoredPosition(m_skipButtonIcon, AnchorPosition::BottomCenter, Vec2{ 0,110 });
    m_skipButtonLabel = Label::createWithTTF("Take From Top", UIConstants::FONT_FREDOKA_ONE_REGULAR, 32);
    m_skipButtonLabel->setTextColor(Color4B::BLACK);
    m_skipButton->addChild(m_skipButtonLabel);
    UIUtils::setAnchoredPosition(m_skipButtonLabel, AnchorPosition::BottomCenter, Vec2{ 0,40 });
    m_skipButton->setMouseClickEvent(CC_CALLBACK_1(DraftBoardView::onSkipButtonClicked, this));
    
    m_opponentPlayerContainer = UIUtils::createGenericRoundedRect(Size{ 1514, 292 }, UIConstants::COLOR_MID_BLUE);
    this->addChild(m_opponentPlayerContainer, 2);
    UIUtils::setAnchoredPosition(m_opponentPlayerContainer, AnchorPosition::BottomCenter, Vec2{ 0, 120 });

    update(viewModel);
}

void DraftBoardView::update(const DraftBoard& viewModel)
{
    bool isDraftingPlayer = viewModel.draftingPlayerIndex() == m_localPlayerIndex;
    m_opponentPlayerContainer->setVisible(viewModel.isDrafting() && !isDraftingPlayer);
    m_localPlayerContainer->setVisible(isDraftingPlayer);
    m_draftOptionsContainer->setEventsEnabled(isDraftingPlayer);

    for (size_t i = 0; i < m_draftPileViews.size(); i++)
    {
        bool isSelectedPile = i == viewModel.currentPileIndex();
        m_draftPileViews.at(i)->toggleSelected(isSelectedPile);
        m_draftPileViews.at(i)->toggleFlipped(isSelectedPile && isDraftingPlayer);
    }

    if (m_localPlayerContainer->isVisible())
    {
        m_draftOptionsContainer->clearCards();
        for (auto card : viewModel.getCurrentPileConst().cardsInPile())
        {
            if (card != nullptr)
                m_draftOptionsContainer->addCard(*card);
        }

        bool isLastPile = viewModel.currentPileIndex() == (DraftBoard::NUM_PILES - 1);
        m_skipButtonIcon->setTexture(isLastPile ? "ui/draft_board/take_from_top.png" : "ui/draft_board/skip_to_next_pile.png");
        m_skipButtonLabel->setString(isLastPile ? "Take From Top" : "Skip To Next Pile");
    }
}

bool DraftBoardView::onCardClicked(EventMouse* mouseEvent, CardView* cardView, size_t cardIndex)
{
    int playerIndex = getViewModel()->draftingPlayerIndex();
    if (playerIndex < 0)
        throw ViewLogicError{ "Mouse down on draft card when model indicates no one is drafting." };
    DraftAtIndexCommand draftAtIndexCommand{ cardIndex, static_cast<unsigned int>(playerIndex) };
    m_commandProcessor.ProcessCommandFromClient(draftAtIndexCommand);
    return true;
}

bool DraftBoardView::onSkipButtonClicked(Ref* buttonRef)
{
    int playerIndex = getViewModel()->draftingPlayerIndex();
    if (playerIndex < 0)
        throw ViewLogicError{ "Skip buton pressed when model indicates no one is drafting." };
    DraftSkipPileCommand skipPileCommand{ static_cast<unsigned int>(playerIndex) };
    m_commandProcessor.ProcessCommandFromClient(skipPileCommand);
    return true;
}
