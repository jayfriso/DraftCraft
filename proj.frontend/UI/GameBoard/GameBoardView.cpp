#include "GameBoardView.h"
#include "UIUtils.h"

bool GameBoardView::init()
{
    if (!Node::init())
        return false;

    m_localPlayerView = LocalPlayerBoardView::create();
    m_localPlayerView->initWithModel(m_gameState.playerAtIndex(m_gameState.localPlayerIndex()));
    this->addChild(m_localPlayerView);
    ui_utils::setAnchoredPosition(m_localPlayerView, AnchorPosition::BottomCenter);

    return true;
}
