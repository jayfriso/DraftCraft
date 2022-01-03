#include "DraftBoard.h"
#include "../UIConstants.h"

const float DraftBoard::WIDTH{ 1880 };

bool DraftBoard::init()
{
    if (!Node::init())
        return false;

    this->setContentSize(Size(WIDTH, UIConstants::DRAFT_BOARD_HEIGHT));

    auto draftDrawerBg = Sprite::create("ui/common/rounded_rect.png");
    draftDrawerBg->setCenterRectNormalized(Rect(Vec2(0.2, 0.2), Size(0.6, 0.6)));
    draftDrawerBg->setContentSize(Size(WIDTH, UIConstants::DRAFT_BOARD_HEIGHT));
    draftDrawerBg->setPositionNormalized(Vec2(0.5f, 0.5f));
    draftDrawerBg->setColor(UIConstants::COLOR_GREY);
    this->addChild(draftDrawerBg, 0);

    return true;
}