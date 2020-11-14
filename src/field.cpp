#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include "cell.hpp"
#include "field.hpp"
#include <SDL2/SDL_timer.h>
#include <iostream>

Cell*** Field::createCells(short rows, short columns){
    Cell ***newCells = new Cell**[rows];
    short y = 0;
    for(int row = 0; row < rows; row++){
        short x = 0;
        newCells[row] = new Cell*[columns];
        for(int col = 0; col < columns; col++){
            newCells[row][col] = new Cell(x, y, false);
            x += CELL_SIZE;
        }
        y += CELL_SIZE;
    }
    return newCells;
}

Field::Field(short rows, short columns): rows(rows), columns(columns) {
    cells    = createCells(rows, columns);
    cellsAdd = createCells(rows, columns);
    cellsDel = createCells(rows, columns);
}


void Field::copyCellsTo(Cell ***cells, Cell ***to){
    for(short row = 0; row < rows; row++){
        for(short col = 0; col < columns; col++){
            if(cells[row][col]->isAlife())  to[row][col]->create();
            else                            to[row][col]->kill();
        }
    }
}


short Field::getNeighborsForCell(Cell ***cells, short row, short col){
    short neighbors = 0;        //Number of neighboring cells

        for(int dRow = -1; dRow <= 1; dRow++){
            for(int dCol = -1; dCol <= 1; dCol++){
                short y = row;
                short x = col;

                if(row + dRow < 0)               y = rows+dRow;
                else if(row + dRow >= rows)      y = dRow - 1;
                else                             y += dRow;
                if(col + dCol < 0)               x = columns+dCol;
                else if(col + dCol >= columns)   x = dCol - 1;
                else                             x += dCol;

                if(y == row && x == col)  continue;

                neighbors += cells[y][x]->isAlife();
            }
        }

        return neighbors;
}


bool Field::checkCellForLife(Cell ***cells,short row, short col){
    short neighbors = getNeighborsForCell(cells, row, col);
    if(neighbors == 3 && !cells[row][col]->isAlife())  return true;
    if((neighbors == 2 || neighbors == 3) && cells[row][col]->isAlife())    return true;
    return false;
}


void Field::singleMoveSimulated(){
    // First kill, then add
    for(short row = 0; row < rows; row++){
        for(short col = 0; col < columns; col++){
            if(!checkCellForLife(cellsDel, row, col))   cells[row][col]->kill();
            if(checkCellForLife(cellsAdd, row, col))    cells[row][col]->create();
        }
    }

    copyCellsTo(cells, cellsAdd);
    copyCellsTo(cells, cellsDel);
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
