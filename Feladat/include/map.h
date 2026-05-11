#ifndef MAP_H
#define MAP_H

#include "utils.h"
#include "camera.h"
#include "texture.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <model.h>


typedef struct Map
{
 Model model;
 GLuint map_texture_id;
 vec3 position;
 Material map_material;

} Map;



void init_map(Map* map);

void draw_map(Map* map);


/*MAP_H*/


#endif
