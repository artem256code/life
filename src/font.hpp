#ifndef FONT_HPP
#define FONT_HPP

#include <SDL2/SDL_ttf.h>
#include <iostream>

#define FONT_SIZE   20

class Font
{
    static TTF_Font *font;     //The font for the displaying text
public:
    /**
     * @brief Setting the font and font size
     * @param pathToFontFile - path to the font file (format: .ttf !!!)
     * @param fontSize       - font size
     */
    static void setFont(std::string pathToFontFile, short fontSize);


    /**
     * @brief Displaying text in the game
     * @param x         -  text 'X' coord
     * @param y         -  text 'Y' coord
     * @param text      -  text to displaying
     * @param r         -  Red color
     * @param g         -  Green color
     * @param b         -  Blue color
     * @param a         -  Font opacity
     */
    static void render(short x, short y, std::string text, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
};

#endif // FONT_HPP
