#ifndef FIELD_HPP
#define FIELD_HPP

#include "cell.hpp"
#include <SDL2/SDL_render.h>
#include <string>

/**
 * @brief The gaming Field which consists of Cell
 * 
 */
class Field{
private:
    short rows, columns;
    Cell ***cells;              // Matrix of cells
    Cell ***cellsAdd;           // Cells after adding
    Cell ***cellsDel;           // Cells after deleting
private:
    /**
     * @brief  Creating the matrix of cells with sizes: rows*column
     * @param  rows      - numbers of row in matrix
     * @param  columns   - numbers of column in matrix
     * @return the pointer to the created matrix
     */
    Cell*** createCells(short rows, short columns);


    /**
     * @brief Copy the matrix of cells from 'cells' in 'to'
     * @param cells - matrix of cells
     * @param to    - matrix of cells
     */
    void copyCellsTo(Cell ***cells, Cell ***to);


    /**
     * @brief Check nearest 8 cells and return value 
     * 
     * @param cells  - matrix in which calculations are performed
     * @param row    - row of this cell
     * @param column - column of this cell
     * @return true  - if cell will continue to live
     * @return false - if cell must dead 
     */
    bool checkCellForLife(Cell ***cells, short row, short column);

    /**
     * @brief Get the Neighboars For Cell object
     *
     * @param cells     - matrix in which calculations are performed
     * @param row       -  row of this cell
     * @param column    -  column of this cell
     * @return short    -  numbers of the neighbors
     */
    short getNeighborsForCell(Cell ***cells, short row, short column);
public:
    /**
     * @brief Construct a new Field object
     * 
     * @param rows      - numbers of rows in the Field 
     * @param columns   - numbers of columns in the Field
     */
    Field(short rows, short columns);
    

    /**
     * @brief Simulating a single move for all cells.
     *        Processing who should die and who should live
     */
    void singleMoveSimulated();

    /**
     * @brief Rendering Field 
     * 
     */
    void render(SDL_Renderer *renderer);
};

#endif
