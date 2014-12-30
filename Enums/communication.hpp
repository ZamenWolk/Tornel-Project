#include <SFML/Network.hpp>

enum AttackType
{
    WEAPON_ATTACK = 0,
    SPELL         = 1,
    ABILITY       = 2,
};

enum ActionType
{
    NONE         = 0,
    DEAL_DAMAGE  = 1,
    HEAL         = 2,
};

enum SpecialAttribute
{
    NO_SPECIAL    = 0,
    MISSED        = 1,
    DODGED        = 2,
    BLOCKED       = 3,
    CRITICAL      = 4,
};

enum SentInfosType
{
    CTS_INTERACTION = 0,
    TEAM_DATA       = 1,
    VERSION_NUMBER  = 2,
    END_OF_COMBAT   = 3,
    PONG            = 4,
    STC_DEBUT_TIME  = 5,
    STC_ACTION      = 6,
    PING            = 7,
};

sf::Packet &operator>>(sf::Packet &packet, ActionType &action);

sf::Packet &operator>>(sf::Packet &packet, SpecialAttribute &attribute);

sf::Packet &operator>>(sf::Packet &packet, AttackType &attackType);

sf::Packet &operator>>(sf::Packet &packet, SentInfosType &infosType);