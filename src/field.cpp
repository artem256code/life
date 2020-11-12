#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include "cell.hpp"
#include "field.hpp"
#include <SDL2/SDL_timer.h>
#include <iostream>

Field::Field(short rows, short columns): rows(rows), columns(columns) {
    cells = new Cell*[rows*columns];
    short y = 0;
    for(int row = 0; row < rows; row++){
        short x = 0;
        y += CELL_SIZE;
        for(int col = 0; col < columns; col++){
            x += CELL_SIZE;
            cells[row*columns + col] = new Cell(x, y, false);
        }
    }
}


short Field::getIndexCell(short row, short column, short offset, short step){
    short index = row*columns+column;
    for(int i = 0; i < offset; i++){
        index += step;
        if(step < 0 && index > rows*columns)    index = 0;
        else if(step < 0 && index < 0)          index = rows*columns-1;
    }
    return index;
}


short Field::getNeighborsForCell(short row, short column){
    short neighbors = 0;        //Number of neighboring cells
    
    // Upper neighbors
    for(int i = 0; i < 3; i++){
        neighbors += cells[getIndexCell(row, column, columns-i, -1)]->isAlife();
    }
    
    // Average neighbors
    neighbors += cells[getIndexCell(row, column, 1, 1)]->isAlife();
    neighbors += cells[getIndexCell(row, column, 1, -1)]->isAlife();
    
    // Lower neighbors
    for(int i = 0; i < 3; i++){
        neighbors += cells[getIndexCell(row, column, columns-i, 1)]->isAlife();
    }

    return neighbors;
}


bool Field::checkCellForLife(short row, short column){
    short neighbors = getNeighborsForCell(row, column);
    if(neighbors == 3)  return true;
    if(neighbors == 2 && cells[row*columns+columns]->isAlife())    return true;
    return false;
}


void Field::render(SDL_Renderer *renderer){
    for(short row = 0; row < rows; row++){
        for(short col = 0; col < columns; col++){
            if(cells[row*columns+col]->isAlife()){
                SDL_Rect renderRect = { col*CELL_SIZE,
                                        row*CELL_SIZE,
                                        CELL_SIZE,
                                        CELL_SIZE};
                SDL_SetRenderDrawColor(renderer, 0x6A, 0xCA, 0x59, 0xff);
                SDL_RenderDrawRect(renderer, &renderRect);
            }
        }
    }
}