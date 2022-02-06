#include "DraftBoardView.h"
#include "UIConstants.h"
#include "UIUtils.h"
#include "DraftPileView.h"
#include "HorizontalLayoutContainer.h"
#include "../CardView.h"

USING_NS_CC;
using namespace ui;

const float DraftBoardView::WIDTH{ 1880 };

void DraftBoardView::updateDraftingState(const DraftBoard& viewModel)
{
    m_opponentPlayerContainer->setVisible(viewModel.isDrafting() && viewModel.draftingPlayerIndex() != m_localPlayerIndex);
    m_localPlayerContainer->setVisible(viewModel.isDrafting() && viewModel.draftingPlayerIndex() == m_localPlayerIndex);
    if (m_localPlayerContainer->isVisible())
    {
        m_draftOptionsContainer->clearCards();
        for (auto card : viewModel.getCurrentPileConst().cardsInPile())
        {
            if (card != nullptr)
                m_draftOptionsContainer->addCard(*card);
        }
    }
}

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
    for (size_t i = 0; i < DraftBoard::getNumPiles(); i++)
    {
        auto pile = DraftPileView::create();
        pile->initWithModel(viewModel.piles().at(i));
        topContainer->addChild(pile);
    }
    UIUtils::setAnchoredPosition(topContainer, AnchorPosition::TopCenter, Vec2(0, -40));

    m_localPlayerContainer = UIUtils::createGenericRoundedRect(Size{ 1750, 490 }, UIConstants::COLOR_GREY);
    this->addChild(m_localPlayerContainer);
    UIUtils::setAnchoredPosition(m_localPlayerContainer, AnchorPosition::BottomRight, Vec2{ -20, 20 });
    m_draftOptionsContainer = InteractableCardContainer::create();
    m_draftOptionsContainer->setContentSize(Size{ 1710, 430 }); // TODO : X should be 1275
    m_localPlayerContainer->addChild(m_draftOptionsContainer);
    UIUtils::setAnchoredPosition(m_draftOptionsContainer, AnchorPosition::CenterLeft, Vec2{ 20, 0 });
    m_localPlayerContainer->setVisible(false);
    
    m_opponentPlayerContainer = UIUtils::createGenericRoundedRect(Size{ 1514, 292 }, UIConstants::COLOR_MID_BLUE);
    this->addChild(m_opponentPlayerContainer);
    UIUtils::setAnchoredPosition(m_opponentPlayerContainer, AnchorPosition::BottomCenter, Vec2{ 0, 120 });
    m_opponentPlayerContainer->setVisible(false);

    updateDraftingState(viewModel);
}

void DraftBoardView::update(const DraftBoard& viewModel)
{
    // update the view here
}
