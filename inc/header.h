#pragma once

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include "../resource/SDL2/SDL.h"
#include "../resource/SDL2/SDL_timer.h"
#include "../resource/SDL2/SDL_image.h"

#define WINDOW_WIDTH (40 * 20)
#define WINDOW_HEIGHT (30 * 20)
#define BLOCK_SIZE (20)
#define SPEED (120)
#define FPS (30)

SDL_Point get_size(SDL_Texture *tex);

int mx_min(int, int);
int mx_max(int, int);
int mx_round(double);
void initialization(void);
int mx_strlen(const char *c);
void win_err(SDL_Window* win);
void mx_printerr(const char *s);
void rend_err(SDL_Renderer* rend, SDL_Window* win);
void tex_err(SDL_Texture* tex, SDL_Renderer* rend, SDL_Window* win);
void surface_err(SDL_Surface* surface, SDL_Renderer* rend, SDL_Window* win);

