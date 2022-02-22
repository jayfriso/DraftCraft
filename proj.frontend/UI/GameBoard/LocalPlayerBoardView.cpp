#include "LocalPlayerBoardView.h"
#include "UIUtils.h"

void LocalPlayerBoardView::initWithModel(Player& viewModel)
{
    AbstractListenerView::initWithModel(viewModel);

    Size contentSize{ 1920, 500 };
    setContentSize(contentSize);

    m_interactableCardContainer = InteractableCardContainer::create();
    m_interactableCardContainer->setContentSize(Size{ 1600, 350 });
    this->addChild(m_interactableCardContainer);
    ui_utils::setAnchoredPosition(m_interactableCardContainer, AnchorPosition::BottomCenter, Vec2{ 0, 20 });
}

void LocalPlayerBoardView::update(const Player& viewModel)
{
    if (viewModel.tempViewData().hasCardBeenAdded);
    {
        m_interactableCardContainer->addCard(viewModel.cardsInHand().back());
    }
    if (viewModel.tempViewData().hasCardBeenRemoved())
    {
        m_interactableCardContainer->removeCardAtIndex((size_t)viewModel.tempViewData().removedCardIndex);
    }
}
