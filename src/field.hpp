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
    Cell ***cells;              // Two-dimensional array describing Field
private:
    /**
     * @brief Check nearest 8 cells and return value 
     * 
     * @return true  - if cell will continue to live
     * @return false - if cell must dead
     */
    bool checkCellForLife();
public:
    /**
     * @brief Construct a new Field object
     * 
     * @param rows      - numbers of rows in the Field 
     * @param columns   - numbers of columns in the Field
     */
    Field(short rows, short columns);
    
    
    /**
     * @brief Rendering Field 
     * 
     */
    void render(SDL_Renderer *renderer);
};

#endif