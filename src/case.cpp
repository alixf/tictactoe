#include "case.hpp"
#include <aSFML/TextureManager.hpp>
#include <aSFML/Animator.hpp>
#include <iostream>

Case::Case(const sf::FloatRect& rect, const sf::Color& backgroundColor) :
m_type(NONE),
m_background(sf::Vector2f(rect.width, rect.height))
{
	m_background.setPosition(rect.left, rect.top);
    m_sprite.setOrigin(rect.width/2, rect.height/2);
    m_sprite.setPosition(rect.left+rect.width/2, rect.top+rect.height/2);

    setBackgroundColor(backgroundColor);
}

Case::~Case()
{
}

void Case::setType(Type type)
{
    if(m_type != type)
    {
        m_type = type;

        switch(m_type)
        {
        case CIRCLE :
            m_sprite.setTexture(sf::TextureManager::getInstance().get("textures/circle.png"));
            // Appearing animations
            sf::Animator::getInstance().addAnimation(m_sprite, sf::Animator::SCALE, 0.f, .25f, sf::Vector2f(0.f, 0.f), sf::Vector2f(1.f, 1.f));
            sf::Animator::getInstance().addAnimation(m_sprite, sf::Animator::COLOR, 0.f, .25f, sf::Color(255,255,255,0), sf::Color::White);
            break;

        case CROSS :
            m_sprite.setTexture(sf::TextureManager::getInstance().get("textures/cross.png"));
            // Appearing animations
            sf::Animator::getInstance().addAnimation(m_sprite, sf::Animator::SCALE, 0.f, .25f, sf::Vector2f(0.f, 0.f), sf::Vector2f(1.f, 1.f));
            sf::Animator::getInstance().addAnimation(m_sprite, sf::Animator::COLOR, 0.f, .25f, sf::Color(255,255,255,0), sf::Color::White);
            break;

        case NONE :
            // Disapearing animations
            sf::Animator::getInstance().addAnimation(m_sprite, sf::Animator::SCALE, 0.f, .25f, sf::Vector2f(1.f, 1.f), sf::Vector2f(0.f, 0.f));
            sf::Animator::getInstance().addAnimation(m_sprite, sf::Animator::COLOR, 0.f, .25f, sf::Color::White, sf::Color(255,255,255,0));
            break;
        }
    }
}

Case::Type Case::getType() const
{
    return m_type;
}

void Case::setBackgroundColor(const sf::Color& backgroundColor)
{
    m_background.setFillColor(backgroundColor);
}

bool Case::operator==(const Case& otherCase)
{
    return m_type == otherCase.m_type;
}

bool Case::operator==(const Type& type)
{
    return m_type == type;
}

bool Case::operator!=(const Case& otherCase)
{
    return m_type != otherCase.m_type;
}

bool Case::operator!=(const Type& type)
{
    return m_type != type;
}

void Case::draw(sf::RenderWindow& window)
{
    window.draw(m_background);
    if(m_sprite.getTexture() != NULL)
        window.draw(m_sprite);
}
