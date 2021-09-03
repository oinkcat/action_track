#ifndef CONSOLEREPORTER_H
#define CONSOLEREPORTER_H

#include <iostream>
#include <Reporter.h>
#include <time.h>

/** Reports message to system console */
class ConsoleReporter : public Reporter
{
    public:
        ConsoleReporter();
        virtual ~ConsoleReporter();

        void report(wstring name, wstring message) override;

    protected:

    private:
};

#endif // CONSOLEREPORTER_H
