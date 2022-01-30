#include "DraftBoardView.h"
#include "UIConstants.h"
#include "UIUtils.h"

const float DraftBoardView::WIDTH{ 1880 };

void DraftBoardView::initWithModel(DraftBoard& viewModel)
{
    AbstractListenerView::initWithModel(viewModel);

    this->setContentSize(Size(WIDTH, UIConstants::DRAFT_BOARD_HEIGHT));

    auto draftBoardBg = UIUtils::createGenericRoundedRect(Size(WIDTH, UIConstants::DRAFT_BOARD_HEIGHT), UIConstants::COLOR_GREY);
    draftBoardBg->setPositionNormalized(Vec2(0.5f, 0.5f));
    this->addChild(draftBoardBg, 0);

    // Container for deck and piles
    auto topContainer = Node::create();
    topContainer->setContentSize(Size(1418, 435));
    this->addChild(topContainer, 1);
    m_draftDeckView = DraftDeckView::create();
    m_draftDeckView->initWithModel(viewModel.deck());
    topContainer->addChild(m_draftDeckView);
    for (size_t i = 0; i < DraftBoard::getNumPiles(); i++)
    {
        auto pile = UIUtils::createGenericRoundedRect(Size(312, 412), UIConstants::COLOR_LIGHT_ORANGE);
        topContainer->addChild(pile);
    }
    UIUtils::distributeChildrenHorizontal(topContainer);
    UIUtils::setAnchoredPosition(topContainer, AnchorPosition::TopCenter);
}

void DraftBoardView::update(const DraftBoard& viewModel)
{
    // update the view here
}
