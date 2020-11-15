#ifndef MOUSE_HPP
#define MOUSE_HPP


class Mouse
{
private:
    static int x, y;
    static bool isPress;
public:
    /**
     * @brief   Return the 'X' coordinate for the mouse
     * @return  the 'X' coordinate
     */
    static int getX();


    /**
     * @brief   Return the 'Y' coordinate for the mouse
     * @return  the 'Y' coordinate
     */
    static int getY();

    /**
     * @brief   Converting the 'X' coordinate from to a column
     * @return  column
     */
    static short convertCoordXToColumn();


    /**
     * @brief   Converting the 'Y' coordinate from to a row
     * @return  row
     */
    static short convertCoordYToRow();


    /**
     * @brief   Return 'true' if mouse is pressed, else -> return 'fasle'
     * @return  Mouse state (pressed -> 'true'; not pressed -> 'false')
     */
    static bool isPressed();


    /**
     * @brief Making 'isPress' true
     */
    static void press();


    /**
     * @brief Making 'isPress' false
     */
    static void notPress();
};

#endif // MOUSE_HPP
