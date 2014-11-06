#include "fonctor.hpp"

using namespace std;

InputFonctor::InputFonctor(std::vector<FightSubserver *> *subservers, bool &stopServer):
					subservers(subservers), stopServer(stopServer)
{

}

void InputFonctor::operator()()
{
	std::string input("");

	while (!stopServer)
	{
		std::cin >> input;

		if (input == "stop")
		{
			stopServer = true;
		}
		else if (input == "reset")
		{
			unsigned int servNumber(0);
			std::cin >> servNumber;

			if (servNumber != 0 && servNumber <= subservers->size())
			{
				subservers->operator[](servNumber - 1)->reset();
				string message("Server #");
				message +=  servNumber;
				message += " was succesfully reset";
				logReport(message);
			}
			else
			{
				logReport("This is not a correct number");
			}
		}
		else
		{
			logReport("This is not an existing command");
		}
	}
}