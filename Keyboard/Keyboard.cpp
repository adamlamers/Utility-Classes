#include "Keyboard.h"
#include <iostream>

Keyboard::Keyboard()
{
    //ctor
}

KeyboardState Keyboard::GetState()
{
    KeyboardState state;
    BYTE pressedKeys[256];
    for(int i = 0; i < 256; i++)
    {
        if(GetKeyState(i) & (1 << 16))
            pressedKeys[i] = true;
        else
            pressedKeys[i] = false;
    }
    state._setKeyData(pressedKeys);
    return state;
}

Keyboard::~Keyboard()
{
    //dtor
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

KeyboardState::KeyboardState()
{
    memset(&keyData, 0, 256);
}

bool KeyboardState::IsKeyDown(BYTE keyValue)
{
    if(keyData[keyValue] == true)
        return true;
    else
        return false;
}

bool KeyboardState::IsKeyUp(BYTE keyValue)
{
    if(keyData[keyValue] == false)
        return true;
    else
        return false;
}

std::list<BYTE> KeyboardState::GetPressedKeys()
{
    std::list<BYTE> returnValue;
    for(int i = 0; i < 256; i++)
    {
        if(keyData[i] == true)
            returnValue.push_back(i);
    }
    return returnValue;

}

int KeyboardState::Modifiers()
{
    int returnVal = 0;
    if(IsKeyDown(Keys::LSHIFT) || IsKeyDown(Keys::RSHIFT))
        returnVal |= SHIFT;
    if(IsKeyDown(Keys::MENU))
        returnVal |= ALT;
    if(IsKeyDown(Keys::CONTROL))
        returnVal |= CTRL;
    return returnVal;
}

bool KeyboardState::operator== (KeyboardState& b) const
{
    BYTE *data2;
    data2 = b._getKeyData();
    for(int i = 0; i < 256; i++)
    {
        if(keyData[i] != data2[i])
            return false;
    }
    return true;
}

void KeyboardState::_setKeyData(BYTE *data)
{
    memcpy(keyData, data, 256);
}

BYTE* KeyboardState::_getKeyData()
{
    return keyData;
}

KeyboardState::~KeyboardState()
{

}
