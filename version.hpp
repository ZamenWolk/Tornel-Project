#include <iostream>
#include <SFML/Network.hpp>

struct VersionNumber
{
    VersionNumber(std::string status, sf::Int32 major, sf::Int32 minor, sf::Int32 patch) :
            status(status),
            major(major),
            minor(minor),
            patch(patch)
    {

    }

    VersionNumber() :
            status(""),
            major(0),
            minor(0),
            patch(0)
    {

    }

    ~VersionNumber()
    {

    }

    std::string status;
    sf::Int32   major;
    sf::Int32   minor;
    sf::Int32   patch;
};

namespace Version
{
    static const char          STATUS[]             = "Alpha";
    static const long          MAJOR                = 1;
    static const long          MINOR                = 13;
    static const long          PATCH                = 1;
    static const VersionNumber VERSION(STATUS, MAJOR, MINOR, PATCH);
    static const char          FULLVERSION_STRING[] = "a1.13.1";
}

sf::Packet &operator<<(sf::Packet &packet, const VersionNumber &version);

sf::Packet &operator>>(sf::Packet &packet, VersionNumber &version);