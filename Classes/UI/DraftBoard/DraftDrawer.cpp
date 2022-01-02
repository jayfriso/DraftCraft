#include "DraftDrawer.h"

bool DraftDrawer::init()
{
    if (!Node::init())
        return false;

    auto mySprite = Sprite::create("ui/draft_board/draft_drawer_bg.png");
    this->addChild(mySprite, 0);
    return true;
}
