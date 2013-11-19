#ifndef CASE_HPP
#define CASE_HPP

#include <SFML/Graphics.hpp>

class Case
{
public :
    enum Type{NONE, CROSS, CIRCLE};

    Case(const sf::FloatRect& rect = sf::FloatRect(), const sf::Color& backgroundColor = sf::Color::White);
    ~Case();

    void setType(Type type);
    Type getType() const;

    void setBackgroundColor(const sf::Color& backgroundColor);

    bool operator==(const Case& otherCase);
    bool operator==(const Type& type);
    bool operator!=(const Case& otherCase);
    bool operator!=(const Type& type);

    void draw(sf::RenderWindow& window);

private :
    Type m_type;
    sf::RectangleShape m_background;
    sf::Sprite m_sprite;
};

#endif // CASE_HPP
