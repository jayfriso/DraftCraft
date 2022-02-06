#pragma once
#include "cocos2d.h"
#include <functional>
#include "CustomMacros.h"

USING_NS_CC;


class EventNode : public Node
{
private:
    typedef std::function<bool(EventMouse* event, EventNode* target)> MouseCallback;

    EventListenerMouse* m_mouseEventListener;
    MouseCallback m_mouseDownCallback;
    MouseCallback m_mouseEnterCallback;
    MouseCallback m_mouseExitCallback;

    bool m_isEventsEnabled;
    bool m_isCurrentlyWithinBounds;

    bool isWithinBounds(EventMouse* event) const;

    void handleMouseDown(Event* event);
    void handleMouseMove(Event* event);

public:

    EventNode::EventNode(bool isEventEnabled) : 
        m_isEventsEnabled{ isEventEnabled }, 
        m_isCurrentlyWithinBounds{ false },
        m_mouseDownCallback{ nullptr },
        m_mouseEnterCallback{nullptr},
        m_mouseExitCallback{ nullptr } {}

    virtual bool init() override;
    CREATE_FUNC_ONE_PARAM(EventNode, bool);

    void setEventsEnabled(bool isEnabled);

    virtual void setMouseDownEvent(MouseCallback callback) { m_mouseDownCallback = callback; }
    virtual void clearMouseDownEvent() { m_mouseDownCallback = nullptr; }

    virtual void setMouseEnterEvent(MouseCallback callback) { m_mouseEnterCallback = callback; }
    virtual void clearMouseEnterEvent() { m_mouseEnterCallback = nullptr; }

    virtual void setMouseExitEvent(MouseCallback callback) { m_mouseExitCallback = callback; }
    virtual void clearMouseExitEvent() { m_mouseExitCallback = nullptr; }
};

