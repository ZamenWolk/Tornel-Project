#include <vector>

#include "Combat.hpp"
#include "../global/communication.hpp"

#define K_CHARMENU eventsMap.isActive("characterMenu")
#define K_TARGMENU eventsMap.isActive("targetMenu")
#define K_ABILMENU eventsMap.isActive("abilityMenu")
#define K_SPELLMENU eventsMap.isActive("spellMenu")
#define K_WEAPATK eventsMap.isActive("weaponAttack")
#define K_MAINMENU eventsMap.isActive("mainMenu")
#define K_PREVPAGE eventsMap.isActive("prevPage")
#define K_NEXTPAGE eventsMap.isActive("nextPage")
#define K_SELEC1 eventsMap.isActive("selector1")
#define K_SELEC2 eventsMap.isActive("selector2")
#define K_SELEC3 eventsMap.isActive("selector3")
#define K_SELEC4 eventsMap.isActive("selector4")
#define K_SELEC5 eventsMap.isActive("selector5")
#define K_SELEC6 eventsMap.isActive("selector6")
#define K_CHARSELEC eventsMap.isActive("charSelector")
#define K_SELEC eventsMap.isActive("selector")

using namespace std;
using namespace sf;

Combat::Combat() :
        App(),
        team1Fighters(),
        team2Fighters(),
        team1Control(NO_CONTROL),
        team2Control(NO_CONTROL),
        team1EventProcessed(true),
        team2EventProcessed(true),
        aboutToStop(false),
        onlineMutex()
{
    eventsMap["characterMenu"] = thor::Action(Keyboard::A, thor::Action::PressOnce);
    eventsMap["targetMenu"]    = thor::Action(Keyboard::Z, thor::Action::PressOnce);
    eventsMap["abilityMenu"]   = thor::Action(Keyboard::E, thor::Action::PressOnce);
    eventsMap["spellMenu"]     = thor::Action(Keyboard::R, thor::Action::PressOnce);
    eventsMap["weaponAttack"]  = thor::Action(Keyboard::D, thor::Action::PressOnce);
    eventsMap["mainMenu"]      = thor::Action(Keyboard::Numpad8, thor::Action::PressOnce);
    eventsMap["prevPage"]      = thor::Action(Keyboard::Numpad7, thor::Action::PressOnce);
    eventsMap["nextPage"]      = thor::Action(Keyboard::Numpad9, thor::Action::PressOnce);
    eventsMap["selector1"]     = thor::Action(Keyboard::Numpad4, thor::Action::PressOnce);
    eventsMap["selector2"]     = thor::Action(Keyboard::Numpad5, thor::Action::PressOnce);
    eventsMap["selector3"]     = thor::Action(Keyboard::Numpad6, thor::Action::PressOnce);
    eventsMap["selector4"]     = thor::Action(Keyboard::Numpad1, thor::Action::PressOnce);
    eventsMap["selector5"]     = thor::Action(Keyboard::Numpad2, thor::Action::PressOnce);
    eventsMap["selector6"]     = thor::Action(Keyboard::Numpad3, thor::Action::PressOnce);
    eventsMap["charSelector"]  = eventsMap["selector1"] || eventsMap["selector2"] || eventsMap["selector3"] || eventsMap["selector4"] || eventsMap["selector5"];
    eventsMap["selector"]      = eventsMap["selector6"] || eventsMap["charSelector"];

    onlinePort.setBlocking(false);
}

void Combat::Start()
{
    App::Start();
}

void Combat::Exit()
{
    App::Exit();
}

int Combat::fillFightersVector(vector<CombatEntity> &teamVector, bool isTeam1)
{
    int deletedEntities(0);
    if (isTeam1)
    {
        team1Fighters = teamVector;
        while (team1Fighters.size() > 5)
        {
            team1Fighters.pop_back();
            deletedEntities++;
        }
    }
    else
    {
        team2Fighters = teamVector;
        while (team2Fighters.size() > 5)
        {
            team2Fighters.pop_back();
            deletedEntities++;
        }
    }

    return deletedEntities;
}

string Combat::Run(RenderWindow &window, map<string, App *> &apps)
{
    if (!combatChecking())
    {
        errorReport("The combat was not properly initialized");
        return "menu";
    }

    Start();

    while (!aboutToStop)
    {
        eventsMap.update(window);

        if (team1Control == KEYBOARD)
        {
            keyboardInstructions(&team1Fighters, &team2Fighters);
        }

        if (team2Control == KEYBOARD)
        {
            keyboardInstructions(&team2Fighters, &team1Fighters);
        }

        serverHandling();
    }

    return endOfCombat();
}

int Combat::setupServer(vector<CombatEntity> yourTeam, Controls controlTeam1, Controls controlTeam2, string IPAddress, unsigned short addressPort)
{
    Packet               versionNumber, charactersPacket, packetFromServer, timePacket;
    SentInfosType        type;
    vector<CombatEntity> teamFromServer;
    tm                   launchTM;
    time_t               launchTime;

    logReport("Connecting to server...", true);
    onlineMutex.lock();
    if (onlinePort.connect(IPAddress, addressPort) != Socket::Done)
    {
        errorReport("Can't connect to the server");
    }

    logReport("Sending version number to server...", true);
    createPacket(versionNumber, Version::VERSION, VERSION_NUMBER);
    if (onlinePort.send(versionNumber) != Socket::Done)
    {
        errorReport("Can't send version information to server");
    }

    team1Control = controlTeam1;
    team2Control = controlTeam2;

    team1Fighters = yourTeam;

    logReport("Sending team information to server...", true);
    createPacket(charactersPacket, team1Fighters, TEAM_DATA);
    if (onlinePort.send(charactersPacket) != Socket::Done)
    {
        errorReport("Can't send team informations to server");
    }

    logReport("Waiting for enemy team informations...", true);
    if (onlinePort.receive(packetFromServer) != Socket::Done)
    {
        errorReport("Can't receive team informations from server");
    }
    infoTypeInPacket(packetFromServer, type);

    if (type != TEAM_DATA)
    {
        errorReport("The packet received is not a TEAM_DATA");
        return 1;
    }

    deconstructPacket(packetFromServer, teamFromServer, type);
    fillFightersVector(teamFromServer, false);

    logReport("Waiting for launch time...", true);
    if (onlinePort.receive(timePacket) != Socket::Done)
    {
        errorReport("Can't receive launch time from server");
    }
    infoTypeInPacket(timePacket, type);

    if (type != STC_DEBUT_TIME)
    {
        errorReport("The packet received is not a STC_DEBUT_TIME");
        return 1;
    }

    deconstructPacket(timePacket, launchTM, type);

    launchTime = mktime(&launchTM) + secondsAheadOfGMT();

    logReport("Waiting for the fight to begin", true);
    while (time(NULL) < launchTime)
    {
        sleep(milliseconds(50));
    }

    return 0;
}

string Combat::endOfCombat()
{
    aboutToStop = true;
    Packet packetFromServer;
    bool   wonBattle;

    onlineMutex.lock();
    if (onlinePort.receive(packetFromServer) != Socket::Done)
    {
        errorReport("Can't receive winner informations from server");
    }
    onlineMutex.unlock();
    packetFromServer >> wonBattle;

    Exit();

    return wonBattle ? "winner" : "loser";
}

bool Combat::combatChecking()
{
    return !(team1Control == AI
          || team1Control == ONLINE
          || team1Control == FROM_FILE
          || team1Control == KEYBOARD && team2Control == KEYBOARD
          || team1Control == CONTROLLER && team2Control == CONTROLLER
          || team1Fighters.size() < 1
          || team1Fighters.size() > 5
          || team2Fighters.size() < 1
          || team2Fighters.size() > 5);
}

void Combat::serverHandling()
{
    Packet         packetFromServer;
    SentInfosType  infoType;
    FightAction    action;
    Socket::Status result;

    onlineMutex.lock();
    result = onlinePort.receive(packetFromServer);
    onlineMutex.unlock();

    if (result != Socket::Done && result != Socket::NotReady)
    {
        errorReport("Can't receive informations from server");
    }
    else
    {
        infoTypeInPacket(packetFromServer, infoType);
        if(infoType != STC_ACTION && infoType != END_OF_COMBAT)
        {
            errorReport("Information from server is not a STC_ACTION");
        }
        else if (infoType == END_OF_COMBAT)
        {
            aboutToStop = true;
        }
        else
        {
            deconstructPacket(packetFromServer, action, infoType);
            action.subject = IDToEntity(action.subjectID);

            switch (action.actionType)
            {
                case NONE:
                    switch (action.specialAttribute)
                    {
                        case NO_SPECIAL:
                        case MISSED:
                        case DODGED:
                        case BLOCKED:
                        case CRITICAL:
                        default:
                            errorReport(
                                    "The request sent by the server is handled by the receiving function, but not by serverHandling(). Please contact the developpers");
                    }
                    break;
                case DEAL_DAMAGE:
                    action.target = IDToEntity(action.targetID);

                    if (action.attackType != WEAPON_ATTACK)
                    {
                        action.skill = singleton<IndexesIndex>().skillIndex.searchByName(action.skillName);
                    }
                    action.target->getEntity()->changeLife(-action.attackDamage);

                    switch (action.specialAttribute)
                    {
                        case NO_SPECIAL:
                            if (action.attackType == WEAPON_ATTACK)
                            {
                                string message(action.subject->getEntity()->getName());
                                message += " attacked ";
                                message += action.target->getEntity()->getName();
                                message += ", dealing ";
                                message += action.attackDamage;
                                message += " damage";
                                logReport(message);
                            }
                            else
                            {
                                string message(action.subject->getEntity()->getName());
                                message += " used ";
                                message += action.skill->name;
                                message += " on ";
                                message += action.target->getEntity()->getName();
                                message += ", dealing ";
                                message += action.attackDamage;
                                message += " damage";
                                logReport(message);
                            }
                            break;
                        case MISSED:
                        case DODGED:
                        case BLOCKED:
                        case CRITICAL:
                        default:
                            errorReport(
                                    "The request sent by the server is handled by the receiving function, but not by serverHandling(). Please contact the developpers");
                    }
                    break;
                case HEAL:
                default:
                    errorReport(
                            "The request sent by the server is handled by the receiving function, but not by serverHandling(). Please contact the developpers");
            }
        }
    }
}

CombatEntity *Combat::IDToEntity(unsigned long entityID)
{
    for (vector<CombatEntity>::iterator it = team1Fighters.begin(); it != team1Fighters.end(); it++)
    {
        if (it->getEntity()->getID() == entityID)
        {
            return &*it;
        }
    }

    for (vector<CombatEntity>::iterator it = team2Fighters.begin(); it != team2Fighters.end(); it++)
    {
        if (it->getEntity()->getID() == entityID)
        {
            return &*it;
        }
    }

    errorReport("Server sent an unknown fighter ID");
    return &team1Fighters[0];
}

void Combat::keyboardInstructions(vector<CombatEntity> *currentTeam, vector<CombatEntity> *currentEnemies)
{

    static CombatMenu   currentMenu(MAIN);
    static int          spellPage(0), abilityPage(0), selectorVariable(-1);
    static CombatEntity *currentCharacter(&currentTeam->at(0));

    if (K_CHARMENU)
    {
        currentMenu = CHARACTER_CHOOSING;
        logReport("Current menu : Character choosing");
    }
    else if (K_TARGMENU)
    {
        currentMenu = TARGET_CHOOSING;
        logReport("Current menu : Target choosing");
    }
    else if (K_ABILMENU)
    {
        currentMenu = ABILITY_CHOOSING;
        logReport("Current menu : Ability choosing");
    }
    else if (K_SPELLMENU)
    {
        currentMenu = SPELL_CHOOSING;
        logReport("Current menu : Spell choosing");
    }
    else if (K_WEAPATK)
    {
        checkActionToSend(*currentCharacter, *currentCharacter->getTarget(),
                WEAPON_ATTACK, currentCharacter->getEffects().baseDamage);
    }
    else if (K_MAINMENU)
    {
        currentMenu = MAIN;
        logReport("Current menu : Main");
    }
    else if (K_SELEC1)
    {
        selectorVariable = 0;
    }
    else if (K_SELEC2)
    {
        selectorVariable = 1;
    }
    else if (K_SELEC3)
    {
        selectorVariable = 2;
    }
    else if (K_SELEC4)
    {
        selectorVariable = 3;
    }
    else if (K_SELEC5)
    {
        selectorVariable = 4;
    }
    else if (K_SELEC6)
    {
        selectorVariable = 5;
    }
    else if (K_PREVPAGE)
    {
        switch (currentMenu)
        {
            case ABILITY_CHOOSING:
                if (abilityPage > 0)
                    abilityPage--;
                logReport("Ability page : " + abilityPage);
                break;

            case SPELL_CHOOSING:
                if (spellPage > 0)
                    spellPage--;
                logReport("Spell page : " + spellPage);
                break;
            case MAIN:
                break;
            case CHARACTER_CHOOSING:
                break;
            case TARGET_CHOOSING:
                break;
        }
    }

    else if (K_NEXTPAGE)
    {
        switch (currentMenu)
        {
            case ABILITY_CHOOSING:
                if (currentCharacter->getEntity()->getKnownAbilities().size() >= (abilityPage*6 + 7))
                    abilityPage++;
                logReport("Ability page : " + abilityPage);
                break;

            case SPELL_CHOOSING:
                if (currentCharacter->getEntity()->getKnownSpells().size() >= (spellPage*6 + 7))
                    spellPage++;
                logReport("Spell page : " + spellPage);
                break;
            case MAIN:
                break;
            case CHARACTER_CHOOSING:
                break;
            case TARGET_CHOOSING:
                break;
        }
    }

    if (K_SELEC && selectorVariable != -1)
    {
        if (K_CHARSELEC)
        {
            switch (currentMenu)
            {
                case CHARACTER_CHOOSING:
                    if (currentTeam->at((unsigned int)selectorVariable).getEntity()->isAlive())
                    {
                        currentCharacter = &currentTeam->at((unsigned int)selectorVariable);
                        logReport("New character : " + currentCharacter->getEntity()->getName());
                    }
                    break;

                case TARGET_CHOOSING:
                    if (currentEnemies->at((unsigned int)selectorVariable).getEntity()->isAlive())
                    {
                        currentCharacter->changeTarget(&currentEnemies->at((unsigned int)selectorVariable));
                        logReport("New target : " + currentCharacter->getTarget()->getEntity()->getName());
                    }
                    break;
                case MAIN:
                    break;
                case SPELL_CHOOSING:
                    break;
                case ABILITY_CHOOSING:
                    break;
            }
        }

        switch (currentMenu)
        {
            case ABILITY_CHOOSING:
                if ((currentCharacter->getEntity()->getKnownAbilities().size() >= abilityPage*6 + selectorVariable + 1))
                {
                    checkActionToSend(*currentCharacter,
                            *currentCharacter->getTarget(),
                            ABILITY,
                            0,
                            currentCharacter->getEntity()->getKnownAbilities().at((unsigned int)(abilityPage*6 + selectorVariable)));
                }
                break;

            case SPELL_CHOOSING:
                if ((currentCharacter->getEntity()->getKnownSpells().size() >= spellPage*6 + selectorVariable + 1))
                {
                    checkActionToSend(*currentCharacter,
                            *currentCharacter->getTarget(),
                            SPELL,
                            0,
                            currentCharacter->getEntity()->getKnownSpells().at((unsigned int)(spellPage*6 + selectorVariable)));
                }
                break;
            case MAIN:
                break;
            case CHARACTER_CHOOSING:
                break;
            case TARGET_CHOOSING:
                break;
        }

        selectorVariable = -1;
        currentMenu      = MAIN;
    }
}

void Combat::checkActionToSend(CombatEntity &attacker, CombatEntity &target, AttackType type, int baseDamage, Skill *skill)
{
    bool canBeSent = true;

    if (clock.getElapsedTime() < (attacker.getLastInteractionTime() + attacker.getInteractionCooldown()))
    {
        canBeSent = false;
        logReport("Your cooldown is not finished yet !", false);
    }

    switch (type)
    {
        case WEAPON_ATTACK:
            if (canBeSent)
            {
                attacker.changeInteractionTimes(clock.getElapsedTime(), attacker.getEffects().cooldownTime);
            }
            break;
        case SPELL:
        case ABILITY:
            if ((attacker.getEntity()->getMana()
                    < skill->manaCost)
                    || (attacker.getEntity()->getStamina()
                    < skill->staminaCost))
            {
                canBeSent = false;
                logReport("You don't have enough CP to use this skill !");
            }
            else
            {
                attacker.changeInteractionTimes(clock.getElapsedTime(), skill->cooldown);
            }
            break;
    }

    if (canBeSent)
    {
        sendToServer(attacker, target, type, baseDamage, skill->name);
    }
}

void Combat::sendToServer(CombatEntity &attacker, CombatEntity &target, AttackType type, int baseDamage, string skillName)
{
    Packet           packetToSend;
    InteractionInfos informationsToSend{attacker.getEntity()->getID(), target.getEntity()->getID(), type, baseDamage, skillName};

    createPacket(packetToSend, informationsToSend, CTS_INTERACTION);

    onlineMutex.lock();
    if (onlinePort.send(packetToSend) != Socket::Done)
    {
        errorReport("Unable to send informations to combat server");
    }
    onlineMutex.unlock();
}
