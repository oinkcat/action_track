#ifndef WATCHER_H
#define WATCHER_H

#define UNICODE
#define _WIN32_WINNT 0x0610

#include <string>
#include "windows.h"
#include "Reporter.h"

using namespace std;

/** Watches for use activity */
class Watcher
{
public:
    virtual wstring getName() = 0;

    virtual void update() = 0;
    virtual void report(Reporter& reporter) = 0;
    virtual void shutdown() = 0;

protected:

private:
};

#endif // WATCHER_H
