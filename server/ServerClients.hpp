#ifndef SERVERCLIENTS_HPP_INCLUDED
#define SERVERCLIENTS_HPP_INCLUDED

   /**
    *   \file ServerClients.hpp
    *   \brief Contains the ServerClient class, as well as ServerClient-related functions
    */

#include <SFML/Network.hpp>

/**
* \addtogroup server
* @{
*/

   /**
    *   \brief Enhanced version of a TCP socket
    *   \details Has extra functions to know if the socket is connected, and automatic handling of a SocketSelector
    */

class ServerClient : public sf::TcpSocket
{
public:

    ServerClient():
           isFree(true),
           socketSelector(0)
    {

    }

   /**
    *   \brief Connects the socket with the socket sent, and adds itself to the SocketSelector if given
    *   \param[in] listener Listener to connect the Socket from
    *   \param[in] socketSelector SocketSelector to add the socket to
    */

    void connect(sf::TcpListener& listener, sf::SocketSelector *socketSelector = 0)
    {
        listener.accept(*this);
        socketSelector = socketSelector;
        if (socketSelector != 0)
        {
            socketSelector->add(*this);
        }
        isFree = false;
    }

   /**
    *   \brief Disconnect the Socket
    */

    void disconnect()
    {
        sf::TcpSocket::disconnect();
        if (socketSelector != 0)
        {
            socketSelector->remove(*this);
        }
        isFree = true;
        socketSelector = 0;
    }

   /**
    *   \return Whether the Socket is free or not
    */

    bool isSocketFree() const
    {
        return isFree;
    }

protected:

    bool 				isFree; ///< Is the Socket free or not
    sf::SocketSelector  *socketSelector; ///< SocketSelector the Socket is in
};

/// @}

#endif // SERVERCLIENTS_HPP_INCLUDED
