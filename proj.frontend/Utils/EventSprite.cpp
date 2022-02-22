#include "EventSprite.h"
#include "UIUtils.h"

bool EventSprite::init()
{
    if (!EventNode::init())
        return false;

    m_defaultSprite = Sprite::create(m_defaultSpritePath);
    if (!m_defaultSprite)
        return false;
    addChild(m_defaultSprite);
    ui_utils::setAnchoredPosition(m_defaultSprite, AnchorPosition::CenterCenter);

    if (!m_downSpritePath.empty())
    {
        m_downSprite = Sprite::create(m_downSpritePath);
        if (!m_downSprite)
            return false;
        addChild(m_downSprite);
        ui_utils::setAnchoredPosition(m_downSprite, AnchorPosition::CenterCenter);
        m_downSprite->setVisible(false);
    }
    else
    {
        m_downSprite = nullptr;
    }


    setContentSize(m_defaultSprite->getContentSize());

    return true;
}

void EventSprite::setContentSize(const Size& size)
{
    Node::setContentSize(size);
    m_defaultSprite->setContentSize(size);
    if (m_downSprite != nullptr)
        m_downSprite->setContentSize(size);
}

void EventSprite::setCenterRectNormalized(const cocos2d::Rect& rect)
{
    m_defaultSprite->setCenterRectNormalized(rect);
    if (m_downSprite != nullptr)
        m_downSprite->setCenterRectNormalized(rect);
}

void EventSprite::handleMouseDown(Event* event)
{
    auto mouseEvent = static_cast<EventMouse*>(event);
    if (_visible && !m_isMouseDown && m_downSprite != nullptr && isWithinBounds(mouseEvent))
    {
        m_defaultSprite->setVisible(false);
        m_downSprite->setVisible(true);
    }

    EventNode::handleMouseDown(event);
}

void EventSprite::handleMouseUp(Event* event)
{
    if (_visible && !m_defaultSprite->isVisible())
    {
        m_defaultSprite->setVisible(true);
        m_downSprite->setVisible(false);
    }

    EventNode::handleMouseUp(event);
}
