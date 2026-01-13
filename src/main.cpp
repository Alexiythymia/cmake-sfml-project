//#include <SFML/Graphics.hpp>
#include <iostream>
#include "Animated_Sprite.hpp"
#include "Input_Manager.hpp"



// This is the main function where the program execution begins.
int main() {
    // Create a new window of size 800x600 pixels with the title "SFML Sprite Sheet".
    // sf::Style::Close allows the user to close the window with the 'X' button.
    unsigned int screen_height{600},screen_width{800};
    sf::RenderWindow window(sf::VideoMode({800,600}), "SFML Sprite Sheet", sf::Style::Close);
    window.setPosition({2400,200});
    window.setFramerateLimit(60); // Limit the frame rate to 60 FPS for smooth rendering.
    Input_Manager keyboard_input;

    const sf::String filename{"spritesheet.png"};
    sf::Time time = sf::milliseconds(125);
    sf::Time master_game_frame_time = sf::milliseconds(16); //60 fps game?
    sf::Clock master_game_clock = sf::Clock(); 
    Animated_Sprite a_sprite(filename,4,time);
/*
    // Create a texture to hold the sprite sheet image.
    sf::Texture texture;
    // Attempt to load the sprite sheet. Make sure the file exists in the same directory as the executable.
    // Replace "spritesheet.png" with the path to your own sprite sheet image.
    if (!texture.loadFromFile("spritesheet.png")) {
        // If the file can't be loaded, print an error message to the console and exit.
        std::cerr << "Error: Could not load spritesheet.png" << std::endl;
        return 1;
    }

    // Create a sprite object from the loaded texture.
    sf::Sprite sprite(texture);
    // This is a rectangle that defines the part of the texture to be displayed.
    // It's used to select a single frame from the sprite sheet.
    // The arguments are (left, top, width, height).
    // The values below assume a spritesheet where each frame is 32x32 pixels.
    // You will need to adjust these values to match your own spritesheet.
*/
    sf::Vector2 initial_postion{0,0}, initial_height_width{64,64};
  
    sf::IntRect spriteFrame(initial_postion,initial_height_width);

    // Set the initial texture rectangle for the sprite.
    a_sprite.get_sprite()->setTextureRect(spriteFrame);
    a_sprite.get_sprite()->setScale(sf::Vector2f{2,2});

    // Set the position of the sprite in the window.
    // This example centers the sprite.
    sf::Vector2u textureSize = a_sprite.get_texture()->getSize();
    float texture_width_f{static_cast<float>(initial_height_width.x)}, texture_height_f{static_cast<float>(initial_height_width.y)};
    float screen_width_f{800.0f}, screen_height_f{600.0f};
    sf::Vector2f sprite_midpoint{texture_width_f / 2,texture_height_f / 2};
    sf::Vector2f screen_midpoint{screen_width_f / 2, screen_height_f / 2}; 
    a_sprite.get_sprite()->setOrigin(sprite_midpoint);
    a_sprite.get_sprite()->setPosition(screen_midpoint);

    while (window.isOpen() && master_game_clock.getElapsedTime() < master_game_frame_time) 
    {
        // Process all events that have occurred since the last frame.
        while (std::optional event = window.pollEvent()) 
        {
            // Check if the event is a window close request.
            if (event->is<sf::Event::Closed>()) 
            {
                window.close();
            }
            //temp fix for bug where mouse movement accelerates the game: ignore mouse moved event via empty if body
            if (event->is<sf::Event::MouseMoved>()) continue;

            // --- Handle Keyboard Input ---
            // We use sf::Keyboard::isKeyPressed() to check for key presses continuously.
            // This is suitable for player movement.
            
            // 'W' key pressed: Move up or change to the 'up' sprite frame.
            // In this example, we change the y-coordinate of the sprite frame.
            // Adjust the top value (e.g., 96) to point to the row for the 'up' animation in your spritesheet.
            
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyReleased>())
            {
            //need input manager here to make sure it's the W key that got released, not just any key
            //test case: walk any direction, press and release an unrelated key. Movement stops.
            a_sprite.stop_moving();
            a_sprite.change_direction(Direction::NONE);
            }
            
            //else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            //{
            
            
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) 
            {
                if (!(a_sprite.is_animated)) a_sprite.start_moving();
                a_sprite.change_direction(Direction::UP);
            }
            //here's where we need the held key case, because we shouldn't be starting to move, we 
            //should be continuing to move

            // 'A' key pressed: Move left or change to the 'left' sprite frame.
            // Adjust the top value (e.g., 32) to point to the row for the 'left' animation.
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) 
            {
                if (!(a_sprite.is_animated)) a_sprite.start_moving();
                a_sprite.change_direction(Direction::LEFT);
            }

            // 'S' key pressed: Move down or change to the 'down' sprite frame.
            // Adjust the top value (e.g., 0) to point to the row for the 'down' animation.
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) 
            {
                if (!(a_sprite.is_animated)) a_sprite.start_moving();
                a_sprite.change_direction(Direction::DOWN);
            }

            // 'D' key pressed: Move right or change to the 'right' sprite frame.
            // Adjust the top value (e.g., 64) to point to the row for the 'right' animation.
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) 
            {
                if (!(a_sprite.is_animated)) a_sprite.start_moving();
                a_sprite.change_direction(Direction::RIGHT);
            }
        }
        a_sprite.move_sprite();
        a_sprite.tick();

        // --- Rendering ---
        // Clear the window with a black color.
        window.clear(sf::Color::Black);
        // Draw the sprite on the window.
        window.draw( *(a_sprite.get_sprite()) );
        // Display the contents of the window.
        window.display();
        master_game_clock.restart();
    }

    // The program exits here when the window is closed.
    return 0;
}

