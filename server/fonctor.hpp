#ifndef FONCTOR_HPP_INCLUDED
#define FONCTOR_HPP_INCLUDED

/**
*   \file fonctor.hpp
*   \brief Contains all the functors of the program
*/

#include <SFML/Network.hpp>
#include <vector>
#include <functional>

/**
* \addtogroup server
* @{
*/

/**
*   \brief Input thread functor. Creates a prompt for the user to type in commands
*/

class inputFonctor
{
public:

	/**
	*   \param[in] subservers Subservers concerned by the commands typed
	*   \param[in] stopServer Reference to the main thread's stopServer variable
	*/

	inputFonctor(std::vector<FightSubserver *> *subservers, bool &stopServer) :
			subservers(subservers), stopServer(stopServer)
	{

	}

	/**
	*   \brief Function of the functor
	*/

	void operator()()
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
				int servNumber(0);
				std::cin >> servNumber;

				if (servNumber > 0 && servNumber <= subservers->size())
				{
					subservers->operator[](servNumber - 1)->reset();
					std::cout << "Server #" << servNumber << " was succesfully reset" << std::endl;
				}
				else
				{
					std::cout << "This is not a correct number" << std::endl;
				}
			}
			else
			{
				std::cout << "This is not an existing command" << std::endl;
			}
		}
	}

private:

	std::vector<FightSubserver *> *subservers; ///< Subservers concerned by the commands typed
	bool                          &stopServer; ///< Reference to the main thread's stopping server variable
};

/// @}

#endif // FONCTOR_HPP_INCLUDED
