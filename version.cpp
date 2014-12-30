#include "version.hpp"

using namespace sf;

Packet &operator<<(Packet &packet, const VersionNumber &version)
{
    return packet << version.status << version.major << version.minor << version.patch;
}

Packet &operator>>(Packet &packet, VersionNumber &version)
{
    return packet >> version.status >> version.major >> version.minor >> version.patch;
}