#include "FightSubserver.hpp"
#include "ServerClients.hpp"

using namespace std;

void connectionHandler(std::vector<FightSubserver*> &subservers, std::vector<ServerClient*> &clientsVector, sf::SocketSelector *selector, sf::TcpListener *listener)
{
    while (!aboutToStop)
    {
        //cout << "searching for event" << endl;

        if (selector->wait())
        {
            cout << "Found something !" << endl;

            if (selector->isReady(*listener))
            {
                FightSubserver *openSubserver(nullptr);

                if (findOpenSubserver(&subservers, openSubserver))
                {
                    ServerClient* clientSocket;
                    clientSocket = openSubserver->connect(listener);
                }
            }
            else
            {
                for (int i = 0; i < clientsVector.size(); i++)
                {
                    if (selector->isReady(*clientsVector[i]) && subservers[i/2]->isLastEventTreated())
                    {
                        std::cout << "Received info !" << std::endl;

                        InteractionInfos                receivedInteraction;
                        std::vector<EntityInformations> receivedTeam;
                        bool                            concernedTeam;
                        SentInfosType                   infosType;
                        sf::Packet                      receivedPacket;

                        clientsVector[i]->receive(receivedPacket);
                        receivedPacket >> infosType;

                        if (infosType == FIGHT_INTERACTION)
                        {
                            receivedPacket >> receivedInteraction;
                            subservers[i/2]->newEvent(receivedInteraction);
                        }
                        else if (infosType == TEAM_DATA)
                        {
                            receivedPacket >> concernedTeam;
                            receivedPacket >> receivedTeam;
                            subservers[i/2]->newEvent(receivedTeam, concernedTeam);
                        }
                    }
                }
            }
        }
        else
        {
            cout << "Couldn't find anything" << endl;
        }

        sf::sleep(sf::milliseconds(25));
    }
}
