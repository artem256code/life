#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_events.h>
#include "mouse.hpp"
#include "cell.hpp"

int Mouse::x = -1;
int Mouse::y = -1;
bool Mouse::isPress = false;

int Mouse::getX() {
    SDL_GetMouseState(&x, &y);
    return x;
}


int Mouse::getY() {
    SDL_GetMouseState(&x, &y);
    return y;
}


short Mouse::convertCoordYToRow(){
    return getY() / CELL_SIZE;
}


short Mouse::convertCoordXToColumn(){
    return getX() / CELL_SIZE;
}


void Mouse::notPress(){
    isPress = false;
}


void Mouse::press(){
    isPress = true;
}


bool Mouse::isPressed(){
    if(isPress)     return true;
    return false;
}
