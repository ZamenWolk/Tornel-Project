#ifndef FONCTOR_HPP_INCLUDED
#define FONCTOR_HPP_INCLUDED

/**
* \file fonctor.hpp
* \brief Contains all the functors of the program
*/

#include <SFML/Network.hpp>
#include <vector>
#include <functional>

#include "FightSubserver.hpp"

/**
* \addtogroup server
* @{
*/

/**
* \brief Input thread functor. Creates a prompt for the user to type in commands
*/

class InputFonctor
{
public:

	/**
	* \param[in] subservers Subservers concerned by the commands typed
	* \param[in] stopServer Reference to the main thread's stopServer variable
	*/

	InputFonctor(std::vector<FightSubserver *> *subservers, bool &stopServer);

	/**
	* \brief Function of the functor
	*/

	void operator()();

private:

	std::vector<FightSubserver *> *subservers; ///< Subservers concerned by the commands typed
	bool                          &stopServer; ///< Reference to the main thread's stopping server variable
};

/// @}

#endif // FONCTOR_HPP_INCLUDED
