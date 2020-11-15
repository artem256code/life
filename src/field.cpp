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


bool Field::getConditionCell(short row, short col){
    if (cells[row][col]->isAlife()) return true;
    return false;
}

void Field::setConditionCell(short row, short col, bool isLife){
    if(isLife){
        cells[row][col]->create();
        cellsAdd[row][col]->create();
        cellsDel[row][col]->create();
    }
    else{
        cells[row][col]->kill();
        cellsAdd[row][col]->kill();
        cellsDel[row][col]->kill();
    }
}


Field::Field(short rows, short columns): rows(rows), columns(columns) {
    cells    = createCells(rows, columns);
    cellsAdd = createCells(rows, columns);
    cellsDel = createCells(rows, columns);
}


void Field::clear(){
    for(short row = 0; row < rows; row++){
        for(short col = 0; col < columns; col++){
            cells[row][col]->kill();
        }
    }
    copyCellsTo(cells, cellsAdd);
    copyCellsTo(cells, cellsDel);
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
    // Draw cells
    for(short row = 0; row < rows; row++){
        for(short col = 0; col < columns; col++){
            if(cells[row][col]->isAlife()){
                SDL_Rect borderRect = { col*CELL_SIZE,
                                        row*CELL_SIZE,
                                        CELL_SIZE,
                                        CELL_SIZE};

                SDL_Rect baseRect = { col*CELL_SIZE + CELL_SIZE / 10,
                                      row*CELL_SIZE + CELL_SIZE / 10,
                                      CELL_SIZE - CELL_SIZE / 5,
                                      CELL_SIZE - CELL_SIZE / 5};

                SDL_Rect flareRect = { col*CELL_SIZE + CELL_SIZE / 5,
                                       row*CELL_SIZE + CELL_SIZE / 5,
                                       CELL_SIZE / 4,
                                       CELL_SIZE / 4};

                SDL_Rect smallFlareRect1 = { col*CELL_SIZE + CELL_SIZE / 2 - CELL_SIZE / 10,
                                             row*CELL_SIZE + CELL_SIZE / 5,
                                             CELL_SIZE / 5,
                                             CELL_SIZE / 5};

                SDL_Rect smallFlareRect2 = { col*CELL_SIZE + CELL_SIZE / 5,
                                             row*CELL_SIZE + CELL_SIZE / 2 - CELL_SIZE / 10,
                                             CELL_SIZE / 5,
                                             CELL_SIZE / 5};

                SDL_SetRenderDrawColor(renderer, 0x31, 0x6b, 0x3f, 0xff);
                SDL_RenderFillRect(renderer, &borderRect);
                SDL_SetRenderDrawColor(renderer, 0x57, 0x8e, 0x64, 0xff);
                SDL_RenderFillRect(renderer, &baseRect);
                SDL_SetRenderDrawColor(renderer, 0x70, 0xa2, 0x7c, 0xff);
                SDL_RenderFillRect(renderer, &flareRect);
                SDL_RenderFillRect(renderer, &smallFlareRect1);
                SDL_RenderFillRect(renderer, &smallFlareRect2);
            }
        }
    }
    // Draw lines
    for(short row = 0; row <= rows; row++){
        // Y lines
        SDL_Rect yRect = {0, row*CELL_SIZE, rows*CELL_SIZE, CELL_SIZE/10};
        SDL_SetRenderDrawColor(renderer, 0x15, 0x1a, 0x1e, 0xff);
        SDL_RenderFillRect(renderer, &yRect);
        for(short col = 0; col <= columns; col++){
            // X lines
            SDL_Rect xRect = {col*CELL_SIZE, 0, CELL_SIZE/10, columns*CELL_SIZE};
            SDL_SetRenderDrawColor(renderer, 0x15, 0x1a, 0x1e, 0xff);
            SDL_RenderFillRect(renderer, &xRect);
        }
    }
}
