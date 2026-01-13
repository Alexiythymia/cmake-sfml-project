#pragma once
#include <SFML/Graphics.hpp>
/*
    Class/concept for the animated component of a thing that moves on the screen. Has all the logic for figuring out 
    the next sprite frame, timing the animation, etc.
*/

enum Direction
{
    NONE, DOWN, UP, LEFT, RIGHT
};

class Animated_Sprite
{
private:
    //sprite/texture stuff
    sf::Sprite *sprite;
    sf::Texture *texture;
    sf::String spritesheet_filename;
    sf::IntRect spritesheet_frame;
    sf::Vector2f sprite_screen_postion;

    //animation specific stuff
    sf::Clock animation_timer; //keeps track of the time length of the current animation frame
    uint32_t animation_frame_count; //number of different frames in the animation
    uint32_t current_animation_frame;//which frame we're currently on
    sf::Time animation_frame_time_millis; //uniform length that each frame is displayed
    Direction current_direction; //which direction we're currently facing
    


public:

    float sprite_velocity; //how fast the sprite translates on the screen
    Animated_Sprite() = delete; //have to specify some of the things: spritesheet, frame count, times
    Animated_Sprite(const sf::String& spritesheet_filename, uint32_t frame_count, sf::Time& frame_time);
    ~Animated_Sprite();

    inline sf::Sprite* get_sprite() const {return sprite;}
    inline sf::Texture* get_texture() const {return texture;}
    inline sf::String get_spritesheet_name() const {return spritesheet_filename;}
    inline sf::Clock& get_animation_timer() {return animation_timer;} // never return a copy?
    inline uint32_t get_animation_frame_count() const {return animation_frame_count;}
    inline uint32_t get_current_animation_frame() const {return current_animation_frame;}
    inline sf::Time get_animation_time_millis() const {return animation_frame_time_millis;}
    inline sf::IntRect get_spriteframeBounds() const {return spritesheet_frame;}
    inline sf::Vector2f get_sprite_screen_position() const { return sprite_screen_postion;}

    //inline void set_sprite(sf::Sprite new_sprite) 
    inline void set_sprite_frame(sf::IntRect rect) {sprite->setTextureRect(rect);}
    inline void set_sprite_scale(const sf::Vector2f& new_scale) {sprite->setScale(new_scale);}
    //inline void set_texture(sf::Texture new_texture) {texture = new_texture;}
    inline void stop_animation_timer() {animation_timer.stop();}
    inline void start_animation_timer() {animation_timer.start();}
    inline void reset_animation_timer() {animation_timer.reset();} //clock ends stopped
    inline void restart_animation_timer() {animation_timer.restart();} //clock ends running
    inline void set_current_frame(uint32_t new_frame) {current_animation_frame = new_frame;}
    inline void set_animation_time_millis(const sf::Time& new_time_millis) {animation_frame_time_millis = new_time_millis;}
    inline void set_spritesheet_frame_bounds(const sf::IntRect& new_bounds)
    {
        sprite->setTextureRect(new_bounds);
    }
    inline void set_sprite_screen_position(const sf::Vector2f& new_position)
    {
        sprite->setPosition(new_position);
    }
    inline bool check_animation_timer() const{ return animation_timer.getElapsedTime() > animation_frame_time_millis;}
    void start_moving();
    void stop_moving();

    inline void increment_animation_frame() 
    {
        current_animation_frame = ++current_animation_frame % animation_frame_count;
        restart_animation_timer();
    }
    //this is the thing that causes everything else to change
    void tick();
    void move_sprite();// now this doesn't care about direction
    void change_direction(const Direction& new_direction);

    bool is_animated;

};