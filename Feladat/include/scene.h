#ifndef SCENE_H
#define SCENE_H


#include "camera.h"
#include "texture.h"
#include "map.h"
#include "icecream.h"
#include "donut.h"
#include "skybox.h"
#include "flag.h"
#include "rain.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>



typedef struct Scene
{
    Map map;
    donut donut;
    Skybox skybox;
    Material material;
    flag flag;
    icecream icecream1;
    icecream icecream2;
    icecream icecream3;
    CandyRain rain;
    GLuint guide_id;
    GLuint lose_id; 
    GLuint win_id;
    float lighting_changer;
    float fog_density;
   //bool is_lose_visible;
    //bool is_win_visible;

    //GLuint donut_texture_id; 

}Scene;


/*To measure the light changing*/


/*Initialize the scene by loading models*/
void init_scene(Scene* scene);


/*Change the lighting of the scene*/
void set_lighting(float light);


/*Set the lighting of the scene*/
//void set_lighting_changer(float light);


/*Set the current material*/
void set_material(Material* material); //const Material


/*Draw the scene objects*/
void draw_scene(Scene* scene); //const Scene


void update_scene(Scene* scene);
void reset_scene(Scene* scene);


/*Reset the brightness of the screen*/
void reset_lights();

//void reset_fog();


/*Draw the origin of the world coordinate system*/
void draw_origin();




#endif