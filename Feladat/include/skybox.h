#ifndef SKYBOX_H
#define SKYBOX_H

#include <utils.h>
#include <camera.h>
#include "texture.h"
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <model.h>

typedef struct Skybox
{
    GLuint skybox_top;
    GLuint skybox_bottom;
    GLuint skybox_left;
    GLuint skybox_right;
    GLuint skybox_back;
    GLuint skybox_front;
    
}Skybox;




void init_skybox(Skybox* skybox);

void draw_skybox(Skybox* skybox);

void kill_skybox(); 



#endif
