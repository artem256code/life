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
    Cell **cells;              // A one dimensional array representing a matrix of cells
private:

    /**
     * @brief Check nearest 8 cells and return value 
     * 
     * @param row    -  row of this cell
     * @param column -  column of this cell
     * @return true  - if cell will continue to live
     * @return false - if cell must dead 
     */
    bool checkCellForLife(short row, short column);

    /**
     * @brief Get the Neighboars For Cell object
     * 
     * @param row       -  row of this cell
     * @param column    -  column of this cell
     * @return short    -  numbers of the neighbors
     */
    short getNeighborsForCell(short row, short column);
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