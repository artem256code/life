#include "cell.hpp"

Cell::Cell(short x, short y, bool isLife): x(x), y(y), alife(isLife) {}

short Cell::getX()   {return x;}
short Cell::getY()   {return y;}

bool Cell::isAlife(){
    if(alife)   return true;
    return false;
}

void Cell::kill(){
    alife = false;
}

void Cell::create(){
    alife = true;
}
