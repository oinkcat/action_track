#ifndef REPORTER_H
#define REPORTER_H

#include <string>

using namespace std;

/** Reports watchers state */
class Reporter
{
public:
    virtual void report(wstring name, wstring message) = 0;

    virtual ~Reporter() = default;
};

#endif // REPORTER_H
