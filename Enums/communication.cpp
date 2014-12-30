#include "communication.hpp"
#include "../global/functions.hpp"

using namespace sf;

Packet &operator>>(Packet &packet, ActionType &action)
{
    int actionNumber;
    packet >> actionNumber;

    switch (actionNumber)
    {
        case NONE:
            action = NONE;
            break;
        case DEAL_DAMAGE:
            action = DEAL_DAMAGE;
            break;
        case HEAL:
            action = HEAL;
            break;
        default:
            errorReport("Unknown action", true);
    }

    return packet;
}

Packet &operator>>(Packet &packet, SpecialAttribute &attribute)
{
    int attributeNumber;
    packet >> attributeNumber;

    switch (attributeNumber)
    {
        case NO_SPECIAL:
            attribute = NO_SPECIAL;
            break;
        case MISSED:
            attribute = MISSED;
            break;
        case DODGED:
            attribute = DODGED;
            break;
        case BLOCKED:
            attribute = BLOCKED;
            break;
        case CRITICAL:
            attribute = CRITICAL;
            break;
        default:
            errorReport("Unknown attribute", true);
    }

    return packet;
}

Packet &operator>>(Packet &packet, AttackType &attackType)
{
    int typeNumber;
    packet >> typeNumber;

    switch (typeNumber)
    {
        case WEAPON_ATTACK:
            attackType = WEAPON_ATTACK;
            break;
        case SPELL:
            attackType = SPELL;
            break;
        case ABILITY:
            attackType = ABILITY;
            break;
        default:
            errorReport("Unknown action type", true);
    }

    return packet;
}

Packet &operator>>(Packet &packet, SentInfosType &infosType)
{
    int infosTypeNumber;
    packet >> infosTypeNumber;

    switch (infosTypeNumber)
    {
        case CTS_INTERACTION:
            infosType = CTS_INTERACTION;
            break;
        case TEAM_DATA:
            infosType = TEAM_DATA;
            break;
        case VERSION_NUMBER:
            infosType = VERSION_NUMBER;
            break;
        case PING:
            infosType = PING;
            break;
        case PONG:
            infosType = PONG;
            break;
        case STC_ACTION:
            infosType = STC_ACTION;
            break;
        case END_OF_COMBAT:
            infosType = END_OF_COMBAT;
            break;
        case STC_DEBUT_TIME:
            infosType = STC_DEBUT_TIME;
            break;
        default:
            errorReport("Unknown information type", true);
    }

    return packet;
}