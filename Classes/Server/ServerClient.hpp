#include <SFML/Network.hpp>

class ServerClient : public sf::TcpSocket
{
public:

    ServerClient();

    void connect(sf::TcpListener &listener, sf::SocketSelector *selector = 0);

    void disconnect();

    sf::Socket::Status send(sf::Packet &packet);

    sf::Socket::Status receive(sf::Packet &packet);

    bool isSocketFree() const;

    sf::Time timeSinceLastInteraction() const;

protected:

    bool               isFree;
    sf::SocketSelector *socketSelector;
    sf::Clock          lastInteractionClock;
};