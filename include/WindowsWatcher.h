#ifndef WINDOWSWATCHER_H
#define WINDOWSWATCHER_H

#include <Watcher.h>

/** Watches currently active windows */
class WindowsWatcher : public Watcher
{
    public:
        WindowsWatcher();
        virtual ~WindowsWatcher();

        wstring getName() { return L"Windows"; }

        void update();
        void report(Reporter& reporter);
        void shutdown();

    private:
        const int WND_TITLE_LENGTH = 300;

        HWND hCurrentWindow;

};

#endif // WINDOWSWATCHER_H
