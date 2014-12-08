#include <SFML/System.hpp>
#include <fstream>
#include <iostream>

#include "IndexesIndex.hpp"
#include "../define.hpp"

using namespace std;
using namespace sf;

IndexesIndex indexes;

Clock mainClock;

void errorReport(string errorMessage, bool isFatal)
{
	time_t    rawtime;
	struct tm *timeinfo;
	char      buffer[100];
	ofstream  errlog("errors.log", ios::app);

	//Creates the time string
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer, 100, "[%d/%m/%y %H:%M:%S]", timeinfo);

	//Prints the strings in the console and the error log file
	#ifndef NDEBUG
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

	//Creates the time string
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer, 100, "[%d/%m/%y %H:%M:%S]", timeinfo);

	//Prints the strings in the console and the event log file

	#ifdef NDEBUG
	if (!hidden)
	#endif
	cout << logMessage << endl;
	eventlog << buffer << "[" << SOFT << "] " << logMessage << endl;
}