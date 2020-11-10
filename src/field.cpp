#include "field.hpp"
#include "cell.hpp"

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
