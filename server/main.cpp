#include <iostream>
#include <SFML/Network.hpp>

#include "FightSubserver.hpp"
#include "fonctor.hpp"

using namespace std;
using namespace sf;

int main()
{
	bool                     stopServer(false);
	TcpListener              listener;
	unsigned int             subserverNumber(0);
	vector<FightSubserver *> subservers;
	vector<ServerClient *>   clientsVector;
	SocketSelector           selector;
	InputFonctor             input(&subservers, stopServer);
	Thread                   inputThread(input);

	listener.listen(2715);

	logReport("How many fights do you want to host simultaneously ?");
	cin >> subserverNumber;

	for (int i = 0; i != subserverNumber; i++)
	{
		FightSubserver *newSubserver = new FightSubserver();
		subservers.push_back(newSubserver);
	}

	for (vector<FightSubserver *>::iterator it = subservers.begin(); it != subservers.end(); it++)
	{
		clientsVector.push_back(&(*it)->clients[0]);
		clientsVector.push_back(&(*it)->clients[1]);
	}

	selector.add(listener);

	for (int i = 0; i < clientsVector.size(); i++)
	{
		selector.add(*clientsVector[i]);
	}

	inputThread.launch();

	logReport("The server host is now ready and working !");

	logReport("Searching for event");

	while (!stopServer)
	{
		if (selector.wait(milliseconds(200)))
		{
			logReport("Found something !");

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
						logReport("Received info !");

						EventsUnion   eventsInfos;
						SentInfosType infosType;
						Packet        receivedPacket;

						clientsVector[i]->receive(receivedPacket);
						infoTypeInPacket(receivedPacket, infosType);

						switch (infosType)
						{
							case CTS_INTERACTION:
								deconstructPacket(receivedPacket, eventsInfos.intEv, infosType);
						        subservers[i/2]->newEvent(infosType, eventsInfos, (i%2 == 0));
						        break;
							case VERSION_NUMBER:
								deconstructPacket(receivedPacket, eventsInfos.versEv, infosType);
						        subservers[i/2]->newEvent(infosType, eventsInfos, (i%2 == 0));
						        break;
							case CTS_TEAM_DATA:
								deconstructPacket(receivedPacket, eventsInfos.teamEv, infosType);
						        subservers[i/2]->newEvent(infosType, eventsInfos, (i%2 == 0));
						        break;
							case TIME:
								deconstructPacket(receivedPacket, eventsInfos.timeEv, infosType);
						        subservers[i/2]->newEvent(infosType, eventsInfos, (i%2 == 0));
						        break;
							case PING:
							{
								Packet pong;
								int    buffer(0);
								createPacket(pong, buffer, PONG);
								clientsVector[i]->send(pong);
							}
						        break;
							case PONG:
								break;
							default:
								errorReport("The information type contained in the packet is not supported be the server");
						}
					}
				}
			}

			logReport("Searching for event");
		}

		sleep(milliseconds(25));
	}

	logReport("Stopping the server");

	inputThread.wait();
	for (vector<ServerClient *>::iterator it = clientsVector.begin(); it != clientsVector.end(); it++)
	{
		selector.remove(**it);
	}

	while (subservers.size() > 0)
	{
		subservers.pop_back();
	}

	logReport("End of program", true);

	return EXIT_SUCCESS;
}
