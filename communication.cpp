#include "communication.hpp"

using namespace std;
using namespace sf;

Packet &emptyPacket(Packet &packet)
{
	int x;
	while (packet >> x);
	return packet;
}

Packet &infoTypeInPacket(Packet &packet, SentInfosType &type)
{
	packet >> type;
	return packet;
}