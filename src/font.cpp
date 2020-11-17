#include <SDL2/SDL_render.h>

#include "game.hpp"
#include "font.hpp"

TTF_Font* Font::font = nullptr;

void Font::setFont(std::string pathToFontFile, short fontSize){
    font = TTF_OpenFont(pathToFontFile.c_str(), fontSize);
    if(font == nullptr){
        std::cout << "Opening font fail..." << SDL_GetError() << std::endl;
    }
}

void Font::render(short x, short y, std::string text, Uint8 r, Uint8 g, Uint8 b, Uint8 a){
    SDL_Color fontColor = {r, g, b, a};
    SDL_Surface *fontSurface = TTF_RenderText_Blended(font, text.c_str(), fontColor);
    if(fontSurface == nullptr){
        std::cout << "Surface creating of font fail..." << std::endl;
    }
    SDL_Texture *fontTexture = SDL_CreateTextureFromSurface(Game::getRenderer(),
                                                            fontSurface);
    if(fontTexture == nullptr){
        std::cout << "Texture creating of font fail..." << std::endl;
    }
    int fontW, fontH;
    SDL_QueryTexture(fontTexture, NULL, NULL, &fontW, &fontH);

    SDL_Rect fontRect = {x, y, fontW, fontH};

    SDL_RenderCopy(Game::getRenderer(), fontTexture, nullptr, &fontRect);
}
