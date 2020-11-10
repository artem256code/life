#ifndef CELL_HPP
#define CELL_HPP

#define CELL_SIZE 30

/**
 * @brief The class describing one cell in the field 
 */
class Cell{
private:
    short x, y;         // Coords in SDL axes
    bool alife;         // Cell is alife? (true/false)
public:
    /**
     * @brief Construct a new Cell object
     * 
     * @param x        - coords 'x' for the new Cell
     * @param y        - coords 'y' for the new Cell
     * @param isLife   - the state of a cell (alive/dead)
     */
    Cell(short x, short y, bool isLife);


    // Simple getters
    short getX();
    short getY();
    

    /**
     * @brief returns the state of the cell
     * 
     * @return true  - if the cell is alife 
     * @return false - if the cell is dead
     */
    bool isAlife();


    /**
     * @brief Kill the cell if she is alive
     * 
     */
    void kill();


    /**
     * @brief Create cell if she is dead
     * 
     */
    void create();

};


#endif