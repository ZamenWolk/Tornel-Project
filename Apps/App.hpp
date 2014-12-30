#include <string>
#include <SFML/Graphics.hpp>
#include <Thor/Input.hpp>

class App
{
public:

    App();
    ~App();

    virtual void Start();
    virtual std::string Run(sf::RenderWindow &window, std::map<std::string, App *> &apps) = 0;
    virtual void Exit();

protected:

    bool isRunning;
    thor::ActionMap<std::string> eventsMap;
    sf::Clock clock;

};