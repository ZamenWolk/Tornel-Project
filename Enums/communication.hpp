#include <SFML/Network.hpp>

enum AttackType
{
    WEAPON_ATTACK = 0, ///< Weapon attack
    SPELL         = 1, ///< Mana-oriented skill
    ABILITY       = 2, ///< Stamina-oriented skill
};

enum ActionType
{
    NONE         = 0, ///< Do nothing
    DEAL_DAMAGE  = 1, ///< Deal damage to the target
    HEAL         = 2, ///< Heal the target
};

enum SpecialAttribute
{
    NO_SPECIAL    = 0, ///< Nothing special
    MISSED        = 1, ///< Missed the interaction
    DODGED        = 2, ///< Target dodged the interaction
    BLOCKED       = 3, ///< Target blocked the interaction
    CRITICAL      = 4, ///< Critical output for interaction
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