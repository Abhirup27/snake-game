#include <SFML/Graphics.hpp>
#pragma region imgui
#include "imgui-SFML.h"
#include "imgui.h"
#include "imguiThemes.h"
#pragma endregion

int main() {
  unsigned int width{640U};
  unsigned int height{480U};
  sf::RenderWindow *window =
      new sf::RenderWindow(sf::VideoMode({width, height}), "Game");

#pragma region imgui
  ImGui::SFML::Init(*window);
  // you can use whatever imgui theme you like!
  // ImGui::StyleColorsDark();
  // imguiThemes::yellow();
  // imguiThemes::gray();
  imguiThemes::green();
  // imguiThemes::red();
  // imguiThemes::gray();
  // imguiThemes::embraceTheDarkness();

  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad
  // Controls
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking
  io.FontGlobalScale = 2.f;
  ImGuiStyle &style = ImGui::GetStyle();
  style.Colors[ImGuiCol_WindowBg].w = 0.5f;
  // style.Colors[ImGuiCol_DockingEmptyBg].w = 0.f;
#pragma endregion

  sf::Clock clock;
  while (window->isOpen()) {

    while (const std::optional event = window->pollEvent()) {
#pragma region imgui
      ImGui::SFML::ProcessEvent(*window, *event);
#pragma endregion

      if (event->is<sf::Event::Closed>()) {
        window->close();
      } else if (const auto *keyPressed =
                     event->getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
          window->close();
        }
      }
    }
    sf::Time deltaTime = clock.restart();
    float deltaTimeSeconds = deltaTime.asSeconds();

    // make sure delta time stays within normal bounds, like between one FPS and
    // zero FPS
    deltaTimeSeconds = std::min(deltaTimeSeconds, 1.f);
    deltaTimeSeconds = std::max(deltaTimeSeconds, 0.f);

#pragma region imgui
    ImGui::SFML::Update(*window, deltaTime);

    ImGui::PushStyleColor(ImGuiCol_WindowBg, {});
    ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, {});
    ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());
    ImGui::PopStyleColor(2);
#pragma endregion

    ImGui::Begin("Game");
    ImGui::Button("Button");
    ImGui::Text("Hello SFML");
    ImGui::End();
    window->clear();
#pragma region imgui
    ImGui::SFML::Render(*window);
#pragma endregion
    window->display();
  }
#pragma region imgui
  ImGui::SFML::Shutdown();
#pragma endregion
  delete window;
  return 0;
}
