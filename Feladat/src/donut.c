#include "scene.h"
#include "donut.h"
#include "texture.h"
#include "utils.h"
#include "camera.h"
#include "app.h"
#include "flag.h"

#include <SDL2/SDL.h>
#include <load.h>
#include <draw.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define GROUND_Z -0.25f

static void draw_visible_donut()
{
    int i, j;
    int main_segments = 48;
    int tube_segments = 16;

    float main_radius = 0.32f;
    float tube_radius = 0.13f;

    for (i = 0; i < main_segments; i++) {
        float theta1 = (float)i / main_segments * 2.0f * M_PI;
        float theta2 = (float)(i + 1) / main_segments * 2.0f * M_PI;

        glBegin(GL_QUAD_STRIP);

        for (j = 0; j <= tube_segments; j++) {
            float phi = (float)j / tube_segments * 2.0f * M_PI;

            float x1 = (main_radius + tube_radius * cos(phi)) * cos(theta1);
            float y1 = (main_radius + tube_radius * cos(phi)) * sin(theta1);
            float z1 = tube_radius * sin(phi);

            float x2 = (main_radius + tube_radius * cos(phi)) * cos(theta2);
            float y2 = (main_radius + tube_radius * cos(phi)) * sin(theta2);
            float z2 = tube_radius * sin(phi);

            glTexCoord2f((float)i / main_segments, (float)j / tube_segments);
            glVertex3f(x1, y1, z1);

            glTexCoord2f((float)(i + 1) / main_segments, (float)j / tube_segments);
            glVertex3f(x2, y2, z2);
        }

        glEnd();
    }
}

void init_donut(donut* donut)
{
    load_model(&(donut->model), "assets/models/donut.obj");
    donut->donut_texture_id = load_texture("assets/textures/donu_texture.png");

    donut->is_win_visible = FALSE;
    donut->is_lose_visible = FALSE;

    donut->radius = 0.32f;

    donut->position.x = 0.0f;
    donut->position.y = 0.0f;
    donut->position.z = GROUND_Z;

    donut->rotation.x = 0.0f;
    donut->rotation.y = 0.0f;
    donut->rotation.z = 0.0f;

    donut->moving_speed = 0.0f;
    donut->rotation_speed = 0.0f;

    donut->gravity = -18.0f;
    donut->upward_speed = 0.0f;
    donut->in_the_air = FALSE;
    donut->bouncing = 0;

    donut->donut_material.ambient.red = 1.0f;
    donut->donut_material.ambient.green = 0.75f;
    donut->donut_material.ambient.blue = 0.95f;

    donut->donut_material.diffuse.red = 1.0f;
    donut->donut_material.diffuse.green = 0.55f;
    donut->donut_material.diffuse.blue = 0.85f;

    donut->donut_material.specular.red = 0.8f;
    donut->donut_material.specular.green = 0.8f;
    donut->donut_material.specular.blue = 0.8f;

    donut->donut_material.shininess = 70.0f;
}

void draw_donut(donut* donut)
{
    glBindTexture(GL_TEXTURE_2D, donut->donut_texture_id);

    glPushMatrix();

    glTranslatef(donut->position.x, donut->position.y, donut->position.z);

    set_material(&(donut->donut_material));

    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(donut->rotation.x, 0.0f, 1.0f, 0.0f);

    draw_visible_donut();

    glPopMatrix();
}

void reset_donut(donut* donut)
{
    donut->bouncing = 0;

    donut->position.x = 0.0f;
    donut->position.y = 0.0f;
    donut->position.z = GROUND_Z;

    donut->rotation.x = 0.0f;
    donut->rotation.y = 0.0f;
    donut->rotation.z = 0.0f;

    donut->moving_speed = 0.0f;
    donut->rotation_speed = 0.0f;

    donut->upward_speed = 0.0f;
    donut->in_the_air = FALSE;

    donut->is_win_visible = FALSE;
    donut->is_lose_visible = FALSE;
}

void update_donut(donut* donut, Map* map, icecream* icecream, flag* flag)
{
    static int last_frame_time = 0;

    int current_time;
    double elapsed_time;

    float current_ground_z = GROUND_Z;

    float donut_r;
    float donut_l;

    float block_l;
    float block_r;
    float block_top;

    float icecream_l;
    float icecream_r;
    float icecream_h;

    float flag_l;
    float flag_r;

    current_time = (int)SDL_GetTicks();

    if (last_frame_time == 0) {
        last_frame_time = current_time;
    }

    elapsed_time = (double)(current_time - last_frame_time) / 1000.0;
    last_frame_time = current_time;

    if (elapsed_time > 0.1) {
        elapsed_time = 0.1;
    }

    if (donut->is_lose_visible || donut->is_win_visible) {
        donut->moving_speed = 0.0f;
        donut->rotation_speed = 0.0f;
        return;
    }

    donut->position.y += donut->moving_speed * elapsed_time;
    donut->rotation.x += donut->rotation_speed * elapsed_time;

    if (donut->position.y > 0.0f) {
        donut->position.y = 0.0f;
    }

    if (donut->position.y < -11.0f) {
        donut->position.y = -11.0f;
    }

    donut_r = donut->position.y - donut->radius;
    donut_l = donut->position.y + donut->radius;

    /*
     * KOCKA TETEJE PLATFORMKÉNT
     */

    if (donut_r <= block_l && donut_l >= block_r) {
        if (donut->position.z >= block_top - 0.35f) {
            current_ground_z = block_top;
        }
    }

    /*
     * GRAVITÁCIÓ / UGRÁS
     */
    donut->upward_speed += donut->gravity * elapsed_time;
    donut->position.z += donut->upward_speed * elapsed_time;

    /*
     * TALAJRA VAGY KOCKA TETEJÉRE ÉRKEZÉS
     */
    if (donut->position.z < current_ground_z) {
        donut->position.z = current_ground_z;
        donut->upward_speed = 0.0f;
        donut->in_the_air = FALSE;
    }

    /*
     * FAGYI ÜTKÖZÉS
     */
    icecream_l = icecream->position.y + 0.35f;
    icecream_r = icecream->position.y - 0.35f;
    icecream_h = icecream->position.z + 0.75f;

    if (donut_r <= icecream_l &&
        donut_l >= icecream_r &&
        donut->position.z < icecream_h) {

        donut->is_lose_visible = TRUE;
        donut->moving_speed = 0.0f;
        donut->rotation_speed = 0.0f;
    }

    /*
     * ZÁSZLÓ CÉL
     */
    flag_l = flag->position.y + 0.45f;
    flag_r = flag->position.y - 0.45f;

    if (donut_r <= flag_l && donut_l >= flag_r) {
        donut->is_win_visible = TRUE;
        donut->moving_speed = 0.0f;
        donut->rotation_speed = 0.0f;
    }
}

void setting_donut_moving_speed(donut* donut, float speed)
{
    if (!donut->is_lose_visible && !donut->is_win_visible) {
        donut->moving_speed = speed;
    }
}

void setting_donut_rotation(donut* donut, float speed)
{
    if (!donut->is_lose_visible && !donut->is_win_visible) {
        donut->rotation_speed = speed;
    }
}

void setting_upward_speed(donut* donut, float jumping_power)
{
    if (!donut->is_lose_visible &&
        !donut->is_win_visible &&
        !donut->in_the_air) {

        donut->upward_speed = jumping_power;
        donut->in_the_air = TRUE;
    }
}