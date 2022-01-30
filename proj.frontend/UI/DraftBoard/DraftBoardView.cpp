#include "DraftBoardView.h"
#include "UIConstants.h"
#include "UIUtils.h"
#include "DraftPileView.h"
#include "HorizontalLayoutContainer.h"

USING_NS_CC;
using namespace ui;

const float DraftBoardView::WIDTH{ 1880 };

void DraftBoardView::initWithModel(DraftBoard& viewModel)
{
    AbstractListenerView::initWithModel(viewModel);

    this->setContentSize(Size(WIDTH, UIConstants::DRAFT_BOARD_HEIGHT));

    auto draftBoardBg = UIUtils::createGenericRoundedRect(Size(WIDTH, UIConstants::DRAFT_BOARD_HEIGHT), UIConstants::COLOR_GREY);
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
}

void DraftBoardView::update(const DraftBoard& viewModel)
{
    // update the view here
}
