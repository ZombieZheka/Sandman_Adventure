#include "../inc/header.h"

bool check_collision(char s) {
    return (s == '#' || s == 'F' || s == 'D'
            || s == 'L' || s == 'R' || s == 'U' || s == '^'
            || s == 'u' || s == 'q' || s == 'Q') ? true : false;
}

bool check_mummy(double x_pos, int y_pos, double mummy_x, int mummy_y) {
    if (y_pos < mummy_y + 1 || y_pos > mummy_y + 3)
        return false;
    if (x_pos < mummy_x + 20 && x_pos > mummy_x - 20)
        return true;
    return false;
}

bool on_platform(char s, int k1, int k2) {
    return (s == '=' && k1 - k2 > -2 && k1 - k2 < 2) ? true : false;
}

int main(void) {
    initialization();
    SDL_Window *win = SDL_CreateWindow("Sandman adventure",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       WINDOW_WIDTH,
                                       WINDOW_HEIGHT, 0);
    win_err(win);
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    SDL_Renderer *rend = SDL_CreateRenderer(win, -1, render_flags);
    rend_err(rend, win);
    //bg
    SDL_Rect dest;
    dest.x = 0;
    dest.y = 0;
    dest.h = WINDOW_HEIGHT;
    dest.w = WINDOW_WIDTH;
    /*
    SDL_Surface *bg = IMG_Load("resource/bg.png");
    surface_err(bg, rend, win);
    SDL_RenderCopy(rend, SDL_CreateTextureFromSurface(rend, bg), NULL, &dest);
    SDL_RenderPresent(rend);
    */  
    //Frames
    //main
    SDL_Surface *hero_main = IMG_Load("resource/character/main.png");
    surface_err(hero_main, rend, win);
    SDL_Surface *hero_jump = IMG_Load("resource/character/jump/jump.png");
    surface_err(hero_jump, rend, win);
    SDL_Texture *tex_static = SDL_CreateTextureFromSurface(rend, hero_main);
    SDL_FreeSurface(hero_main);
    //left
    SDL_Surface *hero_left_0 = IMG_Load("resource/character/walk_left/0.png");
    SDL_Surface *hero_left_1 = IMG_Load("resource/character/walk_left/1.png");
    SDL_Surface *hero_left_2 = IMG_Load("resource/character/walk_left/2.png");
    surface_err(hero_left_0, rend, win);
    surface_err(hero_left_1, rend, win);
    surface_err(hero_left_2, rend, win);
    SDL_Surface *hero_jump_left = IMG_Load("resource/character/jump/jump_left.png");
    surface_err(hero_jump_left, rend, win);
    SDL_Surface *scroll_left_0 = IMG_Load("resource/character/roll_left/roll1.png");
    SDL_Surface *scroll_left_1 = IMG_Load("resource/character/roll_left/roll2.png");
    SDL_Surface *scroll_left_2 = IMG_Load("resource/character/roll_left/roll3.png");
    surface_err(scroll_left_0, rend, win);
    surface_err(scroll_left_1, rend, win);
    surface_err(scroll_left_2, rend, win);
    //right
    SDL_Surface* hero_right_0 = IMG_Load("resource/character/walk_right/0.png");
    SDL_Surface* hero_right_1 = IMG_Load("resource/character/walk_right/1.png");
    SDL_Surface* hero_right_2 = IMG_Load("resource/character/walk_right/2.png");
    surface_err(hero_right_0, rend, win);
    surface_err(hero_right_1, rend, win);
    surface_err(hero_right_2, rend, win);
    SDL_Surface *hero_jump_right = IMG_Load("resource/character/jump/jump_right.png");
    surface_err(hero_jump_right, rend, win);
    SDL_Surface *scroll_right_0 = IMG_Load("resource/character/roll_right/roll1.png");
    SDL_Surface *scroll_right_1 = IMG_Load("resource/character/roll_right/roll2.png");
    SDL_Surface *scroll_right_2 = IMG_Load("resource/character/roll_right/roll3.png");
    surface_err(scroll_right_0, rend, win);
    surface_err(scroll_right_1, rend, win);
    surface_err(scroll_right_2, rend, win);
    //hide
    SDL_Surface* hide_0 = IMG_Load("resource/character/hide/hide0.png");
    SDL_Surface* hide_1 = IMG_Load("resource/character/hide/hide1.png");
    SDL_Surface* hide_2 = IMG_Load("resource/character/hide/hide2.png");
    SDL_Surface* hide_3 = IMG_Load("resource/character/hide/hide3.png");
    SDL_Surface* hide_4 = IMG_Load("resource/character/hide/hide4.png");
    surface_err(hide_0, rend, win);
    surface_err(hide_1, rend, win);
    surface_err(hide_2, rend, win);
    surface_err(hide_3, rend, win);
    surface_err(hide_4, rend, win);

    SDL_Texture* array_left[3] = {SDL_CreateTextureFromSurface(rend, hero_left_0),
                                   SDL_CreateTextureFromSurface(rend, hero_left_1),
                                   SDL_CreateTextureFromSurface(rend, hero_left_2)};
    SDL_Texture* array_right[3] = {SDL_CreateTextureFromSurface(rend, hero_right_0),
                                   SDL_CreateTextureFromSurface(rend, hero_right_1),
                                   SDL_CreateTextureFromSurface(rend, hero_right_2)};

    SDL_Texture* scroll_left[3] = {SDL_CreateTextureFromSurface(rend, scroll_left_0),
                                   SDL_CreateTextureFromSurface(rend, scroll_left_1),
                                   SDL_CreateTextureFromSurface(rend, scroll_left_2)};
    SDL_Texture* scroll_right[3] = {SDL_CreateTextureFromSurface(rend, scroll_right_0),
                                   SDL_CreateTextureFromSurface(rend, scroll_right_1),
                                   SDL_CreateTextureFromSurface(rend, scroll_right_2)};

    SDL_Texture* hiding[5] = {SDL_CreateTextureFromSurface(rend, hide_0),
                                   SDL_CreateTextureFromSurface(rend, hide_1),
                                   SDL_CreateTextureFromSurface(rend, hide_2),
                                   SDL_CreateTextureFromSurface(rend, hide_3),
                                   SDL_CreateTextureFromSurface(rend, hide_4)};

    SDL_Point hero = get_size(tex_static);

    SDL_Texture* tex;

    for (int i = 0; i < 3; i++) {
        tex = array_left[i];
        tex_err(tex, rend, win);
    }
    for (int i = 0; i < 3; i++) {
        tex = array_right[i];
        tex_err(tex, rend, win);
    }
    
    // map constructor
    SDL_Rect dest_map;
    dest_map.h = BLOCK_SIZE;
    dest_map.w = BLOCK_SIZE;
    dest_map.x = 0;
    dest_map.y = 0;
    SDL_Surface *bgo1 = IMG_Load("resource/blocks/bgo1.png");
    SDL_Surface *bgo2 = IMG_Load("resource/blocks/bgo2.png");
    SDL_Surface *earth1 = IMG_Load("resource/blocks/earth1.png");
    SDL_Surface *earth2 = IMG_Load("resource/blocks/earth2.png");
    SDL_Surface *earth3 = IMG_Load("resource/blocks/earth3.png");
    SDL_Surface *earth4 = IMG_Load("resource/blocks/earth4.png");
    SDL_Surface *earth5 = IMG_Load("resource/blocks/earth5.png");
    SDL_Surface *earth6 = IMG_Load("resource/blocks/earth6.png");
    SDL_Surface *earth7 = IMG_Load("resource/blocks/earth7.png");
    SDL_Surface *earth8 = IMG_Load("resource/blocks/earth8.png");
    SDL_Surface *earth9 = IMG_Load("resource/blocks/earth9.png");
    SDL_Surface *earthAngle1 = IMG_Load("resource/blocks/earthAngle1.png");
    SDL_Surface *earthAngle2 = IMG_Load("resource/blocks/earthAngle2.png");
    SDL_Surface *earthAngle3 = IMG_Load("resource/blocks/earthAngle3.png");
    SDL_Surface *earthAngle4 = IMG_Load("resource/blocks/earthAngle4.png");
    SDL_Surface *earthAngle5 = IMG_Load("resource/blocks/earthAngle5.png");
    SDL_Surface *earthAngle6 = IMG_Load("resource/blocks/earthAngle6.png");
    SDL_Surface *earthAngle7 = IMG_Load("resource/blocks/earthAngle7.png");
    SDL_Surface *earthAngle8 = IMG_Load("resource/blocks/earthAngle8.png");
    SDL_Surface *earthBald1 = IMG_Load("resource/blocks/earthBald1.png");
    SDL_Surface *earthBald2 = IMG_Load("resource/blocks/earthBald2.png");
    SDL_Surface *earthBald3 = IMG_Load("resource/blocks/earthBald3.png");
    SDL_Surface *earthBald4 = IMG_Load("resource/blocks/earthBald4.png");
    SDL_Surface *earthBald5 = IMG_Load("resource/blocks/earthBald5.png");
    SDL_Surface *earthBald6 = IMG_Load("resource/blocks/earthBald6.png");
    SDL_Surface *earthTransition1 = IMG_Load("resource/blocks/earthTransition1.png");
    SDL_Surface *earthTransition2 = IMG_Load("resource/blocks/earthTransition2.png");
    SDL_Surface *earthTransition3 = IMG_Load("resource/blocks/earthTransition3.png");
    SDL_Surface *earthTransition4 = IMG_Load("resource/blocks/earthTransition4.png");
    SDL_Surface *cactus1 = IMG_Load("resource/map/cactus1.png");
    SDL_Surface *cactus2 = IMG_Load("resource/map/cactus2.png");
    SDL_Surface *cactus3 = IMG_Load("resource/map/cactus3.png");
    SDL_Surface *cactus4 = IMG_Load("resource/map/cactus4.png");
    SDL_Surface *stone1 = IMG_Load("resource/map/stone1.png");
    SDL_Surface *stone2 = IMG_Load("resource/map/stone2.png");
    SDL_Surface *grass = IMG_Load("resource/map/grass.png");
    SDL_Surface *exit1 = IMG_Load("resource/exit/exit1.png");
    SDL_Surface *exit2 = IMG_Load("resource/exit/exit2.png");
    SDL_Surface *doortop = IMG_Load("resource/door/doorTop.png");
    SDL_Surface *doorbottom = IMG_Load("resource/door/doorBottom.png");

    surface_err(bgo1, rend, win);
    surface_err(bgo2, rend, win);
    surface_err(earth1, rend, win);
    surface_err(earth2, rend, win);
    surface_err(earth3, rend, win);
    surface_err(earth4, rend, win);
    surface_err(earth5, rend, win);
    surface_err(earth6, rend, win);
    surface_err(earth7, rend, win);
    surface_err(earth8, rend, win);
    surface_err(earth9, rend, win);
    surface_err(earthAngle1, rend, win);
    surface_err(earthAngle2, rend, win);
    surface_err(earthAngle3, rend, win);
    surface_err(earthAngle4, rend, win);
    surface_err(earthAngle5, rend, win);
    surface_err(earthAngle6, rend, win);
    surface_err(earthAngle7, rend, win);
    surface_err(earthAngle8, rend, win);
    surface_err(earthBald1, rend, win);
    surface_err(earthBald2, rend, win);
    surface_err(earthBald3, rend, win);
    surface_err(earthBald4, rend, win);
    surface_err(earthBald5, rend, win);
    surface_err(earthBald6, rend, win);
    surface_err(earthTransition1, rend, win);
    surface_err(earthTransition2, rend, win);
    surface_err(earthTransition3, rend, win);
    surface_err(earthTransition4, rend, win);
    surface_err(cactus1, rend, win);
    surface_err(cactus2, rend, win);
    surface_err(cactus3, rend, win);
    surface_err(cactus4, rend, win);
    surface_err(stone1, rend, win);
    surface_err(stone2, rend, win);
    surface_err(grass, rend, win);
    surface_err(exit1, rend, win);
    surface_err(exit2, rend, win);
    surface_err(doortop, rend, win);
    surface_err(doorbottom, rend, win);

    SDL_Texture *tex_bgo1 = SDL_CreateTextureFromSurface(rend, bgo1);
    SDL_Texture *tex_bgo2 = SDL_CreateTextureFromSurface(rend, bgo2);
    SDL_Texture *tex_earth1 = SDL_CreateTextureFromSurface(rend, earth1);
    SDL_Texture *tex_earth2 = SDL_CreateTextureFromSurface(rend, earth2);
    SDL_Texture *tex_earth3 = SDL_CreateTextureFromSurface(rend, earth3);
    SDL_Texture *tex_earth4 = SDL_CreateTextureFromSurface(rend, earth4);
    SDL_Texture *tex_earth5 = SDL_CreateTextureFromSurface(rend, earth5);
    SDL_Texture *tex_earth6 = SDL_CreateTextureFromSurface(rend, earth6);
    SDL_Texture *tex_earth7 = SDL_CreateTextureFromSurface(rend, earth7);
    SDL_Texture *tex_earth8 = SDL_CreateTextureFromSurface(rend, earth8);
    SDL_Texture *tex_earth9 = SDL_CreateTextureFromSurface(rend, earth9);
    SDL_Texture *tex_earthAngle1 = SDL_CreateTextureFromSurface(rend, earthAngle1);
    SDL_Texture *tex_earthAngle2 = SDL_CreateTextureFromSurface(rend, earthAngle2);
    SDL_Texture *tex_earthAngle3 = SDL_CreateTextureFromSurface(rend, earthAngle3);
    SDL_Texture *tex_earthAngle4 = SDL_CreateTextureFromSurface(rend, earthAngle4);
    SDL_Texture *tex_earthAngle5 = SDL_CreateTextureFromSurface(rend, earthAngle5);
    SDL_Texture *tex_earthAngle6 = SDL_CreateTextureFromSurface(rend, earthAngle6);
    SDL_Texture *tex_earthAngle7 = SDL_CreateTextureFromSurface(rend, earthAngle7);
    SDL_Texture *tex_earthAngle8 = SDL_CreateTextureFromSurface(rend, earthAngle8);
    SDL_Texture *tex_earthBald1 = SDL_CreateTextureFromSurface(rend, earthBald1);
    SDL_Texture *tex_earthBald2 = SDL_CreateTextureFromSurface(rend, earthBald2);
    SDL_Texture *tex_earthBald3 = SDL_CreateTextureFromSurface(rend, earthBald3);
    SDL_Texture *tex_earthBald4 = SDL_CreateTextureFromSurface(rend, earthBald4);
    SDL_Texture *tex_earthBald5 = SDL_CreateTextureFromSurface(rend, earthBald5);
    SDL_Texture *tex_earthBald6 = SDL_CreateTextureFromSurface(rend, earthBald6);
    SDL_Texture *tex_earthTransition1 = SDL_CreateTextureFromSurface(rend, earthTransition1);
    SDL_Texture *tex_earthTransition2 = SDL_CreateTextureFromSurface(rend, earthTransition2);
    SDL_Texture *tex_earthTransition3 = SDL_CreateTextureFromSurface(rend, earthTransition3);
    SDL_Texture *tex_earthTransition4 = SDL_CreateTextureFromSurface(rend, earthTransition4);
    SDL_Texture *tex_cactus1 = SDL_CreateTextureFromSurface(rend, cactus1);
    SDL_Texture *tex_cactus2 = SDL_CreateTextureFromSurface(rend, cactus2);
    SDL_Texture *tex_cactus3 = SDL_CreateTextureFromSurface(rend, cactus3);
    SDL_Texture *tex_cactus4 = SDL_CreateTextureFromSurface(rend, cactus4);
    SDL_Texture *tex_stone1 = SDL_CreateTextureFromSurface(rend, stone1);
    SDL_Texture *tex_stone2 = SDL_CreateTextureFromSurface(rend, stone2);
    SDL_Texture *tex_grass = SDL_CreateTextureFromSurface(rend, grass);
    SDL_Texture *tex_exit1 = SDL_CreateTextureFromSurface(rend, exit1);
    SDL_Texture *tex_exit2 = SDL_CreateTextureFromSurface(rend, exit2);
    SDL_Texture *tex_doortop = SDL_CreateTextureFromSurface(rend, doortop);
    SDL_Texture *tex_doorbottom = SDL_CreateTextureFromSurface(rend, doorbottom);

    tex_err(tex_bgo1, rend, win);
    tex_err(tex_bgo2, rend, win);
    tex_err(tex_earth1, rend, win);
    tex_err(tex_earth2, rend, win);
    tex_err(tex_earth3, rend, win);
    tex_err(tex_earth4, rend, win);
    tex_err(tex_earth5, rend, win);
    tex_err(tex_earth6, rend, win);
    tex_err(tex_earth7, rend, win);
    tex_err(tex_earth8, rend, win);
    tex_err(tex_earth9, rend, win);
    tex_err(tex_earthAngle1, rend, win);
    tex_err(tex_earthAngle2, rend, win);
    tex_err(tex_earthAngle3, rend, win);
    tex_err(tex_earthAngle4, rend, win);
    tex_err(tex_earthAngle5, rend, win);
    tex_err(tex_earthAngle6, rend, win);
    tex_err(tex_earthAngle7, rend, win);
    tex_err(tex_earthAngle8, rend, win);
    tex_err(tex_earthBald1, rend, win);
    tex_err(tex_earthBald2, rend, win);
    tex_err(tex_earthBald3, rend, win);
    tex_err(tex_earthBald4, rend, win);
    tex_err(tex_earthBald5, rend, win);
    tex_err(tex_earthBald6, rend, win);
    tex_err(tex_earthTransition1, rend, win);
    tex_err(tex_earthTransition2, rend, win);
    tex_err(tex_earthTransition3, rend, win);
    tex_err(tex_earthTransition4, rend, win);
    tex_err(tex_cactus1, rend, win);
    tex_err(tex_cactus2, rend, win);
    tex_err(tex_cactus3, rend, win);
    tex_err(tex_cactus4, rend, win);
    tex_err(tex_stone1, rend, win);
    tex_err(tex_stone2, rend, win);
    tex_err(tex_grass, rend, win);
    tex_err(tex_exit1, rend, win);
    tex_err(tex_exit2, rend, win);
    tex_err(tex_doortop, rend, win);
    tex_err(tex_doorbottom, rend, win);

    // water
    SDL_Surface *water[8] = {IMG_Load("resource/blocks/water/water1.png"),
                             IMG_Load("resource/blocks/water/water2.png"),
                             IMG_Load("resource/blocks/water/water3.png"),
                             IMG_Load("resource/blocks/water/water4.png"),
                             IMG_Load("resource/blocks/water/water5.png"),
                             IMG_Load("resource/blocks/water/water6.png"),
                             IMG_Load("resource/blocks/water/water7.png"),
                             IMG_Load("resource/blocks/water/water8.png")};
    
    for (int i = 0; i < 8;) surface_err(water[i++], rend, win);
    SDL_Texture *tex_water[8];
    for (int i = 0; i < 8; i++) tex_water[i] = SDL_CreateTextureFromSurface(rend, water[i]);
    for (int i = 0; i < 8;) tex_err(tex_water[i++], rend, win);
    int water_frame = 0;
    SDL_Rect water_dest1;
    water_dest1.h = BLOCK_SIZE;
    water_dest1.w = 2 * BLOCK_SIZE;
    water_dest1.x = 19 * BLOCK_SIZE;
    water_dest1.y = 27 * BLOCK_SIZE;
    SDL_Rect water_dest2;
    water_dest2.h = BLOCK_SIZE;
    water_dest2.w = 2 * BLOCK_SIZE;
    water_dest2.x = 25 * BLOCK_SIZE;
    water_dest2.y = 27 * BLOCK_SIZE;
    SDL_Rect water_dest3;
    water_dest3.h = BLOCK_SIZE;
    water_dest3.w = 2 * BLOCK_SIZE;
    water_dest3.x = 31 * BLOCK_SIZE;
    water_dest3.y = 27 * BLOCK_SIZE;

    //BG
    SDL_Rect BGdest;
    BGdest.h = WINDOW_HEIGHT;
    BGdest.w = WINDOW_WIDTH;
    BGdest.y = 0;
    BGdest.x = 0;
    SDL_Surface *BG = IMG_Load("resource/BG_vertion04_lv1.jpg");
    surface_err(BG, rend, win);
    SDL_Texture *background = SDL_CreateTextureFromSurface(rend, BG);

    SDL_Surface *background_02 = IMG_Load("resource/BG02.jpg");
    surface_err(background_02, rend, win);
    SDL_Texture *tex_background_02 = SDL_CreateTextureFromSurface(rend, background_02);

    //platform
    SDL_Surface *platform1 = IMG_Load("resource/platform/platform1.png");
    SDL_Surface *platform2 = IMG_Load("resource/platform/platform2.png");
    SDL_Surface *platform3 = IMG_Load("resource/platform/platform3.png");
    surface_err(platform1, rend, win);
    surface_err(platform2, rend, win);
    surface_err(platform3, rend, win);
    SDL_Texture *tex_platform1 = SDL_CreateTextureFromSurface(rend, platform1);
    SDL_Texture *tex_platform2 = SDL_CreateTextureFromSurface(rend, platform2);
    SDL_Texture *tex_platform3 = SDL_CreateTextureFromSurface(rend, platform3);
    tex_err(tex_platform1, rend, win);
    tex_err(tex_platform2, rend, win);
    tex_err(tex_platform3, rend, win);

    //Mummy
    SDL_Surface *mummy_left_frames[5] = {IMG_Load("resource/mummy/walk-left/mummy1.png"),
                                         IMG_Load("resource/mummy/walk-left/mummy2.png"),
                                         IMG_Load("resource/mummy/walk-left/mummy3.png"),
                                         IMG_Load("resource/mummy/walk-left/mummy4.png"),
                                         IMG_Load("resource/mummy/walk-left/mummy5.png")};
    SDL_Surface *mummy_right_frames[5] = {IMG_Load("resource/mummy/walk-right/mummy1.png"),
                                         IMG_Load("resource/mummy/walk-right/mummy2.png"),
                                         IMG_Load("resource/mummy/walk-right/mummy3.png"),
                                         IMG_Load("resource/mummy/walk-right/mummy4.png"),
                                         IMG_Load("resource/mummy/walk-right/mummy5.png")};
    SDL_Surface *mummy_left_attack_frames[5] = {IMG_Load("resource/mummy/attack-left/mummy1.png"),
                                                IMG_Load("resource/mummy/attack-left/mummy2.png"),
                                                IMG_Load("resource/mummy/attack-left/mummy3.png"),
                                                IMG_Load("resource/mummy/attack-left/mummy4.png"),
                                                IMG_Load("resource/mummy/attack-left/mummy5.png")};
    SDL_Surface *mummy_right_attack_frames[5] = {IMG_Load("resource/mummy/attack-right/mummy1.png"),
                                                 IMG_Load("resource/mummy/attack-right/mummy2.png"),
                                                 IMG_Load("resource/mummy/attack-right/mummy3.png"),
                                                 IMG_Load("resource/mummy/attack-right/mummy4.png"),
                                                 IMG_Load("resource/mummy/attack-right/mummy5.png")};
    
    for (int i = 0; i < 5; i++) surface_err(mummy_left_frames[i], rend, win);
    for (int i = 0; i < 5; i++) surface_err(mummy_right_frames[i], rend, win);
    for (int i = 0; i < 5; i++) surface_err(mummy_left_attack_frames[i], rend, win);
    for (int i = 0; i < 5; i++) surface_err(mummy_right_attack_frames[i], rend, win);

    SDL_Texture *tex_mummy_left_frames[5];
    SDL_Texture *tex_mummy_right_frames[5];
    SDL_Texture *tex_mummy_left_attack_frames[5];
    SDL_Texture *tex_mummy_right_attack_frames[5];

    for (int i = 0; i < 5; i++) tex_mummy_left_frames[i] = SDL_CreateTextureFromSurface(rend, mummy_left_frames[i]);
    for (int i = 0; i < 5; i++) tex_mummy_right_frames[i] = SDL_CreateTextureFromSurface(rend, mummy_right_frames[i]);
    for (int i = 0; i < 5; i++) tex_mummy_left_attack_frames[i] = SDL_CreateTextureFromSurface(rend, mummy_left_attack_frames[i]);
    for (int i = 0; i < 5; i++) tex_mummy_right_attack_frames[i] = SDL_CreateTextureFromSurface(rend, mummy_right_attack_frames[i]);

    for (int i = 0; i < 5; i++) tex_err(tex_mummy_left_frames[i], rend, win);
    for (int i = 0; i < 5; i++) tex_err(tex_mummy_right_frames[i], rend, win);
    for (int i = 0; i < 5; i++) tex_err(tex_mummy_left_attack_frames[i], rend, win);
    for (int i = 0; i < 5; i++) tex_err(tex_mummy_right_attack_frames[i], rend, win);
    
    SDL_Rect mummy_dest1;
    mummy_dest1.h = BLOCK_SIZE * 4;
    mummy_dest1.w = BLOCK_SIZE * 3;
    mummy_dest1.y = 0;
    mummy_dest1.x = BLOCK_SIZE * 14;
    SDL_Rect mummy_dest2;
    mummy_dest2.h = BLOCK_SIZE * 4;
    mummy_dest2.w = BLOCK_SIZE * 3;
    mummy_dest2.y = BLOCK_SIZE * 6;
    mummy_dest2.x = BLOCK_SIZE * 27;
    SDL_Rect mummy_dest3;
    mummy_dest3.h = BLOCK_SIZE * 4;
    mummy_dest3.w = BLOCK_SIZE * 3;
    mummy_dest3.y = BLOCK_SIZE * 15;
    mummy_dest3.x = BLOCK_SIZE * 5;

    bool mummy1_left = false;
    bool mummy2_left = true;
    bool mummy3_left = false;
    bool mummy1_right = true;
    bool mummy2_right = false;
    bool mummy3_right = true;
    bool mummy1_is_attack = false;
    bool mummy2_is_attack = false;
    bool mummy3_is_attack = false;
    
    int mummy1_max = BLOCK_SIZE * 31;
    int mummy1_min = BLOCK_SIZE * 10;
    int mummy2_max = BLOCK_SIZE * 32;
    int mummy2_min = BLOCK_SIZE * 20;
    int mummy3_max = BLOCK_SIZE * 15;
    int mummy3_min = BLOCK_SIZE * 6;
    
    int mummy1_frame = 0;
    int mummy2_frame = 0;
    int mummy3_frame = 0;
    //end mummy


    SDL_Surface *menu = IMG_Load("resource/stages/menu.png");
    SDL_Surface *instructions = IMG_Load("resource/stages/instractions.png");
    SDL_Surface *lost = IMG_Load("resource/stages/gameLost.png");
    SDL_Surface *finish = IMG_Load("resource/stages/finish.png");
    surface_err(menu, rend, win);
    surface_err(instructions, rend, win);
    surface_err(lost, rend, win);
    surface_err(finish, rend, win);
    SDL_Texture *tex_menu = SDL_CreateTextureFromSurface(rend, menu);
    SDL_Texture *tex_instructions = SDL_CreateTextureFromSurface(rend, instructions);
    SDL_Texture *tex_lost = SDL_CreateTextureFromSurface(rend, lost);
    SDL_Texture *tex_finish = SDL_CreateTextureFromSurface(rend, finish);
    tex_err(tex_menu, rend, win);
    tex_err(tex_instructions, rend, win);
    tex_err(tex_lost, rend, win);
    tex_err(tex_finish, rend, win);

    SDL_Rect menu_dest;
    menu_dest.x = 0;
    menu_dest.y = 0;
    menu_dest.h = WINDOW_HEIGHT;
    menu_dest.w = WINDOW_WIDTH;

    float x_pos = 0;
    float y_pos = WINDOW_HEIGHT;
    float x_vel = 0;
    float y_vel = 0;

    int up = 0;
    int down = 0;
    int left = 0;
    int right = 0;

    int k = 0;
    bool jump = false;
    int start_pos = 0;

    // set to 1 when window close button is pressed
    int close_requested = 0;
    
    int temp_frame = 0;
    bool left_frames = false;
    bool right_frames = false;
    bool static_frames = true;

    //menu
    bool close_menu = false;
    SDL_Event event;
    SDL_RenderCopy(rend, tex_menu, NULL, &menu_dest);
    SDL_RenderPresent(rend);
    while (!close_menu) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    return 0;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.scancode) {
                        case SDL_SCANCODE_RETURN:
                            close_menu = true;
                            break;
                        case SDL_SCANCODE_ESCAPE:
                            return 0;
                    }
                    break;
            }
        }
    }

    int level = 1;
    SDL_Rect lostdest;
    lostdest.w = WINDOW_WIDTH;
    lostdest.h = WINDOW_HEIGHT;
    lostdest.x = 0;
    lostdest.y = 0;
    //hero coor
    SDL_Rect hero_dest;
    hero_dest.w = BLOCK_SIZE;
    hero_dest.h = BLOCK_SIZE * 2;
    bool ability = false;
    
    SDL_Rect water_dest4;
    SDL_Rect water_dest5;
    SDL_Rect water_dest6;
    SDL_Rect water_dest7;
    SDL_Rect water_dest8;
    SDL_Rect water_dest9;
    SDL_Rect water_dest10;

    hero_dest.x = 20;
    hero_dest.y = 540;
    //levels
    //blocks
    SDL_Rect wall_dest;
    wall_dest.x = 0;
    wall_dest.y = 0;
    wall_dest.w = BLOCK_SIZE;
    wall_dest.h = BLOCK_SIZE;
    //level1
    char lv1[30][40] = {{'#', 'D', 'D', '#', '#', '#', '#', '#', '#', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', '#'}, 
                        {'R', 'E', 'e', 'Q', '#', '#', '#', '#', 'q', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'L'},
                        {'R', '0', '.', '.', 'Q', 'D', 'D', 'q', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '1', '2', '.', '.', '.', '.', '.', 'L'},
                        {'R', '9', '.', '.', '.', '.', '.', '.', '.', 'g', '.', '.', 'S', '.', '.', '.', 'g', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'S', '.', '.', '3', '4', '.', '.', '.', '.', '.', 'L'},
                        {'#', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'u', '.', '.', '.', 'L'},
                        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', 'q', '=', '=', '.', '.', 'L'},
                        {'#', '#', '#', '#', '#', '#', '#', 'D', 'D', 'D', '#', '#', '#', '#', '#', '#', '#', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'q', '.', '.', '.', '.', 'U', '#'},
                        {'#', '#', '#', '#', '#', '#', 'q', '.', '.', '.', 'Q', '#', '#', '#', '#', '#', 'q', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'g', 'U', '#', '#'},
                        {'#', '#', '#', '#', '#', 'q', '.', '.', '.', '.', '.', 'Q', 'D', 'D', 'D', 'q', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'U', '#', '#', '#'},
                        {'#', '#', '#', '#', 'q', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'g', '.', '.', '.', '.', '.', 'S', '.', '.', '.', '.', 's', '.', '.', '.', '.', 'g', '.', '.', '.', '.', 'U', '#', '#', '#', '#'},
                        {'#', 'D', 'D', 'D', '.', '.', '.', '.', '.', 'U', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', '#', '#', '#', '#', '#'},
                        {'R', '.', '.', '.', '.', '.', '.', '.', 'U', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
                        {'R', '.', '.', '.', '.', '.', 'g', 'U', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', 'q', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'Q', '#', '#', '#', '#', '#', '#', '#', '#'},
                        {'R', '.', '.', '.', '.', '.', 'U', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', 'D', 'D', 'q', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'Q', 'D', 'D', 'D', 'D', 'D', 'D', '#'},
                        {'R', '.', '.', 'U', 'F', 'F', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', 'q', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'L'},
                        {'R', '.', '.', 'Q', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'q', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'L'},
                        {'R', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'g', '.', '.', '.', '.', '.', 'L'},
                        {'R', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'U', 'F', 'u', '.', '.', 'U', 'F', 'F', 'u', '.', '.', 'U', 'F', 'F', 'F', 'F', 'F', 'u', '.', '.', 'L'},
                        {'R', '.', '.', '.', 'S', '.', '.', '.', '.', '.', 'g', '.', 's', '.', '.', '.', 's', '.', 'U', '#', '#', 'R', '.', '.', 'Q', 'D', 'D', 'q', '.', '.', 'L', '#', '#', '#', '#', '#', 'R', '.', '.', 'L'},
                        {'R', '=', '=', 'U', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', '#', '#', 'D', 'q', '.', '.', '.', '.', '.', '.', '.', '.', 'Q', '#', '#', 'D', 'D', 'D', 'q', '.', '.', 'L'},
                        {'#', 'F', 'F', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', 'q', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'Q', 'q', '.', '.', '.', '.', '.', '.', 'L'},
                        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', 'D', 'D', 'q', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'L'},
                        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', 'D', 'q', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'L'},
                        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', 'D', 'q', '.', '.', '.', '.', '.', '.', '.', '.', '1', '2', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'L'},
                        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', 'q', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '3', '4', '.', '.', '.', '.', '.', 's', '.', '.', '.', '.', '.', 'g', 'S', '.', '.', 'L'},
                        {'#', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'q', '.', '.', '.', '.', '.', 'g', 'U', 'u', '.', '.', 'U', 'F', 'F', 'u', '.', '.', 'U', 'F', 'F', 'u', '.', '.', 'U', 'F', 'F', 'u', '=', '=', 'L'},
                        {'R', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 's', 'U', '#', 'R', '.', '.', 'L', '#', '#', 'R', '.', '.', 'L', '#', '#', 'R', '.', '.', 'L', '#', '#', '#', 'F', 'F', '#'},
                        {'R', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'U', 'F', 'F', '#', '#', 'R', '^', '^', 'L', '#', '#', 'R', '^', '^', 'L', '#', '#', 'R', '^', '^', 'L', '#', '#', '#', '#', '#', '#'},
                        {'R', '.', 's', '.', '.', '.', 'g', '.', '.', 'S', '.', '.', 'U', '#', '#', '#', '#', '#', '#', 'F', 'F', '#', '#', '#', '#', 'F', 'F', '#', '#', '#', '#', 'F', 'F', '#', '#', '#', '#', '#', '#', '#'},
                        {'#', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}};
    //level2
    char lv2[30][40] = {{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}, 
                        {'#', 'D', 'D', 'D', 'D', '#', '#', '#', 'D', 'D', 'q', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'Q', '#', '#', '#', '#', '#', '#', '#', '#', '#', 'D', 'D', 'D', 'D', '#'},
                        {'R', '.', '.', '.', '.', 'L', '#', 'R', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'Q', '#', '#', '#', '#', '#', '#', '#', 'q', '.', '.', '.', '.', 'L'},
                        {'R', '.', '.', 'E', 'e', 'L', '#', 'R', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'Q', '#', '#', '#', '#', '#', 'q', '.', '.', '.', '.', '.', 'L'},
                        {'R', '.', '.', '0', '.', 'L', '#', 'R', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '1', '2', '.', '.', '.', '.', '.', 'Q', 'D', 'D', 'D', 'q', '.', '.', '.', '.', '.', '.', 'L'},
                        {'R', '.', '.', '9', '.', 'L', '#', '#', 'F', 'u', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '3', '4', '.', '.', '.', '.', '.', '.', 'g', '.', '.', '.', '.', 'S', '.', '.', '.', '.', 'L'},
                        {'R', '.', 'g', 'U', 'F', '#', '#', '#', '#', '#', 'F', 'u', '.', '.', '.', 'U', 'F', 'u', '.', '.', '.', 'U', 'u', '.', '.', '.', 'U', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'u', '.', '.', '.', '.', 'L'},
                        {'R', '.', 'Q', '#', '#', '#', '#', '#', '#', '#', '#', 'R', '^', '^', '^', 'L', '#', 'R', '^', '^', '^', 'L', 'R', '^', '^', '^', 'L', '#', '#', '#', '#', '#', '#', '#', 'R', '.', '.', '.', '.', 'L'},
                        {'R', '.', '.', 'Q', 'D', 'D', 'D', 'D', 'D', '#', '#', '#', 'F', 'F', 'F', '#', '#', '#', 'F', 'F', 'F', '#', '#', 'F', 'F', 'F', '#', '#', '#', '#', '#', '#', '#', '#', 'q', '.', '.', '.', '.', 'L'},
                        {'R', '.', '.', '.', '.', '.', '.', '.', '.', 'Q', '#', '#', '#', '#', '#', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', '#', '#', '#', '#', '#', 'q', '.', '.', '.', '.', '.', 'L'},
                        {'R', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'Q', '#', '#', '#', 'R', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'Q', '#', '#', '#', 'q', '.', '.', '.', '.', '.', '.', 'L'},
                        {'R', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'Q', '#', '#', 'R', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'Q', 'D', 'D', '.', '.', '.', '.', '.', '.', '.', 'L'},
                        {'R', '.', '.', 'g', '.', '.', '.', '.', '.', '.', '.', '.', 'Q', '#', 'R', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'S', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'L'},
                        {'R', '=', '=', 'U', 'F', 'u', '.', 'F', 'g', '.', '.', '.', '.', 'L', 'R', '.', '.', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'u', '.', '.', '.', '.', 'L'},
                        {'#', 'F', 'F', '#', 'q', '.', '.', 'L', 'F', '.', '.', '.', '.', 'L', 'R', '.', '.', 'L', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', 'R', 'g', '.', '.', '.', 'L'},
                        {'#', '#', '#', 'q', '.', '.', '.', 'Q', 'D', 'u', '.', '.', '.', 'L', 'R', '.', '.', 'L', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', 'F', 'F', 'u', '.', 'L'},
                        {'#', '#', 'q', '.', '.', '.', '.', '.', '.', 'Q', 'u', '.', '.', 'L', 'R', '.', '.', 'L', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', 'D', 'D', 'D', 'D', '#', '#', '#', '#', '#', 'q', '.', 'L'},
                        {'#', 'q', '.', '.', 'S', 'F', '.', '.', '.', '.', '.', '.', '.', 'L', 'R', '.', '.', 'Q', 'D', 'D', '#', '#', '#', '#', '#', '#', '#', 'q', '.', '.', '.', '.', 'Q', '#', '#', '#', 'q', '.', '.', 'L'},
                        {'R', '.', '.', '.', 'U', '#', 'u', '.', '.', '.', '.', '.', 'g', 'L', 'R', '.', '.', '.', '.', '.', 'Q', '#', '#', '#', '#', '#', 'q', '.', '.', '.', '.', '.', '.', 'Q', 'D', 'q', '.', '.', '.', 'L'},
                        {'R', '.', '.', 'U', '#', '#', '#', 'u', '.', '.', '.', '=', 'U', '#', 'R', '.', '.', '.', '.', '.', '.', 'Q', 'D', 'D', 'D', 'q', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'L'},
                        {'R', '.', '.', 'Q', 'D', 'D', 'D', 'q', '.', '.', '.', 'U', 'D', '#', 'R', '.', '.', '.', '.', 's', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'g', '.', '.', '.', '.', '.', '.', '.', 'L'},
                        {'R', '.', '.', '.', '.', '.', '.', '.', '.', 'g', 'U', 'q', '.', 'L', 'R', '.', 'U', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'u', '.', 'U', '^', '^', 'u', '.', '.', '.', '.', '.', '.', '=', 'L'},
                        {'R', '.', '.', '.', '.', '.', '.', '.', '.', 'U', 'q', '.', '.', 'Q', 'q', '.', 'Q', '#', '#', '#', '#', '#', '#', '#', '#', '#', 'q', '.', 'Q', 'D', 'D', 'q', '.', '.', '.', '.', '.', '.', '.', 'L'},
                        {'R', '.', '.', '.', '.', '.', '.', '.', 'U', 'q', '.', '.', '.', '.', '.', '.', '.', 'Q', '#', '#', '#', '#', '#', 'D', 'D', 'q', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '1', '2', 'L'},
                        {'R', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'Q', '#', '#', '#', 'q', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '3', '4', 'L'},
                        {'R', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '1', '2', '.', '.', '.', '.', 'Q', 'D', 'q', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 's', 'U', 'F', 'F', '#'},
                        {'R', '=', '.', '.', 'U', 'u', '.', '.', 'S', '.', '.', '.', '.', '3', '4', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'g', '.', '.', '.', 'U', 'F', 'F', 'F', 'F', 'F', 'F', '#', '#', '#', '#'},
                        {'R', '^', '^', '^', 'L', '#', '=', 'F', 'F', 'u', '^', '^', '^', 'U', 'u', '^', '^', 'U', 'F', 'F', 'F', 'F', 'u', '^', '^', 'U', 'u', '^', '^', 'L', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
                        {'#', 'F', 'F', 'F', '#', '#', '#', '#', '#', '#', 'F', 'F', 'F', '#', '#', 'F', 'F', '#', '#', '#', '#', '#', '#', 'F', 'F', '#', '#', 'F', 'F', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
                        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}};

    SDL_Rect platform1_dest;
    SDL_Rect platform2_dest;
    SDL_Rect temp_platform1;
    SDL_Rect temp_platform2;

    int platform1_max = 0;
    int platform2_max = 0;
    int platform1_min = 0;
    int platform2_min = 0;

    if (level == 1) {
        platform1_max = WINDOW_HEIGHT - 13 * BLOCK_SIZE;
        platform2_max = WINDOW_HEIGHT - 16 * BLOCK_SIZE;
        platform1_min = WINDOW_HEIGHT - 5 * BLOCK_SIZE;
        platform2_min = WINDOW_HEIGHT - 11 * BLOCK_SIZE;

        platform1_dest.x = WINDOW_WIDTH - 3 * BLOCK_SIZE;
        platform1_dest.y = platform1_min;
        platform1_dest.w = BLOCK_SIZE;
        platform1_dest.h = BLOCK_SIZE;

        platform2_dest.x = 20;
        platform2_dest.y = platform2_min;
        platform2_dest.w = BLOCK_SIZE;
        platform2_dest.h = BLOCK_SIZE;

        temp_platform1.h = platform1_dest.h;
        temp_platform1.w = platform1_dest.w;
        temp_platform2.h = platform2_dest.h;
        temp_platform2.w = platform2_dest.w;
    }

    while (!close_requested) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    close_requested = 1;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.scancode) {
                        case SDL_SCANCODE_W:
                        case SDL_SCANCODE_SPACE:
                            if (!jump && !ability) {
                                jump = true;
                                up = 1;
                                k = hero.y / 1.5;
                                start_pos = y_pos;
                            }
                            break;
                        case SDL_SCANCODE_A:
                            left = 1;
                            break;
                        case SDL_SCANCODE_S:
                            down = 1;
                            break;
                        case SDL_SCANCODE_D:
                            right = 1;
                            break;
                        case SDL_SCANCODE_Q:
                            ability = !ability;
                            break;
                    }
                    break;
                case SDL_KEYUP:
                    switch (event.key.keysym.scancode) {
                        case SDL_SCANCODE_W:
                        case SDL_SCANCODE_SPACE:
                            jump = false;
                            up = 0;
                            break;
                        case SDL_SCANCODE_A:
                            left = 0;
                            break;
                        case SDL_SCANCODE_S:
                            down = 0;
                            break;
                        case SDL_SCANCODE_D:
                            right = 0;
                            break;
                    }
                    break;
            }
        }

        
        if (mummy1_frame == 5) mummy1_frame = 0; // change 1 for animation max 5 or segmentation will met you with hugs
        if (mummy2_frame == 5) mummy2_frame = 0;
        if (mummy3_frame == 5) mummy3_frame = 0;
        if (left_frames || right_frames) temp_frame = (temp_frame == 2) ? 0 : temp_frame + 1;
        if (water_frame == 7) water_frame = 0;
        // determine velocity
        x_vel = 0, y_vel += (SPEED * 2) / FPS;
        if (up && check_collision(lv1[(int)((y_pos + 1.1 * BLOCK_SIZE) / BLOCK_SIZE) + 1][mx_round(x_pos / BLOCK_SIZE)])) y_vel = -SPEED / 1.5;
        if (down && !up) y_vel = SPEED;
        if (left && !right) {
            x_vel = -SPEED;
            left_frames = true;
            if (right_frames) temp_frame = 0;
            right_frames = false;
            static_frames = false;
        }
        if (right && !left) {
            x_vel = SPEED;
            right_frames = true;
            if (left_frames) temp_frame = 0;
            left_frames = false;
            static_frames = false;
        }
        if (!left && !right) {
            temp_frame = 0;
            left_frames = false;
            right_frames = false;
            static_frames = true;
        }
        if (ability) {
            x_vel /= 1.8;
        }

        // collision detection with bounds for all levels
        //if (x_pos < BLOCK_SIZE) x_pos = BLOCK_SIZE;
        //if (y_pos < BLOCK_SIZE) y_pos = BLOCK_SIZE;
        //if (x_pos > WINDOW_WIDTH - hero_dest.w - BLOCK_SIZE) x_pos = WINDOW_WIDTH - hero_dest.w - BLOCK_SIZE;
        //if (y_pos > WINDOW_HEIGHT - hero_dest.h - BLOCK_SIZE) y_pos = WINDOW_HEIGHT - hero_dest.h - BLOCK_SIZE;

        // collision
        int temp_x_pos = (x_pos + ((!left && right) ? 0 : 0.9) * BLOCK_SIZE) / BLOCK_SIZE;
        int temp_y_pos = (y_pos + 1.1 * BLOCK_SIZE) / BLOCK_SIZE;
        //bool collision = false;

        if (level == 1) {
            // чекаем вправо
            if (check_collision(lv1[(int)(y_pos + 1.9 * BLOCK_SIZE) / BLOCK_SIZE][temp_x_pos + 1])) {
                x_vel = mx_min(0, x_vel);
            } // если способность не включена, то чекаем еще верхний-правьій тайл и мумий
            else if (!ability && check_collision(lv1[(int)(y_pos + 0.4 * BLOCK_SIZE) / BLOCK_SIZE][temp_x_pos + 1])) {
                x_vel = mx_min (0, x_vel);
            }
            else if (!ability && check_mummy(x_pos, (int)(y_pos + 1.9 * BLOCK_SIZE) / BLOCK_SIZE, mummy_dest1.x + BLOCK_SIZE * 0.5, (mummy_dest1.y) / BLOCK_SIZE)) {
                // mummy_dest1 attack
                mummy1_is_attack = true;
                mummy1_right = false;
                mummy1_left = true;
                x_vel = mx_min (0, x_vel);
            }
            else if (!ability && check_mummy(x_pos, (int)(y_pos + 1.9 * BLOCK_SIZE) / BLOCK_SIZE, mummy_dest2.x + BLOCK_SIZE * 0.5, (mummy_dest2.y) / BLOCK_SIZE)) {
                // mummy_dest2 attack
                mummy2_is_attack = true;
                mummy3_right = false;
                mummy2_left = true;
                x_vel = mx_min (0, x_vel);
            }
            else if (!ability && check_mummy(x_pos, (int)(y_pos + 1.9 * BLOCK_SIZE) / BLOCK_SIZE, mummy_dest3.x + BLOCK_SIZE * 0.5, (mummy_dest3.y) / BLOCK_SIZE)) {
                // mummy_dest3 attack
                mummy3_is_attack = true;
                mummy3_right = false;
                mummy3_left = true;
                x_vel = mx_min (0, x_vel);
            }
            
            // чекаем лево
            if (check_collision(lv1[(int)(y_pos + 1.9 * BLOCK_SIZE) / BLOCK_SIZE][temp_x_pos - 1])) {
                x_vel = mx_max (0, x_vel);
            } // если способность не включена, то чекаем еще верхний-левьій тайл и мумий
            else if (!ability && check_collision(lv1[(int)(y_pos + 0.4 * BLOCK_SIZE) / BLOCK_SIZE][temp_x_pos - 1])) {
                x_vel = mx_max (0, x_vel);
            }
            else if (!ability && check_mummy(x_pos, (int)(y_pos + 1.9 * BLOCK_SIZE) / BLOCK_SIZE, mummy_dest1.x + BLOCK_SIZE * 1.5, (mummy_dest1.y) / BLOCK_SIZE)) {
                // mummy_dest1 attack
                mummy1_is_attack = true;
                mummy1_right = true;
                mummy1_left = false;
                x_vel = mx_max (0, x_vel);
            }
            else if (!ability && check_mummy(x_pos, (int)(y_pos + 1.9 * BLOCK_SIZE) / BLOCK_SIZE, mummy_dest2.x + BLOCK_SIZE * 1.5, (mummy_dest2.y) / BLOCK_SIZE)) {
                // mummy_dest2 attack
                mummy2_is_attack = true;
                mummy2_right = true;
                mummy2_left = false;
                x_vel = mx_max (0, x_vel);
            }
            else if (!ability && check_mummy(x_pos, (int)(y_pos + 1.9 * BLOCK_SIZE) / BLOCK_SIZE, mummy_dest3.x + BLOCK_SIZE * 1.5, (mummy_dest3.y) / BLOCK_SIZE)) {
                // mummy_dest3 attack
                mummy3_is_attack = true;
                mummy3_right = true;
                mummy3_left = false;
                x_vel = mx_max (0, x_vel);
            }
            
            // чекаем верхний тайл
            if (check_collision(lv1[temp_y_pos + 1][mx_round(x_pos / BLOCK_SIZE)])) {
                y_vel = mx_min(0, y_vel);
            } // чекаем нижний тайл
            if (check_collision(lv1[temp_y_pos - 1][mx_round(x_pos / BLOCK_SIZE)]) || lv1[temp_y_pos + 1][mx_round(x_pos / BLOCK_SIZE)] == '=') {
                y_vel = mx_max (0, y_vel);
            }
            if (lv1[temp_y_pos + 1][mx_round(x_pos / BLOCK_SIZE)] == '9' || lv1[temp_y_pos + 1][mx_round(x_pos / BLOCK_SIZE)] == '0'
                || lv1[temp_y_pos + 1][mx_round(x_pos / BLOCK_SIZE)] == 'E' || lv1[temp_y_pos + 1][mx_round(x_pos / BLOCK_SIZE)] == 'e') {
                    level++;
                    x_pos = 0;
                    y_pos = WINDOW_HEIGHT;
                    x_vel = 0;
                    y_vel = 0;
                    left = 0;
                    right = 0;
                    hero_dest.x = 8 * BLOCK_SIZE;
                    hero_dest.y = 3 * BLOCK_SIZE;

                    water_dest1.h = BLOCK_SIZE;
                    water_dest1.w = 3 * BLOCK_SIZE;
                    water_dest1.x = 12 * BLOCK_SIZE;
                    water_dest1.y = 7 * BLOCK_SIZE;
                    
                    water_dest2.h = BLOCK_SIZE;
                    water_dest2.w = 3 * BLOCK_SIZE;
                    water_dest2.x = 18 * BLOCK_SIZE;
                    water_dest2.y = 7 * BLOCK_SIZE;
                    
                    water_dest3.h = BLOCK_SIZE;
                    water_dest3.w = 3 * BLOCK_SIZE;
                    water_dest3.x = 23 * BLOCK_SIZE;
                    water_dest3.y = 7 * BLOCK_SIZE;
                    
                    water_dest4.h = BLOCK_SIZE;
                    water_dest4.w = 2 * BLOCK_SIZE;
                    water_dest4.x = 29 * BLOCK_SIZE;
                    water_dest4.y = 21 * BLOCK_SIZE;
                    
                    water_dest5.h = BLOCK_SIZE;
                    water_dest5.w = 3 * BLOCK_SIZE;
                    water_dest5.x = 1 * BLOCK_SIZE;
                    water_dest5.y = 27 * BLOCK_SIZE;
                    
                    water_dest6.h = BLOCK_SIZE;
                    water_dest6.w = 3 * BLOCK_SIZE;
                    water_dest6.x = 10 * BLOCK_SIZE;
                    water_dest6.y = 27 * BLOCK_SIZE;
                    
                    water_dest7.h = BLOCK_SIZE;
                    water_dest7.w = 2 * BLOCK_SIZE;
                    water_dest7.x = 15 * BLOCK_SIZE;
                    water_dest7.y = 27 * BLOCK_SIZE;
                    
                    water_dest8.h = BLOCK_SIZE;
                    water_dest8.w = 2 * BLOCK_SIZE;
                    water_dest8.x = 23 * BLOCK_SIZE;
                    water_dest8.y = 27 * BLOCK_SIZE;
                    
                    water_dest9.h = BLOCK_SIZE;
                    water_dest9.w = 2 * BLOCK_SIZE;
                    water_dest9.x = 27 * BLOCK_SIZE;
                    water_dest9.y = 27 * BLOCK_SIZE;

                    water_dest10.h = BLOCK_SIZE;
                    water_dest10.w = 0 * BLOCK_SIZE;
                    water_dest10.x = 0 * BLOCK_SIZE;
                    water_dest10.y = 27 * BLOCK_SIZE;
                    // SDL_RenderCopy(rend, tex_finish, NULL, &lostdest);
                    // SDL_RenderPresent(rend);
                    // SDL_Delay(10000);
                    // return 0;
            }
            if (lv1[temp_y_pos + 1][mx_round(x_pos / BLOCK_SIZE)] == '=') y_vel -= 400;
            if (lv1[temp_y_pos + 1][mx_round(x_pos / BLOCK_SIZE)] == '^') {
                SDL_RenderCopy(rend, tex_lost, NULL, &lostdest);
                SDL_RenderPresent(rend);
                bool close_request = false;
                while (!close_request) {      
                    while (SDL_PollEvent(&event)) {
                        switch (event.type) {
                            case SDL_QUIT:
                                close_requested = 1;
                                break;
                            case SDL_KEYUP:
                                switch (event.key.keysym.scancode) {
                                    case SDL_SCANCODE_SPACE:
                                        close_request = true;   
                                }
                                break;
                        }
                    }
                }
                //stat val
                close_request = false;
                hero_dest.x = 20;
                hero_dest.y = 540;
                x_pos = 0;
                y_pos = WINDOW_HEIGHT;
                x_vel = 0;
                y_vel = 0;
                left = 0;
                right = 0;
                SDL_RenderClear(rend);
                SDL_RenderCopy(rend, background, NULL, &menu_dest);
                SDL_RenderCopy(rend, tex_instructions, NULL, &menu_dest);
                SDL_RenderPresent(rend);
                SDL_Delay(5000);
                continue;
            }
        }
        if (level == 2) {
            // чекаем вправо
            if (check_collision(lv2[(int)(y_pos + 1.9 * BLOCK_SIZE) / BLOCK_SIZE][temp_x_pos + 1])) {
                x_vel = mx_min(0, x_vel);
            } // если способность не включена, то чекаем еще верхний-правьій тайл
            else if (!ability && check_collision(lv2[(int)(y_pos + 0.4 * BLOCK_SIZE) / BLOCK_SIZE][temp_x_pos + 1])) {
                x_vel = mx_min (0, x_vel);
            } // чекаем лево
            if (check_collision(lv2[(int)(y_pos + 1.9 * BLOCK_SIZE) / BLOCK_SIZE][temp_x_pos - 1])) {
                x_vel = mx_max (0, x_vel);
            } // если способность не включена, то чекаем еще верхний-левьій тайл
            else if (!ability && check_collision(lv2[(int)(y_pos + 0.4 * BLOCK_SIZE) / BLOCK_SIZE][temp_x_pos - 1])) {
                x_vel = mx_max (0, x_vel);
            } // чекаем верхний тайл
            if (check_collision(lv2[temp_y_pos + 1][mx_round(x_pos / BLOCK_SIZE)])) {
                y_vel = mx_min(0, y_vel);
            } // чекаем нижний тайл
            if (check_collision(lv2[temp_y_pos - 1][mx_round(x_pos / BLOCK_SIZE)]) || lv2[temp_y_pos + 1][mx_round(x_pos / BLOCK_SIZE)] == '=') {
                y_vel = mx_max (0, y_vel);
            }
            if (lv2[temp_y_pos + 1][mx_round(x_pos / BLOCK_SIZE)] == '9' || lv2[temp_y_pos + 1][mx_round(x_pos / BLOCK_SIZE)] == '0'
                || lv2[temp_y_pos + 1][mx_round(x_pos / BLOCK_SIZE)] == 'E' || lv2[temp_y_pos + 1][mx_round(x_pos / BLOCK_SIZE)] == 'e') {
                    SDL_RenderCopy(rend, tex_finish, NULL, &lostdest);
                    SDL_RenderPresent(rend);
                    SDL_Delay(10000);
                    return 0;
            }
            if (lv2[temp_y_pos + 1][mx_round(x_pos / BLOCK_SIZE)] == '=') y_vel -= 400;
            if (lv2[temp_y_pos + 1][mx_round(x_pos / BLOCK_SIZE)] == '^') {
                SDL_RenderCopy(rend, tex_lost, NULL, &lostdest);
                SDL_RenderPresent(rend);
                bool close_request = false;
                while (!close_request) {      
                    while (SDL_PollEvent(&event)) {
                        switch (event.type) {
                            case SDL_QUIT:
                                close_requested = 1;
                                break;
                            case SDL_KEYUP:
                                switch (event.key.keysym.scancode) {
                                    case SDL_SCANCODE_SPACE:
                                        close_request = true;   
                                }
                                break;
                        }
                    }
                }
                //stat val
                close_request = false;
                hero_dest.x = 8 * BLOCK_SIZE;
                hero_dest.y = 3 * BLOCK_SIZE;
                x_pos = 0;
                y_pos = WINDOW_HEIGHT;
                x_vel = 0;
                y_vel = 0;
                left = 0;
                right = 0;
                continue;
            }
        }

        // update positions
        x_pos = hero_dest.x + x_vel / FPS;
        y_pos = hero_dest.y + y_vel / FPS;
        
        //if (!collision) {
            hero_dest.y = (int) y_pos;
            hero_dest.x = (int) x_pos;
        //}

        // update frames
        if (!ability) {
            if (left_frames) tex = array_left[temp_frame];
            else if (right_frames) tex = array_right[temp_frame];
            else if (static_frames) tex = tex_static;
        }
        else {
            if (left_frames) tex = scroll_left[temp_frame];
            else if (right_frames) tex = scroll_right[temp_frame];
            else if (static_frames) tex = hiding[4];
        }

        // clear prev & draw new image to the window
        SDL_RenderClear(rend);

        if (level == 1) {
            SDL_RenderCopy(rend, background, NULL, &BGdest);
            SDL_RenderCopy(rend, tex_water[water_frame], NULL, &water_dest1);
            SDL_RenderCopy(rend, tex_water[water_frame], NULL, &water_dest2);
            SDL_RenderCopy(rend, tex_water[water_frame++], NULL, &water_dest3);

            SDL_RenderCopy(rend, tex_platform1, NULL, &platform1_dest);
            temp_platform1.x = platform1_dest.x + BLOCK_SIZE;
            temp_platform1.y = platform1_dest.y;
            SDL_RenderCopy(rend, tex_platform3, NULL, &temp_platform1);

            SDL_RenderCopy(rend, tex_platform1, NULL, &platform2_dest);
            temp_platform2.x = platform2_dest.x + BLOCK_SIZE;
            temp_platform2.y = platform2_dest.y;
            SDL_RenderCopy(rend, tex_platform3, NULL, &temp_platform2);

            temp_platform2.x = BLOCK_SIZE * 35;
            temp_platform2.y = BLOCK_SIZE * 5;
            SDL_RenderCopy(rend, tex_platform2, NULL, &temp_platform2);
            temp_platform2.x = BLOCK_SIZE * 36;
            temp_platform2.y = BLOCK_SIZE * 5;
            SDL_RenderCopy(rend, tex_platform3, NULL, &temp_platform2);
            
            if (mummy1_is_attack) {
                if (mummy1_left) {
                    SDL_RenderCopy(rend, tex_mummy_left_attack_frames[mummy1_frame++], NULL, &mummy_dest1);
                    if (mummy1_frame == 3 && check_mummy(x_pos, (int)(y_pos + 1.9 * BLOCK_SIZE) / BLOCK_SIZE, mummy_dest1.x + BLOCK_SIZE * 0.5, (mummy_dest1.y) / BLOCK_SIZE))
                    {
                        SDL_RenderCopy(rend, tex_lost, NULL, &lostdest);
                        SDL_RenderPresent(rend);
                        bool close_request = false;
                        while (!close_request) {      
                            while (SDL_PollEvent(&event)) {
                                switch (event.type) {
                                    case SDL_QUIT:
                                        close_requested = 1;
                                        break;
                                    case SDL_KEYUP:
                                        switch (event.key.keysym.scancode) {
                                            case SDL_SCANCODE_SPACE:
                                                close_request = true;   
                                        }
                                        break;
                                }
                            }
                        }
                        //stat val
                        close_request = false;
                        hero_dest.x = 20;
                        hero_dest.y = 540;
                        x_pos = 0;
                        y_pos = WINDOW_HEIGHT;
                        x_vel = 0;
                        y_vel = 0;
                        left = 0;
                        right = 0;
                        SDL_RenderClear(rend);
                        SDL_RenderCopy(rend, background, NULL, &menu_dest);
                        SDL_RenderCopy(rend, tex_instructions, NULL, &menu_dest);
                        SDL_RenderPresent(rend);
                        SDL_Delay(5000);
                        continue;
                    }
                    if (mummy1_frame == 4)
                        mummy1_is_attack = false;
                }
                else if (mummy1_right) {
                    SDL_RenderCopy(rend, tex_mummy_right_attack_frames[mummy1_frame++], NULL, &mummy_dest1);
                    if (mummy1_frame == 3 && check_mummy(x_pos, (int)(y_pos + 1.9 * BLOCK_SIZE) / BLOCK_SIZE, mummy_dest1.x + BLOCK_SIZE * 1.5, (mummy_dest1.y) / BLOCK_SIZE)) {
                    SDL_RenderCopy(rend, tex_lost, NULL, &lostdest);
                        SDL_RenderPresent(rend);
                        bool close_request = false;
                        while (!close_request) {      
                            while (SDL_PollEvent(&event)) {
                                switch (event.type) {
                                    case SDL_QUIT:
                                        close_requested = 1;
                                        break;
                                    case SDL_KEYUP:
                                        switch (event.key.keysym.scancode) {
                                            case SDL_SCANCODE_SPACE:
                                                close_request = true;   
                                        }
                                        break;
                                }
                            }
                        }
                        //stat val
                        close_request = false;
                        hero_dest.x = 20;
                        hero_dest.y = 540;
                        x_pos = 0;
                        y_pos = WINDOW_HEIGHT;
                        x_vel = 0;
                        y_vel = 0;
                        left = 0;
                        right = 0;
                        SDL_RenderClear(rend);
                        SDL_RenderCopy(rend, background, NULL, &menu_dest);
                        SDL_RenderCopy(rend, tex_instructions, NULL, &menu_dest);
                        SDL_RenderPresent(rend);
                        SDL_Delay(5000);
                        continue;
                    }    // character dead
                    if (mummy1_frame == 4)
                        mummy1_is_attack = false;
                }
            }
            else if (mummy1_left) {
                mummy_dest1.x -= 2;
                SDL_RenderCopy(rend, tex_mummy_left_frames[mummy1_frame++], NULL, &mummy_dest1);
                if (mummy_dest1.x < mummy1_min) {
                    mummy1_left = false;
                    mummy1_right = true;
                }
            }
            else if (mummy1_right) {
                mummy_dest1.x += 2;
                SDL_RenderCopy(rend, tex_mummy_right_frames[mummy1_frame++], NULL, &mummy_dest1);
                if (mummy_dest1.x > mummy1_max) {
                    mummy1_left = true;
                    mummy1_right = false;
                }
            }
            if (mummy2_is_attack) {
                if (mummy2_left) {
                    SDL_RenderCopy(rend, tex_mummy_left_attack_frames[mummy2_frame++], NULL, &mummy_dest2);
                    if (mummy2_frame == 3 && check_mummy(x_pos, (int)(y_pos + 1.9 * BLOCK_SIZE) / BLOCK_SIZE, mummy_dest2.x + BLOCK_SIZE * 0.5, (mummy_dest2.y) / BLOCK_SIZE)) {
                    SDL_RenderCopy(rend, tex_lost, NULL, &lostdest);
                        SDL_RenderPresent(rend);
                        bool close_request = false;
                        while (!close_request) {      
                            while (SDL_PollEvent(&event)) {
                                switch (event.type) {
                                    case SDL_QUIT:
                                        close_requested = 1;
                                        break;
                                    case SDL_KEYUP:
                                        switch (event.key.keysym.scancode) {
                                            case SDL_SCANCODE_SPACE:
                                                close_request = true;   
                                        }
                                        break;
                                }
                            }
                        }
                        //stat val
                        close_request = false;
                        hero_dest.x = 20;
                        hero_dest.y = 540;
                        x_pos = 0;
                        y_pos = WINDOW_HEIGHT;
                        x_vel = 0;
                        y_vel = 0;
                        left = 0;
                        right = 0;
                        SDL_RenderClear(rend);
                        SDL_RenderCopy(rend, background, NULL, &menu_dest);
                        SDL_RenderCopy(rend, tex_instructions, NULL, &menu_dest);
                        SDL_RenderPresent(rend);
                        SDL_Delay(5000);
                        continue;
                    }
                    if (mummy2_frame == 4)
                        mummy2_is_attack = false;
                }
                else if (mummy2_right) {
                    SDL_RenderCopy(rend, tex_mummy_right_attack_frames[mummy2_frame++], NULL, &mummy_dest2);
                    if (mummy2_frame == 3 && check_mummy(x_pos, (int)(y_pos + 1.9 * BLOCK_SIZE) / BLOCK_SIZE, mummy_dest2.x + BLOCK_SIZE * 1.5, (mummy_dest2.y) / BLOCK_SIZE)) {
                    SDL_RenderCopy(rend, tex_lost, NULL, &lostdest);
                        SDL_RenderPresent(rend);
                        bool close_request = false;
                        while (!close_request) {      
                            while (SDL_PollEvent(&event)) {
                                switch (event.type) {
                                    case SDL_QUIT:
                                        close_requested = 1;
                                        break;
                                    case SDL_KEYUP:
                                        switch (event.key.keysym.scancode) {
                                            case SDL_SCANCODE_SPACE:
                                                close_request = true;   
                                        }
                                        break;
                                }
                            }
                        }
                        //stat val
                        close_request = false;
                        hero_dest.x = 20;
                        hero_dest.y = 540;
                        x_pos = 0;
                        y_pos = WINDOW_HEIGHT;
                        x_vel = 0;
                        left = 0;
                        right = 0;
                        y_vel = 0;
                        SDL_RenderClear(rend);
                        SDL_RenderCopy(rend, background, NULL, &menu_dest);
                        SDL_RenderCopy(rend, tex_instructions, NULL, &menu_dest);
                        SDL_RenderPresent(rend);
                        SDL_Delay(5000);
                        continue;
                    }
                        // character dead
                    if (mummy2_frame == 4)
                        mummy2_is_attack = false;
                }
            }
            else if (mummy2_left) {
                mummy_dest2.x -= 2;
                SDL_RenderCopy(rend, tex_mummy_left_frames[mummy2_frame++], NULL, &mummy_dest2);
                if (mummy_dest2.x < mummy2_min) {
                    mummy2_left = false;
                    mummy2_right = true;
                }
            }
            else if (mummy2_right) {
                mummy_dest2.x += 2;
                SDL_RenderCopy(rend, tex_mummy_right_frames[mummy2_frame++], NULL, &mummy_dest2);
                if (mummy_dest2.x > mummy2_max) {
                    mummy2_left = true;
                    mummy2_right = false;
                }
            }
            if (mummy3_is_attack) {
                if (mummy3_left) {
                    SDL_RenderCopy(rend, tex_mummy_left_attack_frames[mummy3_frame++], NULL, &mummy_dest3);
                    if (mummy3_frame == 3 && check_mummy(x_pos, (int)(y_pos + 1.9 * BLOCK_SIZE) / BLOCK_SIZE, mummy_dest3.x + BLOCK_SIZE * 0.5, (mummy_dest3.y) / BLOCK_SIZE)) {
                    SDL_RenderCopy(rend, tex_lost, NULL, &lostdest);
                        SDL_RenderPresent(rend);
                        bool close_request = false;
                        while (!close_request) {      
                            while (SDL_PollEvent(&event)) {
                                switch (event.type) {
                                    case SDL_QUIT:
                                        close_requested = 1;
                                        break;
                                    case SDL_KEYUP:
                                        switch (event.key.keysym.scancode) {
                                            case SDL_SCANCODE_SPACE:
                                                close_request = true;   
                                        }
                                        break;
                                }
                            }
                        }
                        //stat val
                        close_request = false;
                        hero_dest.x = 20;
                        hero_dest.y = 540;
                        x_pos = 0;
                        y_pos = WINDOW_HEIGHT;
                        x_vel = 0;
                        y_vel = 0;
                        left = 0;
                        right = 0;
                        SDL_RenderClear(rend);
                        SDL_RenderCopy(rend, background, NULL, &menu_dest);
                        SDL_RenderCopy(rend, tex_instructions, NULL, &menu_dest);
                        SDL_RenderPresent(rend);
                        SDL_Delay(5000);
                        continue;
                    }
                    // character dead
                    if (mummy3_frame == 4)
                        mummy3_is_attack = false;
                }
                else if (mummy3_right) {
                    SDL_RenderCopy(rend, tex_mummy_right_attack_frames[mummy3_frame++], NULL, &mummy_dest3);
                    if (mummy3_frame == 3 && check_mummy(x_pos, (int)(y_pos + 1.9 * BLOCK_SIZE) / BLOCK_SIZE, mummy_dest3.x + BLOCK_SIZE * 1.5, (mummy_dest3.y) / BLOCK_SIZE)) {
                    SDL_RenderCopy(rend, tex_lost, NULL, &lostdest);
                        SDL_RenderPresent(rend);
                        bool close_request = false;
                        while (!close_request) {      
                            while (SDL_PollEvent(&event)) {
                                switch (event.type) {
                                    case SDL_QUIT:
                                        close_requested = 1;
                                        break;
                                    case SDL_KEYUP:
                                        switch (event.key.keysym.scancode) {
                                            case SDL_SCANCODE_SPACE:
                                                close_request = true;   
                                        }
                                        break;
                                }
                            }
                        }
                        //stat val
                        close_request = false;
                        hero_dest.x = 20;
                        hero_dest.y = 540;
                        x_pos = 0;
                        y_pos = WINDOW_HEIGHT;
                        x_vel = 0;
                        y_vel = 0;
                        left = 0;
                        right = 0;
                        SDL_RenderClear(rend);
                        SDL_RenderCopy(rend, background, NULL, &menu_dest);
                        SDL_RenderCopy(rend, tex_instructions, NULL, &menu_dest);
                        SDL_RenderPresent(rend);
                        SDL_Delay(5000);
                        continue;
                    }
                    if (mummy3_frame == 4)
                        mummy3_is_attack = false;
                }
            }
            else if (mummy3_left) {
                mummy_dest3.x -= 2;
                SDL_RenderCopy(rend, tex_mummy_left_frames[mummy3_frame++], NULL, &mummy_dest3);
                if (mummy_dest3.x < mummy3_min) {
                    mummy3_left = false;
                    mummy3_right = true;
                }
            }
            else if (mummy3_right) {
                mummy_dest3.x += 2;
                SDL_RenderCopy(rend, tex_mummy_right_frames[mummy3_frame++], NULL, &mummy_dest3);
                if (mummy_dest3.x > mummy3_max) {
                    mummy3_left = true;
                    mummy3_right = false;
                }
            }

            if (mummy1_frame == 5) mummy1_frame = 0; // change 1 for animation max 5 or segmentation will met you with hugs
            if (mummy2_frame == 5) mummy2_frame = 0;
            if (mummy3_frame == 5) mummy3_frame = 0;
        }
        else if (level == 2) {
            SDL_RenderCopy(rend, tex_background_02, NULL, &BGdest);
            SDL_RenderCopy(rend, tex_water[water_frame], NULL, &water_dest1);
            SDL_RenderCopy(rend, tex_water[water_frame], NULL, &water_dest2);
            SDL_RenderCopy(rend, tex_water[water_frame], NULL, &water_dest3);
            SDL_RenderCopy(rend, tex_water[water_frame], NULL, &water_dest4);
            SDL_RenderCopy(rend, tex_water[water_frame], NULL, &water_dest5);
            SDL_RenderCopy(rend, tex_water[water_frame], NULL, &water_dest6);
            SDL_RenderCopy(rend, tex_water[water_frame], NULL, &water_dest7);
            SDL_RenderCopy(rend, tex_water[water_frame], NULL, &water_dest8);
            SDL_RenderCopy(rend, tex_water[water_frame], NULL, &water_dest9);
            SDL_RenderCopy(rend, tex_water[water_frame++], NULL, &water_dest10);
        }
        
        if (left_frames || right_frames) temp_frame = (temp_frame == 2) ? 0 : temp_frame + 1;
        if (water_frame == 7) water_frame = 0;

        SDL_RenderCopy(rend, tex, NULL, &hero_dest);
        SDL_RenderPresent(rend);
        SDL_Delay(1000/FPS);
    }
    
    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

