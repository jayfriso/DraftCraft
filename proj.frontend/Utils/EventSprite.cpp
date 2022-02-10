#include "EventSprite.h"
#include "UIUtils.h"

bool EventSprite::init()
{
    if (!EventNode::init())
        return false;

    m_sprite = Sprite::create(m_spritePath);
    if (!m_sprite)
        return false;
    addChild(m_sprite);
    UIUtils::setAnchoredPosition(m_sprite, AnchorPosition::CenterCenter);

    setContentSize(m_sprite->getContentSize());

    return true;
}

void EventSprite::setContentSize(const Size& size)
{
    Node::setContentSize(size);
    m_sprite->setContentSize(size);
}