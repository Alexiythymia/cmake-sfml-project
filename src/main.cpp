#include <SFML/Graphics.hpp>
#include "iostream"
#include <filesystem>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800,600), "SFML works!");
    sf::RectangleShape rec(sf::Vector2f(100,200));
    rec.setPosition(200,200);
    rec.setFillColor(sf::Color::Blue);
    sf::Font font;
    try
    {
        font.loadFromFile("../../src/fonts/Inktype-MAp2J.ttf"); 
    }
    catch(const std::exception& e)
    {
        std::cerr << "failure to load font from file" << '\n';
    }
    
    sf::Text text(std::string("K Pressed"),font);
    text.setPosition(401,200);   
    bool textFlag = false;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    //std::cout << "Escape pressed" << std::endl;
                    window.close();
                }
                if (event.key.code == sf::Keyboard::K) textFlag = !textFlag;
            }
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(rec);
        if (textFlag) window.draw(text);
        window.display();
    }

    return 0;
}
