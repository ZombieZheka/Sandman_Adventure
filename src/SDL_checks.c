#include "../inc/header.h"

void initialization(void) {
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0) {
        mx_printerr("error initializing SDL: ");
        mx_printerr(SDL_GetError());
        mx_printerr("\n");
        exit(-1);
    }
}

void win_err(SDL_Window* win) {
    if (!win) {
        mx_printerr("error creating window: ");
        mx_printerr(SDL_GetError());
        mx_printerr("\n");
        SDL_Quit();
	    exit(-1);
    }
}

void surface_err(SDL_Surface* surface, SDL_Renderer* rend, SDL_Window* win) {
    if (!surface) {
        mx_printerr("error creating surface");
        mx_printerr("\n");
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        exit(-1);
    }
}

void rend_err(SDL_Renderer* rend, SDL_Window* win) {
    if (!rend) {
        mx_printerr("error creating renderer: ");
        mx_printerr(SDL_GetError());
        mx_printerr("\n");
        SDL_DestroyWindow(win);
        SDL_Quit();
        exit(-1);
    }
}

void tex_err(SDL_Texture* tex, SDL_Renderer* rend, SDL_Window* win) {
    if (!tex) {
        mx_printerr("error creating texture: ");
        mx_printerr(SDL_GetError());
        mx_printerr("\n");
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        exit(-1);
    }
}

