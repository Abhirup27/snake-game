#pragma once
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"
#include "State.hpp"
#include "StateMachine.hpp"
extern sf::Texture g_texture;
extern sf::Font g_font;

class Game : public Engine::State {
private:
  sf::RenderWindow &window;
  Engine::StateMachine &m_stateMachine;

  sf::Sprite m_snake;
  sf::Vector2f movement;
  sf::Sprite m_food;

  float moveSpeed;

public:
  Game(Engine::StateMachine &stateMachine, sf::RenderWindow &window)
      : m_stateMachine(stateMachine), m_snake(g_texture), m_food(g_texture),
        moveSpeed(60.0F), movement(0.0F, 0.0F), window(window) {}

  void Init() override;
  void HandleInput(sf::RenderWindow &window, sf::View &view) override;
  void HandleResize(sf::RenderWindow &window, sf::View &view,
                    sf::Vector2f size) override;

  void Update(float dt, sf::RenderWindow &window) override;

  void Draw(sf::RenderWindow &window, sf::View &view) override;
  void Pause() override;
  void Resume() override;

  sf::Vector2f getRandomPosition(const sf::RenderWindow &window,
                                 const sf::FloatRect &spriteBounds);
};
