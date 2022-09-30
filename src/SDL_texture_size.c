#include "../inc/header.h"

SDL_Point get_size(SDL_Texture *tex) {
    SDL_Point size;
    SDL_QueryTexture(tex, NULL, NULL, &size.x, &size.y);
    return size;
}

