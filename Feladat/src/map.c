#include "scene.h"
#include "utils.h"
#include "map.h"

#include <SDL2/SDL.h>
#include <load.h>
#include <draw.h>

void init_map(Map* map)
{
    load_model(&(map->model), "assets/models/cube.obj");
    map->map_texture_id = load_texture("assets/textures/cube.png");

    map->position.x = 0.0f;
    map->position.y = 0.0f;
    map->position.z = -0.9f;

    map->map_material.ambient.red = 0.95f;
    map->map_material.ambient.green = 0.35f;
    map->map_material.ambient.blue = 0.85f;

    map->map_material.diffuse.red = 0.95f;
    map->map_material.diffuse.green = 0.35f;
    map->map_material.diffuse.blue = 0.85f;

    map->map_material.specular.red = 0.3f;
    map->map_material.specular.green = 0.3f;
    map->map_material.specular.blue = 0.3f;

    map->map_material.shininess = 20.0f;
}

void draw_map(Map* map)
{
    int i;

    glBindTexture(GL_TEXTURE_2D, map->map_texture_id);
    set_material(&(map->map_material));

    glColor3f(1.0f, 0.55f, 0.95f);

    glPushMatrix();

    glTranslatef(map->position.x, map->position.y, map->position.z);

    for (i = 0; i < 12; i++) {
        glPushMatrix();
        glTranslatef(0.0f, -i, 0.0f);
        glScalef(1.0f, 1.0f, 0.25f);
        draw_model(&(map->model));
        glPopMatrix();
    }

    glPopMatrix();

    glColor3f(1.0f, 1.0f, 1.0f);
}