#include <ctime>

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