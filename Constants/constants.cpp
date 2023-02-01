#include <SDL2/SDL.h>

#include "Constants/constants.hpp"


void Colour::set_render_black (SDL_Renderer * renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
}


void Colour::set_render_white (SDL_Renderer * renderer)
{
    SDL_SetRenderDrawColor(renderer, 1, 1, 1, 1);
}