#ifndef FIELD_HPP
#define FIELD_HPP

#include "cell.hpp"

/**
 * @brief The gaming Field which consists of Cell
 * 
 */
class Field{
private:
    Cell **cells;       // Two-dimensional array describing Field
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
     * @param _rows      - numbers of rows in the Field 
     * @param _columns   - numbers of columns in the Field
     */
    Field(short _rows, short _columns);
    
    
    /**
     * @brief Rendering Field 
     * 
     */
    void render();
};

#endif