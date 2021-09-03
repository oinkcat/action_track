#include <windows.h>
#include <iostream>
#include <string>
#include <vector>

#include <io.h>
#include <fcntl.h>

#include "ConsoleReporter.h"
#include "WindowsWatcher.h"
#include "InputWatcher.h"

using namespace std;

const int UPDATE_INTERVAL = 1;

const int MIN_REPORT_INTERVAL = 10;
const int DEFAULT_REPORT_INTERVAL = 60;
const int MAX_REPORT_INTERVAL = 120;

ConsoleReporter reporter;

int reportInterval;
vector<Watcher*> watchers;

void reportWatchers()
{
    for(auto* watcher: watchers)
    {
        watcher->report(reporter);
    }

    wcout << endl;
}

void updateWatchers()
{
    static int secondsToReport = reportInterval;

    for(auto* watcher: watchers)
    {
        watcher->update();
    }


    if(--secondsToReport <= 0)
    {
        secondsToReport = reportInterval;

        reportWatchers();
    }
}

void startEventLoop()
{
    UINT_PTR timerId = SetTimer(NULL, 0, UPDATE_INTERVAL * 1000, NULL);

    MSG msg;
    while(GetMessage(&msg, NULL, 0, 0))
    {
        if(msg.message == WM_TIMER)
        {
            updateWatchers();
        }

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    KillTimer(NULL, timerId);
}

void setupWatchers()
{
    watchers = {
        new WindowsWatcher(),
        new InputWatcher()
    };

    wcout << L"* Available watchers:" << endl;

    for(auto* watcher: watchers)
    {
        wcout << " -" << watcher->getName() << endl;
    }
    wcout << "* Report interval: " << reportInterval << "s" << endl << endl;
}

int parseReportIntervalParam(int argc, char** argv)
{
    if(argc > 1)
    {
        int paramValue = std::stoi(argv[1]);

        return (paramValue >= MIN_REPORT_INTERVAL) &&
               (paramValue <= MAX_REPORT_INTERVAL)
               ? paramValue
               : DEFAULT_REPORT_INTERVAL;
    }
    else
    {
        return DEFAULT_REPORT_INTERVAL;
    }
}

int main(int argc, char** argv)
{
    setmode(_fileno(stdout), _O_U16TEXT);
    setmode(_fileno(stdin), _O_U16TEXT);
    setmode(_fileno(stderr), _O_U16TEXT);

    reportInterval = parseReportIntervalParam(argc, argv);

    wcout << L"Actions tracker v.0.1. LOL." << endl;

    setupWatchers();

    // Loop
    startEventLoop();

    return 0;
}
