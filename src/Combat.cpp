#include "Combat.hpp"

using namespace std;
using namespace sf;

CombatEntity::CombatEntity(EntityModel *entity) :
		entity(entity),
		target(nullptr),
		effects(entity->getEffects(), entity->basicAttackEffects()),
		lastInteractionTime(milliseconds(0)),
		interactionCooldown(milliseconds(0))
{

}

void CombatEntity::changeTarget(CombatEntity *newTarget)
{
	if (newTarget->entity->isAlive())
		target = newTarget;
}

EntityModel *CombatEntity::getEntity() const
{
	return entity;
}

CombatEntity *CombatEntity::getTarget() const
{
	return target;
}

CombatEffects CombatEntity::getEffects() const
{
	return effects;
}

Combat::Combat(const Controls team1Control, const Controls team2Control) :
		team1Fighters(),
		team2Fighters(),
		team1Control(team1Control),
		team2Control(team2Control),
		team1EventProcessed(true),
		team2EventProcessed(true),
		aboutToStop(false),
		team1Thread(bind(&Combat::teamInstructions, this, true)),
		team2Thread(bind(&Combat::teamInstructions, this, false)),
		serverThread(&Combat::serverHandling, this),
		onlineMutex(),
		launched(false)
{
	combatChecking();
}

void Combat::changeEnemyTeam(vector<CombatEntity> newTeam)
{
	//Resets the vector of team2
	while (team2Fighters.size() > 0)
	{
		team2Fighters.pop_back();
	}

	while (newTeam.size() > 5)
	{
		newTeam.pop_back();
	}

	//Loads the new team into the vector
	for (vector<CombatEntity>::iterator it = newTeam.begin(); it != newTeam.end(); it++)
	{
		team2Fighters.push_back(*it);
	}
}

string Combat::Run(RenderWindow &app, map<string, Screen *> &screens)
{
	if (team1Fighters.size() < 1 || team1Fighters.size() > 5 || team2Fighters.size() < 1 || team2Fighters.size() > 5)
	{
		errorReport("The combat was not properly initialized");
		return "menu";
	}

	if (!launched)
	{
		//Launches the threads
		logReport("The game begins !");
		team1Thread.launch();
		team2Thread.launch();
		serverThread.launch();

		launched = true;
	}


	//Catches events to be processed by the threads until the fight stops
	while (!aboutToStop)
	{
		indexes.keyboardMap.update(app);

		team1EventProcessed = false;
		team2EventProcessed = false;

		while (!team1EventProcessed && !team2EventProcessed)
		{
			sleep(milliseconds(25));
		}
	}

	return endOfCombat();
}

void Combat::Setup(string IPAddress, unsigned short addressPort)
{
	Packet               versionNumber, charactersPacket, packetFromServer, timePacket;
	VersionNumber        version(AutoVersion::STATUS, AutoVersion::MAJOR, AutoVersion::MINOR, AutoVersion::PATCH);
	vector<CombatEntity> teamFromServer;
	Time                 pingTime(milliseconds(0)), pongTime(milliseconds(0)), timeUntilLaunch(milliseconds(0)), timeAtLaunchDelay(milliseconds(0));

	//Connects to the server
	onlineMutex.lock();
	if (onlinePort.connect(IPAddress, addressPort) != Socket::Done)
	{
		errorReport("Can't connect to the server");
	}

	//Sends version number to the server
	createPacket(versionNumber, version, VERSION_NUMBER);
	if (onlinePort.send(versionNumber) != Socket::Done)
	{
		errorReport("Can't send version information to server");
	}

	//Sends team's character vector to the server
	createPacket(charactersPacket, team1Fighters, CTS_TEAM_DATA);
	if (onlinePort.send(charactersPacket) != Socket::Done)
	{
		errorReport("Can't send team informations to server");
	}

	//Receives opposite team's character vector from the server
	if (onlinePort.receive(packetFromServer) != Socket::Done)
	{
		errorReport("Can't receive team informations from server");
	}
	packetFromServer >> teamFromServer;
	changeEnemyTeam(teamFromServer);

	//Calculates the ping with the server so both clients can begin at the same time
	pingTime = mainClock.getElapsedTime();
	createPacket(timePacket, pingTime, PING);
	if (onlinePort.send(timePacket) != Socket::Done)
	{
		errorReport("Can't ping server");
	}

	if (onlinePort.receive(packetFromServer) != Socket::Done)
	{
		errorReport("Can't receive pong from server");
	}
	pongTime = mainClock.getElapsedTime();

	emptyPacket(timePacket);

	//Sends latency to server
	createPacket(timePacket, pongTime - pingTime, PING);
	if (onlinePort.send(timePacket) != Socket::Done)
	{
		errorReport("Can't send latency to server");
	}

	emptyPacket(timePacket);

	//Receives the delay until the beginning of the fight from the server
	if (onlinePort.receive(timePacket) != Socket::Done)
	{
		errorReport("Can't receive launch delay from server");
	}
	onlineMutex.unlock();

	timePacket >> timeUntilLaunch;
	timeAtLaunchDelay = mainClock.getElapsedTime();

	//Waits until the delay until the beginning of fight is over
	while (mainClock.getElapsedTime() < timeAtLaunchDelay + timeUntilLaunch)
	{
		sleep(milliseconds(50));
	}
}

string Combat::endOfCombat()
{
	aboutToStop = true;
	Packet packetFromServer;
	bool   wonBattle;

	//Terminates all server threads
	team1Thread.wait();
	team2Thread.wait();
	serverThread.wait();

	//Receives winner information from server
	onlineMutex.lock();
	if (onlinePort.receive(packetFromServer) != Socket::Done)
	{
		errorReport("Can't receive winner informations from server");
	}
	onlineMutex.unlock();
	packetFromServer >> wonBattle;

	launched = false;

	return wonBattle ? "winner" : "loser";
}

void Combat::combatChecking()
{
	if (   team1Control == AI
	    || team1Control == ONLINE
	    || team1Control == FROM_FILE
	    || team1Control == KEYBOARD && team2Control == KEYBOARD
	    || team1Control == CONTROLLER && team2Control == CONTROLLER)
	{
		errorReport("Error in combat checking", true);
	}
}

void Combat::teamInstructions(bool team1)
{
	vector<CombatEntity> *currentTeam(nullptr), *currentEnemies(nullptr);
	const Controls       *currentControl(nullptr);
	bool                 *currentTeamEventProcessed(nullptr);

	//Sets up all the pointers so the program can be the same for both team
	if (team1)
	{
		currentTeam               = &team1Fighters;
		currentEnemies            = &team2Fighters;
		currentControl            = &team1Control;
		currentTeamEventProcessed = &team1EventProcessed;
	}
	else
	{
		currentTeam               = &team2Fighters;
		currentEnemies            = &team1Fighters;
		currentControl            = &team2Control;
		currentTeamEventProcessed = &team2EventProcessed;
	}

	//Processes every event that comes by
	while (!aboutToStop)
	{
		if (!*currentTeamEventProcessed && *currentControl == KEYBOARD)
		{
			keyboardInstructions(currentTeam, currentEnemies);
		}

		*currentTeamEventProcessed = true;

		sleep(milliseconds(25));
	}
}

void Combat::serverHandling()
{
	while (!aboutToStop)
	{
		Packet           packetFromServer;
		SentInfosType    infoType;
		FightAction      action;
		Socket::Status   result;

		//Receives packet of information from the server
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
			if(infoType != STC_ACTION)
			{
				errorReport("Information from server is not a STC_ACTION");
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
					case NOT_ENOUGH_CP:

				        action.skill = indexes.skillIndex.searchByName(action.skillName);

				        logReport(action.subject->getEntity()->getName() + " needs more Capacity Points to use " + action.skill->name);
				        break;
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
						action.skill = indexes.skillIndex.searchByName(action.skillName);
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
					case NOT_ENOUGH_CP:
					case MISSED:
					case DODGED:
					case BLOCKED:
					case CRITICAL:
					default:
						errorReport(
								"The request sent by the server is handled by the receiving function, but not by serverHandling(). Please contact the developpers");
					}
				    break;
				case END_OF_FIGHT:
					aboutToStop = true;
					break;
				case HEAL:
				default:
					errorReport(
								"The request sent by the server is handled by the receiving function, but not by serverHandling(). Please contact the developpers");
				}
			}
		}

		sleep(milliseconds(25));
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

	//Reads keypresses
	//If user wants to go to the character menu
	if (K_CHARMENU)
	{
		currentMenu = CHARACTER_CHOOSING;
		logReport("Current menu : Character choosing");
	}
		//If user wants to go to the target menu
	else if (K_TARGMENU)
	{
		currentMenu = TARGET_CHOOSING;
		logReport("Current menu : Target choosing");
	}
		//If user wants to go to the ability menu
	else if (K_ABILMENU)
	{
		currentMenu = ABILITY_CHOOSING;
		logReport("Current menu : Ability choosing");
	}
		//If user wants to go to the spell menu
	else if (K_SPELLMENU)
	{
		currentMenu = SPELL_CHOOSING;
		logReport("Current menu : Spell choosing");
	}
		//If user wants to attack
	else if (K_WEAPATK)
	{
		sendToServer(*currentCharacter, *currentCharacter->getTarget(), WEAPON_ATTACK);
	}
		//If user wants to go back to main menu
	else if (K_MAINMENU)
	{
		currentMenu = MAIN;
		logReport("Current menu : Main");
	}
		//If user selects the number 1
	else if (K_SELEC1)
	{
		selectorVariable = 0;
	}
		//If user selects the number 2
	else if (K_SELEC2)
	{
		selectorVariable = 1;
	}
		//If user selects the number 3
	else if (K_SELEC3)
	{
		selectorVariable = 2;
	}
		//If user selects the number 4
	else if (K_SELEC4)
	{
		selectorVariable = 3;
	}
		//If user selects the number 5
	else if (K_SELEC5)
	{
		selectorVariable = 4;
	}
		//If user selects the number 6
	else if (K_SELEC6)
	{
		selectorVariable = 5;
	}
		//If user wants to go to the previous page
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

		//If user wants to go to the next page
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

	//If a selector key was pressed
	if (K_SELEC && selectorVariable != -1)
	{
		//Only runs tests for Character and target choosing if selector 6 was not pressed
		if (K_CHARSELEC)
		{
			switch (currentMenu)
			{
				case CHARACTER_CHOOSING:
					//Only changes the chosen character if he is still alive
					if (currentTeam->at(selectorVariable).getEntity()->isAlive())
					{
						currentCharacter = &currentTeam->at(selectorVariable);
						logReport("New character : " + currentCharacter->getEntity()->getName());
					}
			        break;

				case TARGET_CHOOSING:
					//Only changes the target if he is still alive
					if (currentEnemies->at(selectorVariable).getEntity()->isAlive())
					{
						currentCharacter->changeTarget(&currentEnemies->at(selectorVariable));
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
				if (currentCharacter->getEntity()->getKnownAbilities().size() >= abilityPage*6 + selectorVariable + 1)
				{
					sendToServer(*currentCharacter,
					             *currentCharacter->getTarget(),
					             ABILITY,
					             currentCharacter->getEntity()->getKnownAbilities().at(abilityPage*6 + selectorVariable)->name);
				}
		        break;

			case SPELL_CHOOSING:
				if (currentCharacter->getEntity()->getKnownSpells().size() >= spellPage*6 + selectorVariable + 1)
				{
					sendToServer(*currentCharacter,
					             *currentCharacter->getTarget(),
					             SPELL,
					             currentCharacter->getEntity()->getKnownSpells().at(spellPage*6 + selectorVariable)->name);
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

void Combat::sendToServer(CombatEntity &attacker, CombatEntity &target, AttackType type, string spellName)
{
	Packet           packetToSend;
	InteractionInfos informationsToSend{attacker.getEntity()->getID(), target.getEntity()->getID(), type, spellName};

	createPacket(packetToSend, informationsToSend, CTS_INTERACTION);

	onlineMutex.lock();
	if (onlinePort.send(packetToSend) != Socket::Done)
	{
		errorReport("Unable to send informations to combat server");
	}
	onlineMutex.unlock();
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

void CombatEntity::operator=(const CombatEntity &a)
{
	entity              = a.entity;
	target              = a.target;
	effects             = a.effects;
	lastInteractionTime = a.lastInteractionTime;
	interactionCooldown = a.interactionCooldown;
}
