#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <windows.h>
#include <list>
#include "Keys.h"

#define SHIFT (1 << 1)
#define CTRL (1 << 2)
#define ALT (1 << 3)

class KeyboardState
{
    public:
        KeyboardState();
        bool IsKeyDown(BYTE keyValue);
        bool IsKeyUp(BYTE keyValue);
        std::list<BYTE> GetPressedKeys();
        int Modifiers();
        void _setKeyData(BYTE *data);
        BYTE* _getKeyData();
        virtual ~KeyboardState();
        bool operator== (KeyboardState& b) const;
    protected:
        BYTE keyData[256];
};

class Keyboard
{
    public:
        Keyboard();
        static KeyboardState GetState();
        virtual ~Keyboard();
    protected:
    private:
};

#endif // KEYBOARD_H
