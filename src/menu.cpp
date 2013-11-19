#include "menu.hpp"

#include <boost/bind.hpp>
#include <boost/ref.hpp>

Menu::Menu() : Scene(),
m_playButton(L"Jouer", 0,0,100,100),
m_playClicked(false)
{
    m_playButton.onClick(boost::bind(&Menu::play, boost::ref(*this)));
}

Menu::~Menu()
{
}

bool Menu::onEvent(const sf::Event& event)
{
	return false;
}

Scene::Type Menu::draw(sf::RenderWindow& window)
{
    m_playButton.draw(window);

    if(m_playClicked)
        return GAME;
    return NONE;
}

void Menu::play()
{
    m_playClicked = true;
}
