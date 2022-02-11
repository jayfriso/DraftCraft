#include "EventNode.h"

bool EventNode::isWithinBounds(EventMouse* event) const
{
    Vec2 mousePosition = _parent->convertToNodeSpace(Vec2{ event->getCursorX(), event->getCursorY() });
    return getBoundingBox().containsPoint(mousePosition);
}

void EventNode::handleMouseDown(Event* event)
{
    if (!_visible)
        return;

    auto mouseEvent = static_cast<EventMouse*>(event);
    Vec2 mousePosition{ mouseEvent->getCursorX(), mouseEvent->getCursorY() };
    if (m_mouseDownCallback && isWithinBounds(mouseEvent))
    {
        bool stopProp = m_mouseDownCallback(mouseEvent, this);
        
        if (stopProp)
            event->stopPropagation();
    }
}

void EventNode::handleMouseMove(Event* event)
{
    if (!_visible)
        return;

    auto mouseEvent = static_cast<EventMouse*>(event);
    bool newWithinBounds{ isWithinBounds(mouseEvent) };
    bool endProp = false;
    if (m_isCurrentlyWithinBounds != newWithinBounds)
    {
        m_isCurrentlyWithinBounds = newWithinBounds;
        
        if (m_isCurrentlyWithinBounds && m_mouseEnterCallback)
            endProp = m_mouseEnterCallback(mouseEvent, this);
        else if (m_mouseExitCallback)
            endProp = m_mouseExitCallback(mouseEvent, this);
    }
    else if (m_isCurrentlyWithinBounds)
    {
        if (m_mouseMoveOverCallback)
        {
            endProp = m_mouseMoveOverCallback(mouseEvent, this);
        }
    }

    if (endProp)
        mouseEvent->stopPropagation();
}

bool EventNode::init()
{
    if (!Node::init())
        return false;

    m_mouseEventListener = EventListenerMouse::create();
    m_mouseEventListener->onMouseDown = CC_CALLBACK_1(EventNode::handleMouseDown, this);
    m_mouseEventListener->onMouseMove = CC_CALLBACK_1(EventNode::handleMouseMove, this);

    setEventsEnabled(m_isEventsEnabled);

    return true;
}

void EventNode::setEventsEnabled(bool isEnabled)
{
    m_isEventsEnabled = isEnabled;

    if (m_isEventsEnabled)
    {
        _eventDispatcher->addEventListenerWithSceneGraphPriority(m_mouseEventListener, this);
    }
    else
    {
        _eventDispatcher->removeEventListener(m_mouseEventListener);
    }
}