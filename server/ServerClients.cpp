#include "ServerClients.hpp"

ServerClient::ServerClient() :
		isFree(true), socketSelector(0), lastInteractionClock()
{

}

void ServerClient::connect(sf::TcpListener &listener, sf::SocketSelector *selector)
{
	listener.accept(*this);
	socketSelector = selector;
	if (socketSelector != 0)
	{
		socketSelector->add(*this);
	}
	isFree = false;
}

void ServerClient::disconnect()
{
	sf::TcpSocket::disconnect();
	if (socketSelector != 0)
	{
		socketSelector->remove(*this);
	}
	isFree         = true;
	socketSelector = 0;
}

bool ServerClient::isSocketFree() const
{
	return isFree;
}

sf::Socket::Status ServerClient::send(sf::Packet &packet)
{
	lastInteractionClock.restart();
	sf::Socket::Status status = TcpSocket::send(packet);
	lastInteractionClock.restart();
	return status;
}

sf::Socket::Status ServerClient::receive(sf::Packet &packet)
{
	lastInteractionClock.restart();
	sf::Socket::Status status = TcpSocket::receive(packet);
	lastInteractionClock.restart();
	return status;
}

sf::Time ServerClient::timeSinceLastInteraction() const
{
	return lastInteractionClock.getElapsedTime();
}
