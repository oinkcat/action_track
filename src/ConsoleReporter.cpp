#include "ConsoleReporter.h"

ConsoleReporter::ConsoleReporter()
{
    //ctor
}

ConsoleReporter::~ConsoleReporter()
{
    //dtor
}

void ConsoleReporter::report(wstring name, wstring message)
{
    time_t now;
    time(&now);

    wcout << "[" << now << ", " << name << "] " << message << endl;
}
