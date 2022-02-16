#include "EventNode.h"

void EventNode::resetMouseStateVariables()
{
    m_isCurrentlyWithinBounds = false;
    m_isMouseDown = false;
}

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
    if (!m_isMouseDown)
        m_firstMouseDownPos = Vec2{ mouseEvent->getCursorX(), mouseEvent->getCursorY() };
    m_isMouseDown = true;

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

void EventNode::handleMouseUp(Event* event)
{
    if (!_visible || !m_isMouseDown)
        return;

    m_isMouseDown = false;

    auto mouseEvent = static_cast<EventMouse*>(event);

    auto mouseUpPos = Vec2{ mouseEvent->getCursorX(), mouseEvent->getCursorY() };
    float distance = mouseUpPos.distance(m_firstMouseDownPos);
    if (distance > MAX_CLICK_DISTANCE)
        return;

    if (m_mouseClickCallback && isWithinBounds(mouseEvent))
    {
        bool endProp = m_mouseClickCallback(mouseEvent, this);
        if (endProp)
            mouseEvent->stopPropagation();
    }
}

bool EventNode::init()
{
    if (!Node::init())
        return false;

    setEventsEnabled(m_isEventsEnabled);

    return true;
}

void EventNode::setVisible(bool visible)
{
    if (!visible)
        resetMouseStateVariables();
    Node::setVisible(visible);
}

void EventNode::setEventsEnabled(bool isEnabled)
{
    m_isEventsEnabled = isEnabled;

    if (m_isEventsEnabled && m_mouseEventListener == nullptr)
    {
        m_mouseEventListener = EventListenerMouse::create();
        m_mouseEventListener->retain();
        m_mouseEventListener->onMouseDown = CC_CALLBACK_1(EventNode::handleMouseDown, this);
        m_mouseEventListener->onMouseMove = CC_CALLBACK_1(EventNode::handleMouseMove, this);
        m_mouseEventListener->onMouseUp = CC_CALLBACK_1(EventNode::handleMouseUp, this);

        _eventDispatcher->addEventListenerWithSceneGraphPriority(m_mouseEventListener, this);
    }
    else if (!m_isEventsEnabled && m_mouseEventListener != nullptr)
    {
        _eventDispatcher->removeEventListener(m_mouseEventListener);
        m_mouseEventListener->release();
        m_mouseEventListener = nullptr;
        resetMouseStateVariables();
    }
}