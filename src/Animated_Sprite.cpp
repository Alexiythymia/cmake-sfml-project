#include <iostream>
#include "Animated_Sprite.hpp"

Animated_Sprite::Animated_Sprite(const sf::String& spritesheet_filename, uint32_t frame_count, sf::Time& frame_time)
{
    sprite_velocity = 1.0f; //TODO: move into constructor args later
    this->spritesheet_filename = spritesheet_filename;
    texture = new sf::Texture(static_cast<std::string>(spritesheet_filename));
    if (!texture) 
    {
        std::cerr << "Failed to load texture from " << std::string(spritesheet_filename) << std::endl;
        exit(1);
    }

    sprite = new sf::Sprite(*texture);
    if (!sprite) 
    {
        std::cerr << "Failed to create sprite from texture using spritesheet " 
        << std::string(spritesheet_filename) << std::endl;
        exit(2);
    }
    animation_frame_count = frame_count;
    animation_frame_time_millis = frame_time;
    animation_timer = sf::Clock();
    current_animation_frame = 0;
    current_direction = Direction::NONE;
    is_animated = false;
}

void Animated_Sprite::start_moving()
{

    is_animated = true;
    animation_timer.restart();

}

void Animated_Sprite::stop_moving()
{
    if (is_animated)
    {
        is_animated = false;
        //change_direction(Direction::NONE);
        animation_timer.reset();
        current_animation_frame = 0;
        /*
        auto old_bounds = get_spriteframeBounds();
        std::cerr << "old_bounds: " << old_bounds.position.x << "," << old_bounds.position.y << " " << old_bounds.size.x << "," <<old_bounds.size.y << std::endl; 
        set_spritesheet_frame_bounds(old_bounds);
        */
       //WORKING HERE, REMOVE THE HARDCODE. WHERE ARE THESE VALUES SET NORMALLY?
        int32_t position_x = current_direction == Direction::DOWN ? 0 : current_direction == Direction::UP ? 64: current_direction == Direction::LEFT ? 192 : current_direction == Direction::RIGHT? 128 : 128, position_y= 64 * get_current_animation_frame(), size_x = 64, size_y = 64;
        //sf::IntRect new_frame{a_sprite.get_spriteframeBounds()};
        sf::Vector2i pos{position_x,position_y}, size{size_x,size_y};
        sf::IntRect new_frame_bounds{pos,size};
        set_spritesheet_frame_bounds(new_frame_bounds);
    }
}
void Animated_Sprite::tick()
{
    if (is_animated)
    {
        if (check_animation_timer())
        {
            increment_animation_frame();
        }
    }
    else
    {
        stop_moving();
    }
    
    
}
//change which column of the spritesheet is being displayed
void Animated_Sprite::change_direction(const Direction& new_direction)
{
    current_direction = new_direction;
}
// change the sprite to the appropriate one given the direction we're moving in, and translate the sprite
void Animated_Sprite::move_sprite()
{
    switch(current_direction)
    {
        case Direction::DOWN:
        {
            current_direction = Direction::DOWN;
            sprite->setPosition(sprite->getPosition() + sf::Vector2{0.0f,sprite_velocity});
            //change the sprite texture rec to be the correct one
            int32_t position_x = 0, position_y = 64 * get_current_animation_frame(), size_x = 64, size_y = 64;
            //sf::IntRect new_frame{a_sprite.get_spriteframeBounds()};
            sf::Vector2i pos{position_x,position_y}, size{size_x,size_y};
            sf::IntRect new_frame_bounds{pos,size};
            set_spritesheet_frame_bounds(new_frame_bounds);
            break;
        }
        case Direction::UP:
        {
            current_direction = Direction::UP;
            sprite->setPosition(sprite->getPosition() + sf::Vector2{0.0f,-sprite_velocity});
            //change the sprite texture rec to be the correct one
            int32_t position_x = 64, position_y = 64 * get_current_animation_frame(), size_x = 64, size_y = 64;
            //sf::IntRect new_frame{a_sprite.get_spriteframeBounds()};
            sf::Vector2i pos{position_x,position_y}, size{size_x,size_y};
            sf::IntRect new_frame_bounds{pos,size};
            set_spritesheet_frame_bounds(new_frame_bounds);
            break;
        }
        case Direction::LEFT:
        {
            current_direction = Direction::LEFT;
            sprite->setPosition(sprite->getPosition() + sf::Vector2{-sprite_velocity,0.0f});
            //change the sprite texture rec to be the correct one
            int32_t position_x = 192, position_y = 64 * get_current_animation_frame(), size_x = 64, size_y = 64;
            //sf::IntRect new_frame{a_sprite.get_spriteframeBounds()};
            sf::Vector2i pos{position_x,position_y}, size{size_x,size_y};
            sf::IntRect new_frame_bounds{pos,size};
            set_spritesheet_frame_bounds(new_frame_bounds);
            break;
        }
        case Direction::RIGHT:
        {
            current_direction = Direction::RIGHT;
            sprite->setPosition(sprite->getPosition() + sf::Vector2{sprite_velocity,0.0f});
            //change the sprite texture rec to be the correct one
            int32_t position_x = 128, position_y = 64 * get_current_animation_frame(), size_x = 64, size_y = 64;
            //sf::IntRect new_frame{a_sprite.get_spriteframeBounds()};
            sf::Vector2i pos{position_x,position_y}, size{size_x,size_y};
            sf::IntRect new_frame_bounds{pos,size};
            set_spritesheet_frame_bounds(new_frame_bounds);
            break;
        }
        case Direction::NONE: break;
    }
}

Animated_Sprite::~Animated_Sprite()
{
    if (sprite) delete sprite;
    if (texture) delete texture;
}