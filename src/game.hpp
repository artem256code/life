#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <string>

#include "field.hpp"

#define FPS   20

/**
 * @brief the main class of the game. 
 * 
 */
class Game{
private:    
    SDL_Window *window;          
    static SDL_Renderer *renderer;      
    SDL_Event event;
    Field *field;               
    Uint32 elapsed_time;        // Elapsed time since the beginning of the game
    short width, height;        // The sizes of the game window 
    bool is_run;                // Is the game running? (true/false)
    bool simulated;             // Is the simulated running? (true/fasle)
    bool hiddenHelp;            // Help is hidden? (true/false)
private:
    /**
     * @brief Closing the game
     * 
     */
    void close();

    /**
     * @brief   Rendering the help-manual
     */
    void viewHelp();


    /**
     * @brief   To show the help
     */
    void showHelp();


    /**
     * @brief To hide the help
     */
    void hideHelp();
public:
    /**
     * @brief Construct a new Game object
     * 
     * @param title  - title of the game window
     * @param with   - width of the game window
     * @param height - height of the game window
     */
    Game(std::string title, short width, short height);


    /**
     * @brief Returns the game condition 
     * 
     * @return true  - if the game is running
     * @return false - if the game is stoping 
     */
    bool isRun();

    /**
     * @brief Clearing the full scene
     * 
     */
    void clear();


    /**
     * @brief Processing the all events in the game and 
     *        running the nessesary functions  
     */
    void handleEvents();


    /**
     * @brief Processing the all logics with cells
     *        
     */
    void update();


    /**
     * @brief Sleeping the some time = 1000 ms / FPS
     * 
     */
    void wait();


    /**
     * @brief Rendering full scene. 
     *        Gets all the information using the "Field"
     */
    void render();


    /**
     * @brief Get the Renderer object
     * 
     * @return SDL_Renderer* - object Rendrer
     */
    static SDL_Renderer* getRenderer();


    /**
     * @brief Sets the state of the cell depending on the mouse coordinate.
     */
    void setCellInMouseCoords();
};

#endif
