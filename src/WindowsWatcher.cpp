#include "WindowsWatcher.h"

WindowsWatcher::WindowsWatcher()
{
    this->update();
}

WindowsWatcher::~WindowsWatcher()
{
    //dtor
}

void WindowsWatcher::update()
{
    hCurrentWindow = GetForegroundWindow();
}

void WindowsWatcher::report(Reporter& reporter)
{
    wchar_t title[WND_TITLE_LENGTH];
    GetWindowTextW(hCurrentWindow, title, WND_TITLE_LENGTH);

    wstring titleStr(title);
    reporter.report(getName(), title);
}

void WindowsWatcher::shutdown()
{

}
