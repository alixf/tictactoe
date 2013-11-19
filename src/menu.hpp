#ifndef MENU_HPP
#define MENU_HPP

#include <aSFML/ui.hpp>
#include "scene.hpp"

class Menu : public Scene
{
public :
    Menu();
    ~Menu();

    bool onEvent(const sf::Event& event);
    Type draw(sf::RenderWindow& window);

private :
    void play();

    sf::ui::Button m_playButton;
    bool m_playClicked;
};

#endif // MENU_HPP
