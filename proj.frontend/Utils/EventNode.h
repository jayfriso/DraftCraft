#pragma once
#include "cocos2d.h"
#include <functional>
#include "CustomMacros.h"

USING_NS_CC;


class EventNode : public Node
{
private:
    typedef std::function<bool(EventMouse* event, EventNode* target)> MouseCallback;

    static constexpr float MAX_CLICK_DISTANCE = 20;

    EventListenerMouse* m_mouseEventListener;
    MouseCallback m_mouseDownCallback;
    MouseCallback m_mouseClickCallback;
    MouseCallback m_mouseEnterCallback;
    MouseCallback m_mouseExitCallback;
    // Note : not called the frame mouse enter, but all frames after where the mouse is still over the element
    MouseCallback m_mouseMoveOverCallback;

    // Reset variables related to the current state of the mouse. Called when events are disabled or if the view is turned invisible.
    void resetMouseStateVariables();

protected:
    bool m_isEventsEnabled;
    bool m_isCurrentlyWithinBounds;
    Vec2 m_firstMouseDownPos;
    bool m_isMouseDown;

    bool isWithinBounds(EventMouse* event) const;

    virtual void handleMouseDown(Event* event);
    virtual void handleMouseMove(Event* event);
    virtual void handleMouseUp(Event* event);

public:
    EventNode::EventNode(bool isEventEnabled) : 
        m_isEventsEnabled{ isEventEnabled }, 
        m_isCurrentlyWithinBounds{ false },
        m_mouseEventListener {nullptr},
        m_mouseDownCallback{ nullptr },
        m_mouseEnterCallback{nullptr},
        m_mouseExitCallback{ nullptr },
        m_isMouseDown{ false },
        m_firstMouseDownPos{ 0,0 }{}

    virtual bool init() override;
    CREATE_FUNC_ONE_PARAM(EventNode, bool);

    virtual void setVisible(bool visible) override;

    void setEventsEnabled(bool isEnabled);

    void setMouseDownEvent(MouseCallback callback) { m_mouseDownCallback = callback; }
    void clearMouseDownEvent() { m_mouseDownCallback = nullptr; }

    void setMouseEnterEvent(MouseCallback callback) { m_mouseEnterCallback = callback; }
    void clearMouseEnterEvent() { m_mouseEnterCallback = nullptr; }

    void setMouseExitEvent(MouseCallback callback) { m_mouseExitCallback = callback; }
    void clearMouseExitEvent() { m_mouseExitCallback = nullptr; }

    void setMouseMoveOverEvent(MouseCallback callback) { m_mouseMoveOverCallback = callback; }
    void clearMouseMoveEvent() { m_mouseMoveOverCallback = nullptr; }

    void setMouseClickEvent(MouseCallback callback) { m_mouseClickCallback = callback; }
    void clearMouseClickEvent() { m_mouseClickCallback = nullptr; }
};

