#include "ServerClients.hpp"

ServerClient::ServerClient() :
		isFree(true), socketSelector(0)
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