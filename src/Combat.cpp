#include "Combat.hpp"

CombatEntity::CombatEntity(EntityModel *entity):
						entity(entity),
						target(nullptr),
						effects(entity->getEffects(), entity->basicAttackEffects()),
						ID((unsigned long)((long long int)this%4200000000)),
						lastInteractionTime(sf::milliseconds(0)),
						interactionCooldown(sf::milliseconds(0))
{

}

void CombatEntity::changeTarget(CombatEntity *newTarget)
{
	if (newTarget->entity->isAlive())
		target = newTarget;
}

EntityModel* CombatEntity::getEntity() const
{
	return entity;
}

CombatEntity* CombatEntity::getTarget() const
{
	return target;
}

CombatEffects CombatEntity::getEffects() const
{
	return effects;
}

unsigned long CombatEntity::getID() const
{
	return ID;
}

Combat::Combat(std::vector<CombatEntity> team1Fighters,
			   std::vector<CombatEntity> team2Fighters,
			   const Controls team1Control,
			   const Controls team2Control):
			team1Fighters(team1Fighters),
			team2Fighters(team2Fighters),
			team1Control(team1Control),
			team2Control(team2Control),
			team1EventProcessed(true),
			team2EventProcessed(true),
			aboutToStop(false),
			team1Thread(std::bind(&Combat::teamInstructions, this, true)),
			team2Thread(std::bind(&Combat::teamInstructions, this, false)),
			serverThread(&Combat::serverHandling, this),
			onlineMutex()
{
	while (team1Fighters.size() >= 5)
	{
		team1Fighters.pop_back();
	}

	while (team2Fighters.size() >= 5)
	{
		team2Fighters.pop_back();
	}

	combatChecking();
}

void Combat::changeEnemyTeam(std::vector<CombatEntity> newTeam)
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
	for (std::vector<CombatEntity>::iterator it = newTeam.begin(); it != newTeam.end(); it++)
	{
		team2Fighters.push_back(*it);
	}
}

int Combat::combatRunning(sf::RenderWindow &window, std::string IPAddress, unsigned short addressPort)
{
	setUpServer(IPAddress, addressPort);

	//Launches the threads
	std::cout << "The game begins !" << std::endl;
	team1Thread.launch();
	team2Thread.launch();

	//Catches events to be processed by the threads until the fight stops
	while (!aboutToStop)
	{
		indexes.keyboardMap.update(window);

		team1EventProcessed = false;
		team2EventProcessed = false;

		while (!team1EventProcessed && !team2EventProcessed)
		{
			sf::sleep(sf::milliseconds(25));
		}
	}

	return endOfCombat();
}

void Combat::setUpServer(std::string IPAddress, unsigned short addressPort)
{
	sf::Packet                versionNumber, charactersPacket, packetFromServer, timePacket;
	VersionNumber             version(AutoVersion::STATUS,
									  AutoVersion::MAJOR,
									  AutoVersion::MINOR,
									  AutoVersion::PATCH);
	std::vector<CombatEntity> teamFromServer;
	sf::Time                  pingTime(sf::milliseconds(0)), pongTime(sf::milliseconds(0)), timeUntilLaunch(sf::milliseconds(0)),
							  timeAtLaunchDelay(sf::milliseconds(0));

	//Connects to the server
	onlineMutex.lock();
	if (onlinePort.connect(IPAddress, addressPort) != sf::Socket::Done)
	{
		errorReport("Can't connect to the server");
	}

	//Sends version number to the server
	createPacket(versionNumber, version, VERSION_NUMBER);
	if (onlinePort.send(versionNumber) != sf::Socket::Done)
	{
		errorReport("Can't send version information to server");
	}

	//Sends team's character vector to the server
	createPacket(charactersPacket, team1Fighters, TEAM_DATA);
	if (onlinePort.send(charactersPacket) != sf::Socket::Done)
	{
		errorReport("Can't send team informations to server");
	}

	//Receives opposite team's character vector from the server
	if (onlinePort.receive(packetFromServer) != sf::Socket::Done)
	{
		errorReport("Can't receive team informations from server");
	}
	packetFromServer >> teamFromServer;
	changeEnemyTeam(teamFromServer);

	//Calculates the ping with the server so both clients can begin at the same time
	pingTime = mainClock.getElapsedTime();
	createPacket(timePacket, pingTime, PING);
	if (onlinePort.send(timePacket) != sf::Socket::Done)
	{
		errorReport("Can't ping server");
	}

	if (onlinePort.receive(packetFromServer) != sf::Socket::Done)
	{
		errorReport("Can't receive pong from server");
	}
	pongTime = mainClock.getElapsedTime();

	{
		int x;
		while (timePacket >> x);
	}

	//Sends latency to server
	createPacket(timePacket, pongTime - pingTime, PING);
	if (onlinePort.send(timePacket) != sf::Socket::Done)
	{
		errorReport("Can't send latency to server");
	}

	{
		int x;
		while (timePacket >> x);
	}

	//Receives the delay until the beginning of the fight from the server
	if (onlinePort.receive(timePacket) != sf::Socket::Done)
	{
		errorReport("Can't receive launch delay from server");
	}
	onlineMutex.unlock();
	timePacket >> timeUntilLaunch;
	timeAtLaunchDelay = mainClock.getElapsedTime();

	//Waits until the delay until the beginning of fight is over
	while (mainClock.getElapsedTime() < timeAtLaunchDelay + timeUntilLaunch)
	{
		sf::sleep(sf::milliseconds(50));
	}
}

bool Combat::endOfCombat()
{
	aboutToStop = true;
	sf::Packet packetFromServer;
	bool       wonBattle;

	//Terminates all server threads
	team1Thread.wait();
	team2Thread.wait();
	serverThread.wait();

	//Receives winner information from server
	onlineMutex.lock();
	if (onlinePort.receive(packetFromServer) != sf::Socket::Done)
	{
		errorReport("Can't receive winner informations from server");
	}
	onlineMutex.unlock();
	packetFromServer >> wonBattle;

	return wonBattle;
}

void Combat::teamInstructions(bool team1)
{
	std::vector<CombatEntity> *currentTeam(nullptr), *currentEnemies(nullptr);
	const Controls            *currentControl(nullptr);
	bool                      *currentTeamEventProcessed(nullptr);

	//Sets up all the pointers so the program can be the same for both team
	if (team1)
	{
		currentTeam               = &team1Fighters, currentEnemies = &team2Fighters;
		currentControl            = &team1Control;
		currentTeamEventProcessed = &team1EventProcessed;
	}
	else
	{
		currentTeam               = &team2Fighters, currentEnemies = &team1Fighters;
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

		sf::sleep(sf::milliseconds(25));
	}
}

void Combat::serverHandling()
{
	while (!aboutToStop)
	{
		sf::Packet       packetFromServer;
		ActionType       actionType;
		SpecialAttribute specialAttribute;
		sf::Uint32       subjectID(0);
		CombatEntity *subject(nullptr);
		sf::Socket::Status result;

		//Receives packet of information from the server
		onlineMutex.lock();
		result = onlinePort.receive(packetFromServer);
		onlineMutex.unlock();

		if (result != sf::Socket::Done && result != sf::Socket::NotReady)
		{
			errorReport("Can't receive informations from server");
		}
		else
		{
			packetFromServer >> actionType;
			packetFromServer >> specialAttribute;
			packetFromServer >> subjectID;
			subject = IDToEntity(subjectID);

			//If no action happened
			if (actionType == NONE)
			{
				//If it is because there is not enough capacity points
				if (specialAttribute == NOT_ENOUGH_CP)
				{
					std::string skillName;
					packetFromServer >> skillName;

					Skill *skill(indexes.skillIndex.searchByName(skillName));

					std::cout << subject->getEntity()->getName() << " needs more Capacity Points to use " << skill->name << std::endl;
				}
					//Reaction not handled by the client
				else
				{
					errorReport(
							"The request sent by the server is handled by the receiving function, but not by serverHandling(). Please contact the developpers",
							0);
				}
			}
				//If damages were dealt
			else if (actionType == DEAL_DAMAGE)
			{
				sf::Uint32 targetID;
				packetFromServer >> targetID;
				CombatEntity *target(IDToEntity(targetID));
				int         attackDamage;
				AttackType  attackType;
				std::string skillName;
				Skill       *skill(nullptr);

				//Searches who was hit
				packetFromServer >> attackDamage;
				packetFromServer >> attackType;

				if (attackType != WEAPON_ATTACK)
				{
					packetFromServer >> skillName;
					skill = indexes.skillIndex.searchByName(skillName);
				}

				//Cjanges target's life and displays it
				target->getEntity()->changeLife(-attackDamage);
				if (specialAttribute == NO_SPECIAL)
				{
					if (attackType == WEAPON_ATTACK)
					{
						std::cout << subject->getEntity()->getName() << " attacked " << target->getEntity()->getName() << ", dealing " << attackDamage << " damages" << std::endl;
					}
					else
					{
						std::cout << subject->getEntity()->getName() << " used " << skill->name << " on " << target->getEntity()->getName() << ", dealing " << attackDamage << " damages" << std::endl;
					}
				}
					//Attribute of attack not handled by function
				else
				{
					errorReport(
							"The request sent by the server is handled by the receiving function, but not by serverHandling(). Please contact the developpers",
							0);
				}
			}
				/**else if (actionType == HEAL)
				{
				if (specialAttribute == NO_SPECIAL)
				{

				}
				else if (specialAttribute == CRITICAL)
				{

				}
				}**/
				//End of fight
			else if (actionType == END_OF_FIGHT)
			{
				aboutToStop = true;
			}
				//Action requested not handled by server
			else
			{
				errorReport(
						"The request sent by the server is handled by the receiving function, but not by serverHandling(). Please contact the developpers",
						0);
			}
		}

		sf::sleep(sf::milliseconds(25));
	}
}

CombatEntity* Combat::IDToEntity(unsigned long entityID)
{
		for (std::vector<CombatEntity>::iterator it = team1Fighters.begin(); it != team1Fighters.end(); it++)
		{
			if (it->getID() == entityID)
			{
				return &*it;
			}
		}

		for (std::vector<CombatEntity>::iterator it = team2Fighters.begin(); it != team2Fighters.end(); it++)
		{
			if (it->getID() == entityID)
			{
				return &*it;
			}
		}

		errorReport("Server sent an unknown fighter ID");
		return &team1Fighters[0];
	}

void Combat::keyboardInstructions(std::vector<CombatEntity> *currentTeam, std::vector<CombatEntity> *currentEnemies)
{

	static CombatMenu currentMenu(MAIN);
	static int        spellPage(0), abilityPage(0);
	static unsigned int selectorVariable(0);
	static CombatEntity *currentCharacter(&currentTeam->at(0));

	//Reads keypresses
	//If user wants to go to the character menu
	if (indexes.keyboardMap.isActive("characterMenu"))
	{
		currentMenu = CHARACTER_CHOOSING;
		std::cout << "Current menu : Character choosing" << std::endl;
	}
		//If user wants to go to the target menu
	else if (indexes.keyboardMap.isActive("targetMenu"))
	{
		currentMenu = TARGET_CHOOSING;
		std::cout << "Current menu : Target choosing" << std::endl;
	}
		//If user wants to go to the ability menu
	else if (indexes.keyboardMap.isActive("abilityMenu"))
	{
		currentMenu = ABILITY_CHOOSING;
		std::cout << "Current menu : Ability choosing" << std::endl;
	}
		//If user wants to go to the spell menu
	else if (indexes.keyboardMap.isActive("spellMenu"))
	{
		currentMenu = SPELL_CHOOSING;
		std::cout << "Current menu : Spell choosing" << std::endl;
	}
		//If user wants to attack
	else if (indexes.keyboardMap.isActive("weaponAttack"))
	{
		sendToServer(*currentCharacter, *currentCharacter->getTarget(), WEAPON_ATTACK);
	}
		//If user wants to go back to main menu
	else if (indexes.keyboardMap.isActive("mainMenu"))
	{
		currentMenu = MAIN;
		std::cout << "Current menu : Main" << std::endl;
	}
		//If user selects the number 1
	else if (indexes.keyboardMap.isActive("selector1"))
	{
		selectorVariable = 0;
	}
		//If user selects the number 2
	else if (indexes.keyboardMap.isActive("selector2"))
	{
		selectorVariable = 1;
	}
		//If user selects the number 3
	else if (indexes.keyboardMap.isActive("selector3"))
	{
		selectorVariable = 2;
	}
		//If user selects the number 4
	else if (indexes.keyboardMap.isActive("selector4"))
	{
		selectorVariable = 3;
	}
		//If user selects the number 5
	else if (indexes.keyboardMap.isActive("selector5"))
	{
		selectorVariable = 4;
	}
		//If user selects the number 6
	else if (indexes.keyboardMap.isActive("selector6"))
	{
		selectorVariable = 5;
	}
		//If user wants to go to the previous page
	else if (indexes.keyboardMap.isActive("prevPage"))
	{
		switch (currentMenu)
		{
			case ABILITY_CHOOSING:
				if (abilityPage > 0)
					abilityPage--;
				std::cout << "Ability page : " << abilityPage << std::endl;
				break;

			case SPELL_CHOOSING:
				if (spellPage > 0)
					spellPage--;
				std::cout << "Spell page : " << spellPage << std::endl;
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
	else if (indexes.keyboardMap.isActive("nextPage"))
	{
		switch (currentMenu)
		{
			case ABILITY_CHOOSING:
				if (currentCharacter->getEntity()->getKnownAbilities().size() >= (abilityPage*6 + 7))
					abilityPage++;
				std::cout << "Ability page : " << abilityPage << std::endl;
				break;

			case SPELL_CHOOSING:
				if (currentCharacter->getEntity()->getKnownSpells().size() >= (spellPage*6 + 7))
					spellPage++;
				std::cout << "Spell page : " << spellPage << std::endl;
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
	if (indexes.keyboardMap.isActive("selector"))
	{
		//Only runs tests for Character and target choosing if selector 6 was not pressed
		if (indexes.keyboardMap.isActive("charSelector"))
		{
			switch (currentMenu)
			{
				case CHARACTER_CHOOSING:
					//Only changes the chosen character if he is still alive
					if (currentTeam->at(selectorVariable).getEntity()->isAlive())
					{
						currentCharacter = &currentTeam->at(selectorVariable);
						std::cout << "New character : " << currentCharacter->getEntity()->getName() << std::endl;
					}
					break;

				case TARGET_CHOOSING:
					//Only changes the target if he is still alive
					if (currentEnemies->at(selectorVariable).getEntity()->isAlive())
					{
						currentCharacter->changeTarget(&currentEnemies->at(selectorVariable));
						std::cout << "New target : " << currentCharacter->getTarget()->getEntity()->getName() << std::endl;
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

		currentMenu = MAIN;
	}
}

void Combat::sendToServer(CombatEntity &attacker, CombatEntity &target, AttackType type, std::string spellName)
{
		sf::Packet       packetToSend;
		InteractionInfos informationsToSend{attacker.getID(), target.getID(), type, spellName};

		packetToSend << informationsToSend;

		onlineMutex.lock();
		if (onlinePort.send(packetToSend) != sf::Socket::Done)
		{
			errorReport("Unable to send informations to combat server");
		}
		onlineMutex.unlock();
	}