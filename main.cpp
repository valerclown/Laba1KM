#include "imgui.h"
#include "imgui-SFML.h"
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Risovalka");
    ImGui::SFML::Init(window);

    std::vector<sf::CircleShape> circles;
    ImVec4 currentColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f); // Изначально установим белый цвет
    bool isMousePressed = false;
    bool drawing = true; // Переменная для отслеживания режима рисования

    sf::Clock deltaClock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                isMousePressed = true;
            else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
                isMousePressed = false;

            if (isMousePressed && drawing)
            {
                sf::CircleShape newCircle;
                newCircle.setRadius(30.0f);
                newCircle.setFillColor(sf::Color(
                    static_cast<sf::Uint8>(currentColor.x * 255),
                    static_cast<sf::Uint8>(currentColor.y * 255),
                    static_cast<sf::Uint8>(currentColor.z * 255)
                ));
                newCircle.setOutlineThickness(0.0f);
                newCircle.setOrigin(30.0f, 30.0f);
                newCircle.setPosition(static_cast<float>(sf::Mouse::getPosition(window).x), static_cast<float>(sf::Mouse::getPosition(window).y));
                circles.push_back(newCircle);
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("Painter");
        if (ImGui::Button("Clear Canvas"))
        {
            circles.clear();
        }

        // Интерфейс для выбора цвета
        if (ImGui::ColorEdit3("Brush Color", (float*)&currentColor))
        {
            // Переключение режима рисования при изменении цвета
            drawing = true;
        }

        // Переключатель режима рисования
        ImGui::Checkbox("Drawing Mode", &drawing);

        ImGui::End();

        window.clear(sf::Color(18, 33, 43));

        for (const auto& circle : circles)
        {
            window.draw(circle);
        }

        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}
