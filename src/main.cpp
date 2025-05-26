#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800,600), "SFML works!");
    sf::RectangleShape rec(sf::Vector2f(100,200));
    rec.setPosition(200,200);
    rec.setFillColor(sf::Color::Blue);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(rec);
        window.display();
    }

    return 0;
}
