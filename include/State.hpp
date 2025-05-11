#pragma once
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/View.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Event.hpp"
#include <SFML/Graphics.hpp>

namespace Engine {
class State {

public:
  virtual ~State() {}
  virtual void Init() = 0;
  virtual void HandleInput(sf::RenderWindow &window, sf::View &view) = 0;
  virtual void HandleResize(sf::RenderWindow &window, sf::View &view,
                            sf::Vector2f size) = 0;
  virtual void Update(float deltaTime, sf::RenderWindow &window) = 0;
  virtual void Draw(sf::RenderWindow &window, sf::View &view) = 0;
  virtual void Pause() {}
  virtual void Resume() {}
};
} // namespace Engine
