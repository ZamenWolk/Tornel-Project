#ifndef SERVERCLIENTS_HPP_INCLUDED
#define SERVERCLIENTS_HPP_INCLUDED

/**
* \file ServerClients.hpp
* \brief Contains the ServerClient class, as well as ServerClient-related functions
*/

#include <SFML/Network.hpp>

/**
* \addtogroup server
* @{
*/

/**
* \brief Enhanced version of a TCP socket
* \details Has extra functions to know if the socket is connected, and automatic handling of a SocketSelector
*/

class ServerClient : public sf::TcpSocket
{
public:

	ServerClient();

	/**
	* \brief Connects the socket with the socket sent, and adds itself to the SocketSelector if given
	* \param[in] listener Listener to connect the Socket from
	* \param[in] socketSelector SocketSelector to add the socket to
	*/

	void connect(sf::TcpListener &listener, sf::SocketSelector *selector = 0);

	/**
	* \brief Disconnect the Socket
	*/

	void disconnect();

	sf::Socket::Status send(sf::Packet &packet);

	sf::Socket::Status receive(sf::Packet &packet);

	/**
	* \return Whether the Socket is free or not
	*/

	bool isSocketFree() const;

	sf::Time timeSinceLastInteraction() const;

protected:

	bool               isFree; ///< Is the Socket free or not
	sf::SocketSelector *socketSelector; ///< SocketSelector the Socket is in
	sf::Clock		   lastInteractionClock;
};

/// @}

#endif // SERVERCLIENTS_HPP_INCLUDED
