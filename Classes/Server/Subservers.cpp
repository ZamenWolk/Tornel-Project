#include <vector>

#include "Subservers.hpp"
#include "../../global/functions.hpp"
#include "../../global/communication.hpp"
#include "../../global/define.hpp"
#include "../Indexes/IndexesIndex.hpp"
#include "../Singleton.hpp"

using namespace std;
using namespace sf;

FightSubserver::FightSubserver() :
        clients(),
        serverThread(&FightSubserver::threadFunction, this),
        stopSubServer(0),
        eventsStructure()
{
    teams[0] = 0;
    teams[1] = 0;
}

FightSubserver::~FightSubserver()
{
    stopSubServer = true;
    serverThread.wait();
    delete teams[0];
    delete teams[1];
}

bool FightSubserver::isFull() const
{
    return !(clients[0].isSocketFree() || clients[1].isSocketFree());
}


void FightSubserver::reset()
{
    disconnect(true);
    disconnect(false);
}

ServerClient *FightSubserver::connect(TcpListener *listener, SocketSelector *socketSelector)
{
    ServerClient               *concernedClient(nullptr);
    vector<EntityInformations> *concernedTeamVector(nullptr);
    bool                       isClient1(false);

    if (clients[0].isSocketFree())
    {
        concernedClient     = &clients[0];
        concernedTeamVector = teams[0];
        isClient1           = true;
    }
    else if (clients[1].isSocketFree())
    {
        concernedClient     = &clients[1];
        concernedTeamVector = teams[1];
        isClient1           = false;
    }
    else
    {
        ServerClient buffer;
        buffer.connect(*listener);
        buffer.disconnect();
        return 0;
    }

    concernedClient->connect(*listener, socketSelector);

    while (eventsStructure.isEventTreated || eventsStructure.team1 != isClient1)
    {
        sleep(milliseconds(1000));
    }

    if (eventsStructure.typeOfEvent != VERSION_NUMBER)
    {
        errorReport("The information received is not a VERSION_NUMBER");
        concernedClient->disconnect();
        return NULL;
    }

    if (eventsStructure.infos.versEv.status != Version::STATUS || eventsStructure.infos.versEv.major != Version::MAJOR)
    {
        disconnect(true);
        eventsStructure.isEventTreated = true;
        return NULL;
    }

    concernedTeamVector = new vector<EntityInformations>;

    while (eventsStructure.isEventTreated || eventsStructure.team1 != isClient1)
    {
        sleep(milliseconds(1000));
    }

    if (eventsStructure.typeOfEvent != TEAM_DATA)
    {
        errorReport("The infformation received is not a TEAM_DATA");
        concernedClient->disconnect();
        return NULL;
    }

    *concernedTeamVector = eventsStructure.infos.teamEv;

    if (isFull())
    {
        serverThread.launch();
    }

    eventsStructure.isEventTreated = true;
    return concernedClient;
}

ServerClient *FightSubserver::disconnect(bool isClient1)
{
    if (isClient1)
    {
        clients[0].disconnect();
        delete teams[0];
        return &clients[0];
    }
    else
    {
        clients[1].disconnect();
        delete teams[1];
        return &clients[1];
    }
}

void FightSubserver::newEvent(SentInfosType infoType, const EventsUnion &eventInfos, bool isTeam1)
{
    eventsStructure.typeOfEvent    = infoType;
    eventsStructure.infos          = eventInfos;
    eventsStructure.team1          = isTeam1;
    eventsStructure.isEventTreated = false;
}

bool FightSubserver::isLastEventTreated()
{
    return eventsStructure.isEventTreated;
}

int FightSubserver::threadFunction()
{
    sf::Packet teamPacket, timePacket;
    time_t currentTime, debutTime;
    tm     debutTM;

    createPacket(teamPacket, *teams[1], TEAM_DATA);
    if (clients[0].send(teamPacket) != Socket::Done)
    {
        errorReport("Can't send team data to client 1");
        disconnect(true);
        return 1;
    }

    createPacket(teamPacket, *teams[0], TEAM_DATA);
    if (clients[1].send(teamPacket) != Socket::Done)
    {
        errorReport("Can't send team data to client 2");
        disconnect(false);
        return 1;
    }

    time(&currentTime);
    debutTime = currentTime + 10;
    debutTM = *gmtime(&debutTime);
    createPacket(timePacket, debutTM, STC_DEBUT_TIME);
    if (clients[0].send(timePacket) != Socket::Done)
    {
        errorReport("Can't send debut time data to client 1");
        disconnect(true);
        return 1;
    }
    if (clients[1].send(timePacket) != Socket::Done)
    {
        errorReport("Can't send debut time data to client 2");
        disconnect(false);
        return 1;
    }

    while (isFull() && !stopSubServer)
    {
        if (!eventsStructure.isEventTreated)
        {
            if (eventsStructure.typeOfEvent != CTS_INTERACTION)
            {
                errorReport("The information received is not a CTS_INTERACTION");
                disconnect(true);
                disconnect(false);
            }
            else
            {
                Packet actionPacket;
                FightAction action;
                action.subjectID = eventsStructure.infos.intEv.attackerID;
                action.targetID = eventsStructure.infos.intEv.targetID;
                action.actionType = DEAL_DAMAGE;
                action.attackType = eventsStructure.infos.intEv.type;
                action.specialAttribute = NO_SPECIAL;
                action.subject = NULL;
                action.skill = NULL;
                action.target = NULL;
                action.skillName = eventsStructure.infos.intEv.spellName;

                EntityInformations *subjectInfos = IDToInformations(action.subjectID, eventsStructure.team1),
                        *targetInfos = IDToInformations(action.targetID, !eventsStructure.team1);
                Skill *currentSkill;

                switch (eventsStructure.infos.intEv.type)
                {
                    case WEAPON_ATTACK:
                        action.attackDamage = (Int32)(((double)(eventsStructure.infos.intEv.baseDamage))*STRENGTH_TO_ATTACK_FACTOR.result(subjectInfos->effects.strength)*TOUGHNESS_TO_ATTACK_REDUCTION.result(targetInfos->effects.toughness));
                        break;
                    case SPELL:
                        currentSkill = singleton<IndexesIndex>().skillIndex.searchByName(action.skillName);
                        action.attackDamage = (Int32)(((double)(currentSkill->baseDamage))*WISDOM_TO_ATTACK_FACTOR.result(subjectInfos->effects.wisdom)*MENTAL_RESISTANCE_TO_ATTACK_REDUCTION.result(targetInfos->effects.mentalResistance));
                        break;
                    case ABILITY:
                        currentSkill = singleton<IndexesIndex>().skillIndex.searchByName(action.skillName);
                        action.attackDamage = (Int32)(((double)(currentSkill->baseDamage))*STRENGTH_TO_ATTACK_FACTOR.result(subjectInfos->effects.strength)*TOUGHNESS_TO_ATTACK_REDUCTION.result(targetInfos->effects.toughness));
                        break;
                }

                createPacket(actionPacket, action, STC_ACTION);
                if (clients[0].send(actionPacket) != Socket::Done)
                {
                    errorReport("Can't send action to client 1");
                    disconnect(true);
                    return 1;
                }
                if (clients[1].send(actionPacket) != Socket::Done)
                {
                    errorReport("Can't send action to client 2");
                    disconnect(false);
                    return 1;
                }
            }

            eventsStructure.isEventTreated = true;
        }

        sleep(milliseconds(100));
    }
}

EntityInformations *FightSubserver::IDToInformations(sf::Uint32 searchID, bool isTeam1)
{
    if (isTeam1)
    {
        for (vector<EntityInformations>::iterator it = teams[0]->begin(); it != teams[0]->end(); it++)
        {
            if (it->ID == searchID)
            {
                return &*it;
            }
        }
    }
    else
    {
        for (vector<EntityInformations>::iterator it = teams[1]->begin(); it != teams[1]->end(); it++)
        {
            if (it->ID == searchID)
            {
                return &*it;
            }
        }
    }

    errorReport("EntityInformations data doesn't exist for this ID");
    return &teams[0]->at(0);
}


bool findOpenSubserver(vector<FightSubserver *> &serverVector, FightSubserver **returnedSubserver)
{
    for (unsigned int i = 0; i < serverVector.size(); i++)
    {
        if (!(serverVector.operator[](i)->isFull()))
        {
            *returnedSubserver = serverVector[i];
            return true;
        }
    }

    return false;
}
