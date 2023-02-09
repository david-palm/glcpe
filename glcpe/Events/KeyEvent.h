#pragma once

#include <sstream>
#include "Event.h"
#include <map>

class KeyEvent: public Event
{
public:
    inline int getKeyCode() const { return m_KeyCode; }

    EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
protected:
    KeyEvent(int keyCode)
        : m_KeyCode(keyCode)
    {
    }
    int m_KeyCode;

};

class KeyDownEvent : public KeyEvent
{
public:
    KeyDownEvent(int keyCode, bool repeated)
        : KeyEvent(keyCode), m_Repeated(repeated) {}
    inline bool getKeyRepeated(){ return m_Repeated; }

    std::string toString() const override
    {
        std::stringstream stringStream;
        stringStream << "KeyDown Event: " << m_KeyCode << ", repeated: " << m_Repeated;
        return stringStream.str();
    }

    EVENT_CLASS_TYPE(KeyDown)
private:
    bool m_Repeated;
};

class KeyUpEvent : public KeyEvent
{
public:
    KeyUpEvent(int keyCode)
        : KeyEvent(keyCode) {}

    std::string toString() const override
    {
        std::stringstream stringStream;
        stringStream << "KeyUp Event: " << m_KeyCode;
        return stringStream.str();
    }

    EVENT_CLASS_TYPE(KeyUp)
};
