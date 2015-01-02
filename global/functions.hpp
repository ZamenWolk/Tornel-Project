#ifndef GLOBAL_FUNCTIONS_HPP
#define GLOBAL_FUNCTIONS_HPP

#include <iostream>
#include <ctime>

time_t secondsAheadOfGMT();

void errorReport(std::string errorMessage, bool isFatal = true);

void logReport(std::string logMessage, bool hidden = true);

#endif