#ifndef CONSTANTS_HPP_INCLUDED
#define CONSTANTS_HPP_INCLUDED

#include <string>

/**
* \file constants.hpp
* \brief Contains all the preprocessor definitions
*/

/**
* \addtogroup client
* @{
*/

#define WINDOW_HEIGHT 600 ///< Height of the game window in pixels

#define WINDOW_WIDTH 1067 ///< Width of the window in pixels

/// @}

/**
* \addtogroup both
* @{
*/

#define OLD_EXPERIENCE_TO_LEVEL ExponentialFunction(true, 0.9996, 11485.0, 100.0, 0.0, 4000.0) ///< Function converting the number of experience points to the level
#define EXPERIENCE_TO_LEVEL ExponentialFunction(true, 0.99996, 114900.0, 100.1, 0.0, 40000.0) ///< New function to convert the experience to the level (Still waiting for approval)

#define STRENGTH_TO_ATTACK_FACTOR ThirdPowerFunction(1, 0.00275, -0.000000625) ///< Function converting entities' strength into attack factor

#define STRENGTH_TO_STAMINA ThirdPowerFunction(0, 0.1, -0.000011) ///< Function converting entities' strength into stamina

#define WISDOM_TO_ATTACK_FACTOR ThirdPowerFunction(1, 0.00275, -0.000000625) ///< Function converting entities' wisdom into attack factor

#define WISDOM_TO_MANA ThirdPowerFunction(0, 0.4, -0.0001) ///< Function converting entities' wisdom into mana

#define TOUGHNESS_TO_ATTACK_REDUCTION ThirdPowerFunction(1, -0.0009, 0.000000225) ///< Function converting entities' toughness into attack reduction

#define TOUGHNESS_TO_LIFE ThirdPowerFunction(0, 8.0/30.0, -2.0/30000.0, 0, 2000) ///< Function converting entities' toughness into life

#define MENTAL_RESISTANCE_TO_ATTACK_REDUCTION ThirdPowerFunction(1, -0.0009, 0.000000225) ///< Function converting entities' mental resistance into attack reduction

#define MENTAL_RESISTANCE_TO_LIFE ThirdPowerFunction(0, 4.0/30.0, -1.0/30000.0, 0, 2000) ///< Function converting entities' mental resistance into life


/// @}

/**
* \addtogroup client
* @{
*/

/**
* 	\brief Lists all possible ways to control a team during fights
*/

enum Controls
{
	KEYBOARD, ///< Controlled by keyboard
	CONTROLLER, ///< Controlled by a gamepad
	AI, ///< Controlled by the AI
	ONLINE, ///< Actions received from online
	FROM_FILE, ///< Actions read from a file
};

/// @}

/**
* \addtogroup both
* @{
*/

/**
* \brief Function called in case of error
*/

void errorReport(std::string errorMessage, bool isFatal = 1);

void logReport(std::string logMessage, bool hidden = false);

/// @}

#endif // CONSTANTS_HPP_INCLUDED
