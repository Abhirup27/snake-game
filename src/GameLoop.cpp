
#include "GameLoop.hpp"
#include "AssetManager.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/View.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Keyboard.hpp"
#include <optional>

void Game::Init() {
  Engine::AssetManager *assets = Engine::AssetManager::GetInstance();

  /* if (!assets->HasTexture("snake")) {
     assets->LoadTexture("snake", "snake.png");
   } */
  if (!assets->HasTexture("apfel")) {
    assets->LoadTexture("apfel", "apple.png");
  }

  //  m_snake.setTexture(assets->GetTexture("snake"), true);
  m_snake.setOrigin({8, 16});
  m_snake.setPosition({640U / 2.0F, 480U / 2.0F});
  movement.y = moveSpeed * 0.04 * -1;

  m_food.setTexture(assets->GetTexture("apfel"), true);
  m_food.setOrigin({16, 16});
  m_food.setPosition(getRandomPosition(window, m_food.getGlobalBounds()));
}
void Game::Draw(sf::RenderWindow &window, sf::View &view) {
  window.setView(view);
  window.draw(m_snake);
  window.draw(m_food);
}
void Game::Update(float dt, sf::RenderWindow &window) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
    movement.y = 0.0F;
    movement.x = moveSpeed * dt * -1;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
    movement.y = 0.0F;
    movement.x = moveSpeed * dt;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
    movement.x = 0.0F;
    movement.y = moveSpeed * dt * -1;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
    movement.x = 0.0F;
    movement.y = moveSpeed * dt;
  }

  // Apply movement to sprite
  m_snake.move(movement);

  // Keep sprite within window bounds
  sf::Vector2f position = m_snake.getPosition();
  sf::Vector2u windowSize = window.getSize();
  sf::FloatRect spriteBounds = m_snake.getGlobalBounds();

  if (position.x < 0)
    m_snake.setPosition({0, position.y});
  if (position.y < 0)
    m_snake.setPosition({position.x, 0});
  if (position.x + spriteBounds.size.x > windowSize.x)
    m_snake.setPosition({windowSize.x - spriteBounds.size.x, position.y});
  if (position.y + spriteBounds.size.y > windowSize.y)
    m_snake.setPosition({position.x, windowSize.y - spriteBounds.size.y});

  if (m_snake.getGlobalBounds().contains(m_food.getGlobalBounds().position)) {
    m_food.setPosition(getRandomPosition(window, m_food.getGlobalBounds()));
  }
}

void Game::HandleInput(sf::RenderWindow &window, sf::View &view) {
  while (const std::optional event = window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      window.close();
    }
    if (const auto *resized = event->getIf<sf::Event::Resized>()) {
      HandleResize(window, view, static_cast<sf::Vector2f>(resized->size));
    }
  }
}

void Game::HandleResize(sf::RenderWindow &window, sf::View &view,
                        sf::Vector2f size) {
  view.setSize(size);
  view.setCenter({size.x / 2.0F, size.y / 2.0F});
  window.setView(view);

  // update all the UI and other sprite bounding boxes, origins and positions
}

void Game::Pause() {}
void Game::Resume() {}

sf::Vector2f Game::getRandomPosition(const sf::RenderWindow &window,
                                     const sf::FloatRect &spriteBounds) {
  unsigned int maxX =
      window.getSize().x - static_cast<unsigned int>(spriteBounds.size.x);
  unsigned int maxY =
      window.getSize().y - static_cast<unsigned int>(spriteBounds.size.y);

  return {static_cast<float>(rand() % maxX), static_cast<float>(rand() % maxY)};
}
