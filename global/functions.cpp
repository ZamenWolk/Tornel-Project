#include <time.h>
#include <fstream>

#include "functions.hpp"
#include "define.hpp"

using namespace std;

time_t secondsAheadOfGMT()
{
    time_t currentTime, utcTime, localTime;
    tm utcTM, localTM;

    time(&currentTime);
    utcTM = *gmtime(&currentTime);

    time(&currentTime);
    localTM = *localtime(&currentTime);

    utcTime = mktime(&utcTM);
    localTime = mktime(&localTM);

    return (time_t)difftime(localTime, utcTime);
}

void errorReport(string errorMessage, bool isFatal)
{
    time_t    rawtime;
    struct tm *timeinfo;
    char      buffer[100];
    ofstream  errlog("errors.log", ios::app);

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, 100, "[%d/%m/%y %H:%M:%S]", timeinfo);

#ifdef DEBUG
    cerr << buffer << " " << errorMessage << endl;
#endif
    errlog << buffer << " " << errorMessage << endl;

    if (isFatal)
        exit(EXIT_FAILURE);
}

void logReport(string logMessage, bool hidden)
{
    time_t    rawtime;
    struct tm *timeinfo;
    char      buffer[100];
    ofstream  eventlog("events.log", ios::app);

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, 100, "[%d/%m/%y %H:%M:%S]", timeinfo);

#ifndef DEBUG
	if (!hidden)
#endif
    cout << logMessage << endl;
    eventlog << buffer << "[" << SOFT << "] " << logMessage << endl;
}