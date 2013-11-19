#include "game.hpp"
#include <sstream>
#include <aSFML/FontManager.hpp>
#include <aSFML/TextureManager.hpp>
#include <aSFML/Animator.hpp>
#include <iostream>

namespace
{
    const sf::Color caseColor1(255,255,255,10);
    const sf::Color caseColor2(255,255,255,25);
    const sf::Color gridBorderColor(255,255,255,50);
    const sf::Color circleWinColor(255,0,0,25);
    const sf::Color crossWinColor(0,128,255,25);
    const sf::Color textColor(255,255,255,200);
}

Game::Game() :Scene(),
m_gameWon(false),
m_playedTurns(0),
m_turn(Case::CIRCLE),
m_turnSprite(sf::TextureManager::getInstance().get("textures/circle.png")),
m_scoreText("Tour :\n\nScore :\n   0\n   0", sf::FontManager::getInstance().get("fonts/candara.ttf")),
m_circleScoreSprite(sf::TextureManager::getInstance().get("textures/smallCircle.png")),
m_crossScoreSprite(sf::TextureManager::getInstance().get("textures/smallCross.png")),
m_gridBackground(sf::RectangleShape(sf::Vector2f(300,300)))
{
	m_gridBackground.setPosition(10,10);

	 //sf::RectangleShape(sf::FloatRect(10,10,300,300),sf::Color::White,1.f,gridBorderColor)

    m_score[0] = 0; // Circle Player
    m_score[1] = 0; // Cross Player

    m_scoreText.setPosition(sf::Vector2f(330.f,10.f));
    m_scoreText.setColor(textColor);
    m_turnSprite.setPosition(sf::Vector2f(410.f,5.f));
    m_circleScoreSprite.setPosition(sf::Vector2f(325.f,130.f));
    m_crossScoreSprite.setPosition(sf::Vector2f(325.f,167.f));

    // Cases Initialisation
    for(unsigned int i = 0; i < 9; ++i)
        m_cases[i] = Case(sf::FloatRect(i%3*100+10,i/3*100+10,100,100), (i%2) ? caseColor1 : caseColor2);

    // Checkset Initialisation
    // Horizontal lines
    m_checkset[0][0] = 0; m_checkset[0][1] = 1; m_checkset[0][2] = 2;
    m_checkset[1][0] = 3; m_checkset[1][1] = 4; m_checkset[1][2] = 5;
    m_checkset[2][0] = 6; m_checkset[2][1] = 7; m_checkset[2][2] = 8;
    // Vertical lines
    m_checkset[3][0] = 0; m_checkset[3][1] = 3; m_checkset[3][2] = 6;
    m_checkset[4][0] = 1; m_checkset[4][1] = 4; m_checkset[4][2] = 7;
    m_checkset[5][0] = 2; m_checkset[5][1] = 5; m_checkset[5][2] = 8;
    // Diagonal lines
    m_checkset[6][0] = 0; m_checkset[6][1] = 4; m_checkset[6][2] = 8;
    m_checkset[7][0] = 2; m_checkset[7][1] = 4; m_checkset[7][2] = 6;
}

Game::~Game()
{
}

bool Game::onEvent(const sf::Event& event)
{
    if(event.type == sf::Event::MouseButtonPressed)
    {
        if(m_gameWon)
        {
            // Reset the grid
            for(unsigned int i = 0; i < 9; ++i)
            {
                m_cases[i].setType(Case::NONE);
                m_cases[i].setBackgroundColor((i%2) ? caseColor1 : caseColor2);
            }
            m_gameWon = false;
            m_playedTurns = 0;
        }
        else if(sf::FloatRect(10.f,10.f,300.f,300.f).contains(event.mouseButton.x, event.mouseButton.y)) // if mouse is on the grid
        {
            int caseNumber = static_cast<int>((event.mouseButton.y-10)/100)*3+static_cast<int>((event.mouseButton.x-1)/100);

            if(m_cases[caseNumber] == Case::NONE)
            {
                m_cases[caseNumber].setType(m_turn);
                m_playedTurns++;

                // Check the grid
                if(check())
                {
                    m_gameWon = true;
                    incrementScore(m_turn);
                }
                if(m_playedTurns == 9 && !m_gameWon)
                    m_gameWon = true;

                // Change turn
                m_turn = (m_turn == Case::CIRCLE) ? Case::CROSS : Case::CIRCLE;
                if(m_turn == Case::CIRCLE)
                    m_turnSprite.setTexture(sf::TextureManager::getInstance().get("textures/circle.png"));
                else
                    m_turnSprite.setTexture(sf::TextureManager::getInstance().get("textures/cross.png"));
            }
        }
    }

    return false;
}

Scene::Type Game::draw(sf::RenderWindow& window)
{
    sf::Animator::getInstance().apply();

    //window.draw(m_gridBackground);
    for(unsigned int i = 0; i < 9; ++i)
        m_cases[i].draw(window);

    m_scoreText.move(0.f,1.f);
    m_scoreText.setColor(sf::Color::Black);
    window.draw(m_scoreText);
    m_scoreText.move(0.f,-1.f);
    m_scoreText.setColor(textColor);
    window.draw(m_scoreText);
    window.draw(m_turnSprite);
    window.draw(m_circleScoreSprite);
    window.draw(m_crossScoreSprite);

    return NONE;
}

bool Game::check()
{
    bool win = false;
    for(unsigned int i = 0; i < 8; ++i)
    {
        if(m_cases[m_checkset[i][0]] == m_cases[m_checkset[i][1]] && m_cases[m_checkset[i][0]] == m_cases[m_checkset[i][2]] && m_cases[m_checkset[i][0]] != Case::NONE)
        {
            sf::Color winColor = (m_cases[m_checkset[i][0]] == Case::CIRCLE) ? circleWinColor : crossWinColor;
            m_cases[m_checkset[i][0]].setBackgroundColor(winColor);
            m_cases[m_checkset[i][1]].setBackgroundColor(winColor);
            m_cases[m_checkset[i][2]].setBackgroundColor(winColor);
            win = true;
        }
    }
    return win;
}

void Game::incrementScore(const Case::Type& player)
{
    if(player == Case::CIRCLE)
        m_score[0]++;
    else
        m_score[1]++;

    std::ostringstream oss;
    oss << "Tour :\n\nScore :\n   " << m_score[0] << "\n   " << m_score[1];
    m_scoreText.setString(oss.str());
}
