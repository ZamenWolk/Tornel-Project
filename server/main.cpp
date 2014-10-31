#include <iostream>
#include <SFML/Network.hpp>

#include "../src/operators.hpp"
#include "FightSubserver.hpp"
#include "fonctor.hpp"

using namespace std;
using namespace sf;

int main()
{
	bool 					stopServer(false);
    TcpListener             listener;
    unsigned int            subserverNumber(0);
    vector<FightSubserver*> subservers;
    vector<ServerClient*>   clientsVector;
    SocketSelector          selector;
    inputFonctor input(&subservers, stopServer);
    Thread                  inputThread(input);

    listener.listen(2715);

    cout << "How many fights do you want to host simultaneously ?" << endl;
    cin >> subserverNumber;

    for (int i=0; i != subserverNumber; i++)
    {
        FightSubserver* newSubserver= new FightSubserver();
        subservers.push_back(newSubserver);
    }

    for (vector<FightSubserver*>::iterator it = subservers.begin(); it != subservers.end(); it++)
    {
         clientsVector.push_back(&(*it)->m_clients[0]);
         clientsVector.push_back(&(*it)->m_clients[1]);
    }

    selector.add(listener);

    for (int i = 0; i < clientsVector.size(); i++)
    {
        selector.add(*clientsVector[i]);
    }

	inputThread.launch();

    cout << "The server host is now ready and working !" << endl;

	cout << "Searching for event" << endl;

	while (!stopServer)
    {
        if (selector.wait(milliseconds(200)))
        {
            cout << "Found something !" << endl;

            if (selector.isReady(listener))
            {
                FightSubserver *openSubserver(nullptr);
                if (findOpenSubserver(subservers, &openSubserver))
                {
                    openSubserver->connect(&listener);
                }
            }
            else
            {
                for (int i = 0; i < clientsVector.size(); i++)
                {
                    if (selector.isReady(*clientsVector[i]) && subservers[i/2]->isLastEventTreated())
                    {
                        cout << "Received info !" << endl;

                        InteractionInfos                receivedInteraction;
                        vector<EntityInformations>      receivedTeam;
                        bool                            isTeam1;
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
                            receivedPacket >> receivedTeam;
                            isTeam1 = (i%2 == 0);

                            subservers[i/2]->newEvent(receivedTeam, isTeam1);
                        }
                    }
                }
            }

			cout << "Searching for event" << endl;
		}

        sf::sleep(sf::milliseconds(25));
    }

	std::cout << "Stopping the server" << std::endl;

    inputThread.wait();
    for (vector<ServerClient*>::iterator it = clientsVector.begin(); it != clientsVector.end(); it++)
    {
        selector.remove(**it);
    }

    while (subservers.size() > 0)
    {
        subservers.pop_back();
    }

    return EXIT_SUCCESS;
}
