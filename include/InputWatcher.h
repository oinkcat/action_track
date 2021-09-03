#ifndef INPUTWATCHER_H
#define INPUTWATCHER_H

#include <Watcher.h>

/** Watches for mouse and keyboard input */
class InputWatcher : public Watcher
{
    public:
        InputWatcher();
        virtual ~InputWatcher();

        wstring getName() { return L"Input"; }

        void update();
        void report(Reporter& reporter);
        void shutdown();

    private:
        void setupHooks();
        static LRESULT __stdcall callback(int nCode, WPARAM wParam, LPARAM lParam);
        void removeHooks();

        HHOOK hKeyHook;
        HHOOK hMouseHook;

        static bool mouseMoved;
        static bool keysPressed;

        POINT prevMousePos;
};

#endif // INPUTWATCHER_H
