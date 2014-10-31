#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <fstream>
#include <iostream>

#include "Index.hpp"
#include "AIControlledEntity.hpp"

using namespace std;

IndexesIndex indexes;

sf::Clock mainClock;

void errorReport(string errorMessage, bool isFatal)
{
	time_t rawtime;
	struct tm *timeinfo;
	char buffer [100];
	string output("");
	ofstream errlog("errlog.txt", ios::app);

    //Creates the time string
	time (&rawtime);
	timeinfo = localtime(&rawtime);
	strftime (buffer,100,"[%d/%m/%y %H:%M]",timeinfo);

    //Creates the error message string
	output = " ";
	output += errorMessage;

    //Prints the strings in the console and the error log file
	cerr << buffer << output << endl;
	errlog << buffer << output << endl;

    if (isFatal)
        exit(EXIT_FAILURE);
}
