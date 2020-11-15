#include "game.hpp"
#include "cell.hpp"
#include "field.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_mouse.h>
#include <iostream>


SDL_Renderer* Game::renderer;     


Game::Game(std::string title,short width, short height): width(width), 
    height(height), is_run(true), elapsed_time(0), simulated(false) {
    
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::cout << "Failed init SDL lib...";
    }
    window = SDL_CreateWindow(title.c_str(), 
                              SDL_WINDOWPOS_UNDEFINED, 
                              SDL_WINDOWPOS_UNDEFINED, 
                              width, 
                              height, 
                              0);
    if(window == nullptr){
        std::cout << "Failed create SDL_Window...";
    }

    renderer = SDL_CreateRenderer(window, 
                                  -1, 
                                  0);
    if(renderer == nullptr){
        std::cout << "Failed create SDL_Renderer";
    }

    field = new Field(height/CELL_SIZE, width/CELL_SIZE);
}

void Game::close(){
    is_run = false;
}


bool Game::isRun(){
    if(is_run)  return true;
    return false;
}

void Game::clear(){
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
    SDL_RenderClear(renderer);
}


void Game::handleEvents(){
    while(SDL_PollEvent(&event)){
        switch (event.type) {
            case SDL_QUIT:      close();    break;
            case SDL_KEYDOWN:   
                switch(event.key.keysym.sym){
                    case SDLK_SPACE:
                        if(simulated)   simulated = false;
                        else            simulated = true;
                        break;
                    case SDLK_ESCAPE:
                        close();
                        break;
                    case SDLK_DELETE:
                        field->clear();
                        break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                int xMouse, yMouse;
                SDL_GetMouseState(&xMouse, &yMouse);
                if((xMouse >= 0 && xMouse <= width) && (yMouse >= 0 && yMouse <= height)){
                    short row = yMouse / CELL_SIZE;
                    short col = xMouse / CELL_SIZE;
                    if(field->getConditionCell(row, col))
                        field->setConditionCell(row, col, false);
                    else
                        field->setConditionCell(row, col, true);
                }
                break;
        }
    }
}


void Game::update(){
    if(simulated)   field->singleMoveSimulated();
}


void Game::wait(){
    SDL_Delay(1000 / FPS);
}


void Game::render(){
    field->render(renderer);
    SDL_RenderPresent(renderer);
}

SDL_Renderer* Game::getRenderer(){
    return renderer;
}
