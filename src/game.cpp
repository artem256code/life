#include "game.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <iostream>


Game::Game(std::string title,short width, short height): width(width), 
    height(height), is_run(true), elapsed_time(0) {
    
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


bool Game::isRun(){
    if(is_run)  return true;
    return false;
}

void Game::clear(){
    SDL_RenderClear(renderer);
}


void Game::update(){
    //Some code...
}


void Game::wait(){
    SDL_Delay(1000 / FPS);
}


void Game::render(){
    SDL_RenderPresent(renderer);
}