#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <string>

#include "field.hpp"

/**
 * @brief the main class of the game. 
 * 
 */
class Game{
private:    
    SDL_Window *window;
    SDL_Renderer *renderer;
    Field *field;
public:
    /**
     * @brief Construct a new Game object
     * 
     * @param title  - title of the game window
     * @param with   - width of the game window
     * @param height - height of the game window
     */
    Game(std::string title,short with, short height);

};

#endif