#ifndef donut_H
#define donut_H

#include "utils.h"
#include "camera.h"
#include "map.h"
#include "icecream.h"
#include "scene.h"
#include "flag.h"
#include <stdbool.h>
#include <model.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/*
# minden olyan elem ami szerepelhet benne kupa/zászló , icecream stb
PUSH POP egyszerre hajtja végre a dolgokat benne
*/
typedef struct donut
{
    GLuint donut_texture_id; 
    Model model;
    float radius;
    float moving_speed;
    float rotation_speed;
    float gravity;
    float upward_speed;
    float bouncing;
    bool in_the_air;
    double uptime;
    vec3 position;
    vec3 rotation;
    Material donut_material;
    bool is_win_visible;
    bool is_lose_visible;


} donut;


//inincializálása
void init_donut(donut* donut);

//megrajzolása
void draw_donut(donut* donut);

//mozgatása
void setting_donut_moving_speed(donut* donut, float speed);

//forgatása
void setting_donut_rotation(donut* donut, float angle); 

//pattogása
void setting_upward_speed(donut* donut, float jumping_power);

//elyzetének visszaállítás
void reset_donut(donut* donut);

//helyzetének frissítése
void update_donut(donut* donut, Map* map, icecream* icecream, flag* flag);  

void show_lose();

void show_win();

/* donut_H*/
#endif 