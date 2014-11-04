#include "communication.hpp"

sf::Packet &emptyPacket(sf::Packet &packet)
{
	int x;
	while (packet >> x);
	return packet;
}

sf::Packet &infoTypeInPacket(sf::Packet &packet, SentInfosType &type)
{
	packet >> type;
	return packet;
}