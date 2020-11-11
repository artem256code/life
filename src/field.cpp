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


void Field::render(SDL_Renderer *renderer){
    for(short row = 0; row < rows; row++){
        for(short col = 0; col < columns; col++){
            if(cells[row][col]){
                SDL_Rect renderRect = { col*CELL_SIZE,
                                        row*CELL_SIZE,
                                        CELL_SIZE,
                                        CELL_SIZE};
                SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
                SDL_RenderDrawRect(renderer, &renderRect);
            }
        }
    }
}