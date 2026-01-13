/*
    Input Manager is an abstraction on top of SFML's input events:
    keyPressed/Released,click events, joystick crap. This tracks
    things like if a button is already down (key held for things like
    continuing animations) and this is probably how we're gonna do
    controller/joystick support.

    I think once we get that far, a Game_Context is gonna have an input 
    manager, so when an event gets received, it gets routed to the current
    context and that routes it to an input manager that has one mapping for
    that event.
*/
/*
    So Input_Manager is just going to keep a collection of all the keys/buttons
    and their current state: up or down for buttons, for instance. If there is a 
    new key pressed event and the key is already down, then it's held.
*/

#include <map>
#include <iostream>

#include<SFML/Window.hpp>
//"pressed" means key just went down. "Released" is key just went up.
//"Held" means it was down and it continues to be down, "up" means wasn't and isn't
enum KeyState
{
    KEY_PRESSED, KEY_RELEASED, KEY_HELD
};

//we need to take the key that the event is raising, and use that to check the state
class Input_Manager
{
private:
    std::map<sf::Keyboard::Key, enum KeyState> KeyStates;
public:
    inline KeyState get_key_state(sf::Keyboard::Key new_key)
    {
        try
        {
        return KeyStates.at(new_key);
        }    
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }
    
    inline void press_key(sf::Keyboard::Key press_key)
    {
        auto key = KeyStates.at(press_key);
        if (key == KeyState::KEY_RELEASED) 
        {
            KeyStates.at(press_key) = KEY_PRESSED;
        }
        else
        {
            KeyStates.at(press_key) = KEY_HELD;
        }
        
    }

    /*
    inline void hold_key(sf::Keyboard::Key hold_key)
    {
        KeyStates.at(hold_key) = KEY_HELD;
    }
*/
    inline void release_key(sf::Keyboard::Key release_key)
    {
        KeyStates.at(release_key) = KEY_RELEASED;      
    }
    //default-construction has every key up
    Input_Manager()
    {
        KeyStates.emplace(sf::Keyboard::Key::W,KEY_RELEASED);
    }
};

