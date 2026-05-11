#ifndef RAIN_H
#define RAIN_H

#include <GL/gl.h>

#define MAX_RAIN 220

typedef struct RainDrop
{
    float x;
    float y;
    float z;
    float speed;
    float size;
} RainDrop;

typedef struct CandyRain
{
    GLuint texture;
    RainDrop drops[MAX_RAIN];
} CandyRain;

void init_rain(CandyRain* rain);
void update_rain(CandyRain* rain);
void draw_rain(CandyRain* rain);

#endif