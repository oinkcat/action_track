#include "InputWatcher.h"

bool InputWatcher::mouseMoved = false;
bool InputWatcher::keysPressed = false;

InputWatcher::InputWatcher()
{
    this->setupHooks();
    this->update();
}

InputWatcher::~InputWatcher()
{
    //dtor
}

void InputWatcher::setupHooks()
{
    hKeyHook = SetWindowsHookEx(WH_KEYBOARD_LL, callback, NULL, 0);
    hMouseHook = SetWindowsHookEx(WH_MOUSE_LL, callback, NULL, 0);
}

LRESULT __stdcall InputWatcher::callback(int nCode, WPARAM wParam, LPARAM lParam)
{
    if(wParam == WM_KEYDOWN)
    {
        keysPressed = true;
    }
    else if((wParam == WM_MOUSEWHEEL) ||
            (wParam == WM_LBUTTONDOWN) ||
            (wParam == WM_RBUTTONDOWN))
    {
        mouseMoved = true;
    }

    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

void InputWatcher::removeHooks()
{
    UnhookWindowsHookEx(hKeyHook);
    UnhookWindowsHookEx(hMouseHook);
}

void InputWatcher::update()
{
    POINT currentMousePos;
    GetCursorPos(&currentMousePos);

    if((currentMousePos.x != prevMousePos.x) ||
       (currentMousePos.y != prevMousePos.y))
    {
        mouseMoved = true;

        prevMousePos.x = currentMousePos.x;
        prevMousePos.y = currentMousePos.y;
    }
}

void InputWatcher::report(Reporter& reporter)
{
    if(mouseMoved && keysPressed)
    {
        reporter.report(getName(), L"Mouse and keyboard activity");
    }
    else if(mouseMoved)
    {
        reporter.report(getName(), L"Mouse moved");
    }
    else if(keysPressed)
    {
        reporter.report(getName(), L"Keys pressed on keyboard");
    }
    else
    {
        reporter.report(getName(), L"No input activity");
    }

    mouseMoved = false;
    keysPressed = false;
}

void InputWatcher::shutdown()
{
    this->removeHooks();
}
