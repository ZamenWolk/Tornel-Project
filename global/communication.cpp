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

Packet &operator<<(Packet &packet, const Time &time)
{
    return packet << time.asMilliseconds();
}

Packet &operator>>(Packet &packet, Time &time)
{
    Int32 timeMilliseconds;

    packet >> timeMilliseconds;
    time = milliseconds(timeMilliseconds);

    return packet;
}

Packet &operator<<(Packet &packet, const tm &time)
{
    return packet << time.tm_sec << time.tm_min << time.tm_hour << time.tm_mday << time.tm_mon << time.tm_year << time.tm_isdst;
}

Packet &operator>>(Packet &packet, tm &time)
{
    return packet >> time.tm_sec >> time.tm_min >> time.tm_hour >> time.tm_mday >> time.tm_mon >> time.tm_year >> time.tm_isdst;
}