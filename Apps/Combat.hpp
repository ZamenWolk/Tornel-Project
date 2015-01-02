#ifndef APPS_COMBAT_HPP
#define APPS_COMBAT_HPP

#include <string>
#include <SFML/Graphics.hpp>

#include "App.hpp"
#include "../Classes/CharEntities/CombatEntity.hpp"
#include "../Enums/Combat.hpp"
#include "../Classes/Indexes/IndexesIndex.hpp"
#include "../Classes/Singleton.hpp"

class Combat : public App
{
public:

    Combat();

    virtual void Start();

    virtual std::string Run(sf::RenderWindow &window, std::map<std::string, App *> &apps);

    virtual void Exit();

    int setupServer(std::vector<CombatEntity> yourTeam, Controls controlTeam1, Controls controlTeam2, std::string IPAddress = "localhost", unsigned short addressPort = 2715);

    /**
    * \todo Enhance so it makes real things
    */

    std::string endOfCombat();

    bool combatChecking();

    int fillFightersVector(std::vector<CombatEntity> &teamVector, bool isTeam1);

protected:

    void serverHandling();

    CombatEntity *IDToEntity(unsigned long entityID);

    void keyboardInstructions(std::vector<CombatEntity> *currentTeam, std::vector<CombatEntity> *currentEnemies);

    void checkActionToSend(CombatEntity &attacker, CombatEntity &target, AttackType type, int baseDamage, Skill* skill = singleton<IndexesIndex>().skillIndex.searchByName());

    void sendToServer(CombatEntity &attacker, CombatEntity &target, AttackType type, int baseDamage, std::string skillName = "");

    std::vector<CombatEntity> team1Fighters,
                              team2Fighters;
    Controls                  team1Control,
                              team2Control;
    bool                      team1EventProcessed,
                              team2EventProcessed,
                              aboutToStop;
    sf::TcpSocket             onlinePort;
    sf::Mutex                 onlineMutex;
};

#endif