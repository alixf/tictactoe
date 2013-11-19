#include <SFML/Graphics.hpp>
#include "game.hpp"
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(520,320,32), "Tic Tac Toe", sf::Style::Close, sf::ContextSettings(24,8,0));
    window.setFramerateLimit(60);

    Scene* scene = new Game;

    const sf::Color backgroundColor(50,50,50);

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
            sf::EventManager::getInstance().postEvent(event);
        }

        window.clear(backgroundColor);

        switch(scene->draw(window))
        {
        case Scene::GAME :
            delete scene;
            scene = new Game;
            break;

        default :
            break;
        }

        window.display();
    }

    // Delete scene if needed
    if(scene)
        delete scene;

    return 0;
}
