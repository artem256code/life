#include "game.hpp"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <iostream>
#include <SDL2/SDL.h>

Game::Game(std::string title,short with, short height){
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::cout << "Failed init SDL lib...";
    }
    window = SDL_CreateWindow(title.c_str(), 
                              SDL_WINDOWPOS_UNDEFINED, 
                              SDL_WINDOWPOS_UNDEFINED, 
                              400, 
                              500, 
                              SDL_WINDOW_OPENGL);
    if(window == nullptr){
        std::cout << "Failed create SDL_Window...";
    }

    renderer = SDL_CreateRenderer(window, 
                                  -1, 
                                  SDL_RENDERER_ACCELERATED);
    if(renderer == nullptr){
        std::cout << "Failed create SDL_Renderer";
    }
}

void Game::render(){
    SDL_RenderPresent(renderer);
}