#include "ServerClients.hpp"

using namespace std;
using namespace sf;

ServerClient::ServerClient() :
		isFree(true), socketSelector(0), lastInteractionClock()
{

}

void ServerClient::connect(TcpListener &listener, SocketSelector *selector)
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
	TcpSocket::disconnect();
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

Socket::Status ServerClient::send(Packet &packet)
{
	lastInteractionClock.restart();
	Socket::Status status = TcpSocket::send(packet);
	lastInteractionClock.restart();
	return status;
}

Socket::Status ServerClient::receive(Packet &packet)
{
	lastInteractionClock.restart();
	Socket::Status status = TcpSocket::receive(packet);
	lastInteractionClock.restart();
	return status;
}

Time ServerClient::timeSinceLastInteraction() const
{
	return lastInteractionClock.getElapsedTime();
}
