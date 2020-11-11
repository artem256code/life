#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include "cell.hpp"
#include "field.hpp"


Field::Field(short rows, short columns): rows(rows), columns(columns) {
    cells = new Cell**[rows];
    for(short row = 0; row < rows; row++){
        cells[row] = new Cell*[columns];
        short y = row * CELL_SIZE;
        for(int col = 0; col < columns; col++){
            short x = col * CELL_SIZE;
            cells[row][col] = new Cell(x, y, false);
        }
    }
}


short Field::getNeighborsForCell(short row, short column){
    short neighbors = 0;        //Number of neighboring cells
    // Left
    if(column == 0)
        for(int i = 0; i < 3; i++)  neighbors += cells[rows-1+i][columns-1]->isAlife();
    else
        for(int i = 0; i < 3; i++)  neighbors += cells[rows-1+i][columns-1]->isAlife();

    // Right
    if(column == columns-1)
        for(int i = 0; i < 3; i++)  neighbors += cells[rows-1+i][0]->isAlife();
    else
        for(int i = 0; i < 3; i++)  neighbors += cells[rows-1+i][columns+1]->isAlife();
    
    // Up
    if(row == 0)
        for(int i = 0; i < 3; i++)  neighbors += cells[rows-1][column-1+i]->isAlife();
    else
        for(int i = 0; i < 3; i++)  neighbors += cells[row-1][column-1+i]->isAlife();

    // Down
    if(row == rows-1)
        for(int i = 0; i < 3; i++)  neighbors += cells[0][column-1+i]->isAlife();
    else
        for(int i = 0; i < 3; i++)  neighbors += cells[row+1][column-1+i]->isAlife();
    
    return neighbors;
}


bool Field::checkCellForLife(short row, short column){
    short neighbors = getNeighborsForCell(row, column);
    if(neighbors == 3)  return true;
    if(neighbors == 2 && cells[row][column]->isAlife())    return true;
    return false;
}


void Field::render(SDL_Renderer *renderer){
    for(short row = 0; row < rows; row++){
        for(short col = 0; col < columns; col++){
            if(cells[row][col]->isAlife()){
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