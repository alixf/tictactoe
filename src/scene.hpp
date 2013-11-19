#ifndef SCENE_HPP
#define SCENE_HPP

#include <SFML/Graphics.hpp>
#include <aSFML/EventManager.hpp>

class Scene : public sf::EventManager::Listener
{
public :
    enum Type {NONE, GAME};

    Scene()
    {
    }

    virtual ~Scene()
    {
    }

    virtual Type draw(sf::RenderWindow& window) = 0;

protected :
    sf::Clock m_clock;
};

#endif // SCENE_HPP
