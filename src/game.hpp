#ifndef GAME_HPP
#define GAME_HPP

#include "scene.hpp"
#include "case.hpp"

class Game : public Scene
{
public :
    Game();
    ~Game();

    bool onEvent(const sf::Event& event);
    Type draw(sf::RenderWindow& window);

private :
    bool check();
    void incrementScore(const Case::Type& player);

    bool m_gameWon;
    unsigned int m_playedTurns;
    Case::Type m_turn;
    sf::Sprite m_turnSprite;
    Case m_cases[9];
    unsigned int m_checkset[8][3];

    unsigned int m_score[2];
    sf::Text m_scoreText;
    sf::Sprite m_circleScoreSprite;
    sf::Sprite m_crossScoreSprite;

    sf::RectangleShape m_gridBackground;
};

#endif // GAME_HPP
