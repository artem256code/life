#include "game.hpp"
#include "cell.hpp"
#include "field.hpp"
#include "mouse.hpp"
#include "font.hpp"
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
    height(height), is_run(true), elapsed_time(0), simulated(false), hiddenHelp(false) {
    
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::cout << "Failed init SDL lib..." << SDL_GetError() << std::endl;
    }
    if(TTF_Init() != 0){
        std::cout << "Failed init TTF lib..." << SDL_GetError() << std::endl;
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
    Font::setFont("/home/artem/C++/life2/font/JetBrainsMono-Medium.ttf", FONT_SIZE);
}

void Game::close(){
    is_run = false;
}


bool Game::isRun(){
    if(is_run)  return true;
    return false;
}

void Game::clear(){
    SDL_SetRenderDrawColor(renderer, 0x1e, 0x26, 0x2b, 0xff);
    SDL_RenderClear(renderer);
}


void Game::setCellInMouseCoords()
{
    short row = Mouse::convertCoordYToRow();
    short col = Mouse::convertCoordXToColumn();
    if(event.button.button == SDL_BUTTON_LEFT){
        field->setConditionCell(row, col, true);
    }
    else{
        field->setConditionCell(row, col, false);
    }
}

void Game::handleEvents(){
    while(SDL_PollEvent(&event)){
        switch (event.type) {
            case SDL_QUIT:      close();    break;
            case SDL_KEYDOWN:   
                switch(event.key.keysym.sym){
                    case SDLK_SPACE:
                        hideHelp();
                        if(simulated)   simulated = false;
                        else            simulated = true;
                        break;
                    case SDLK_ESCAPE:
                        close();
                        break;
                    case SDLK_DELETE:
                        hideHelp();
                        field->clear();
                        break;
                    case SDLK_h:
                        showHelp();
                        break;
                }
                break;
            case SDL_MOUSEMOTION:
                if(Mouse::isPressed()){
                    hideHelp();
                    setCellInMouseCoords();
                    break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                hideHelp();
                setCellInMouseCoords();
                Mouse::press();
                break;
            case SDL_MOUSEBUTTONUP:
                hideHelp();
                setCellInMouseCoords();
                Mouse::notPress();
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


void Game::showHelp(){
    if(hiddenHelp)  hiddenHelp = false;
    else            hiddenHelp = true;
}


void Game::hideHelp(){
    hiddenHelp = true;
}

void Game::viewHelp(){
    Font::render(50, 50 + FONT_SIZE*0, "Hi! It's a simple 'life' simulator!",         0x7c, 0x07, 0xa9, 0xff );
    Font::render(50, 50 + FONT_SIZE*2, "GAME CONTROL:",                               0x7c, 0x07, 0xa9, 0xff );
    Font::render(50, 50 + FONT_SIZE*4, "ESC         -- exit:",                        0x7c, 0x07, 0xa9, 0xff );
    Font::render(50, 50 + FONT_SIZE*5, "H           -- viev/hide this help-manual",   0x7c, 0x07, 0xa9, 0xff );
    Font::render(50, 50 + FONT_SIZE*6, "SPACE       -- run/stop simulation",          0x7c, 0x07, 0xa9, 0xff );
    Font::render(50, 50 + FONT_SIZE*7, "DEL         -- to clear the field",           0x7c, 0x07, 0xa9, 0xff );
    Font::render(50, 50 + FONT_SIZE*8, "MOUSE LEFT  -- add a cell",                   0x7c, 0x07, 0xa9, 0xff );
    Font::render(50, 50 + FONT_SIZE*9, "MOUSE Right -- delete a cell",                0x7c, 0x07, 0xa9, 0xff );
}


void Game::render(){
    field->render(renderer);
    if(!hiddenHelp) viewHelp();
    SDL_RenderPresent(renderer);
}

SDL_Renderer* Game::getRenderer(){
    return renderer;
}
