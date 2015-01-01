#ifndef GLOBAL_COMMUNICATION_HPP
#define GLOBAL_COMMUNICATION_HPP

#include <SFML/Network.hpp>

#include "../Enums/communication.hpp"
#include "../version.hpp"
#include "../Classes/communication.hpp"
#include "functions.hpp"

sf::Packet &emptyPacket(sf::Packet &packet);

template<typename T>
sf::Packet &createPacket(sf::Packet &packet, const T &infos, SentInfosType type)
{
    if (   (typeid(infos) == typeid(const VersionNumber) && type == VERSION_NUMBER)
            || (typeid(infos) == typeid(const InteractionInfos) && type == CTS_INTERACTION)
            || (typeid(infos) == typeid(const std::vector<CombatEntity>) && type == TEAM_DATA)
            || (typeid(infos) == typeid(const int) && (type == PING || type == PONG))
            || (typeid(infos) == typeid(const FightAction) && type == STC_ACTION)
            || (typeid(infos) == typeid(const EOFStruct) && type == END_OF_COMBAT)
            || (typeid(infos) == typeid(const tm) && type == STC_DEBUT_TIME)
            || (typeid(infos) == typeid(const FightAction) && type == STC_ACTION))
    {
        emptyPacket(packet);
        return packet << type << infos;
    }
    else
    {
        errorReport("The type of info sent does not match the type of variable");
        return packet;
    }
}

sf::Packet &infoTypeInPacket(sf::Packet &packet, SentInfosType &type);

template<typename T>
sf::Packet &deconstructPacket(sf::Packet &packet, T &infos, SentInfosType type)
{
    if (   (typeid(infos) == typeid(VersionNumber) && type == VERSION_NUMBER)
            || (typeid(infos) == typeid(InteractionInfos) && type == CTS_INTERACTION)
            || (typeid(infos) == typeid(std::vector<CombatEntity>) && type == TEAM_DATA)
            || (typeid(infos) == typeid(int) && (type == PING || type == PONG))
            || (typeid(infos) == typeid(FightAction) && type == STC_ACTION)
            || (typeid(infos) == typeid(EOFStruct) && type == END_OF_COMBAT)
            || (typeid(infos) == typeid(tm) && type == STC_DEBUT_TIME)
            || (typeid(infos) == typeid(FightAction) && type == STC_ACTION))
    {
        return packet >> infos;
    }
    else
    {
        errorReport("The type of info sent does not match the type of variable");
        return packet;
    }
}

sf::Packet &operator<<(sf::Packet &packet, const sf::Time &time);

sf::Packet &operator>>(sf::Packet &packet, sf::Time &time);

sf::Packet &operator<<(sf::Packet &packet, const tm &time);

sf::Packet &operator>>(sf::Packet &packet, tm &time);

#endif