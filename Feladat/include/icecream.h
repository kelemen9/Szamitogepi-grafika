#ifndef ICECREAM_H
#define ICECREAM_H

#include "utils.h"
#include <GL/gl.h>

typedef struct icecream
{
    vec3 position;
    GLuint cone_texture;
    GLuint scoop_texture;
} icecream;

void init_icecream(icecream* icecream, float y, float z);
void draw_icecream(icecream* icecream);

#endif