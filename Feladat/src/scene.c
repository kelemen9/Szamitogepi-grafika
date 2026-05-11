#include "scene.h"
#include "donut.h"
#include "utils.h"
#include "app.h"
#include "camera.h"
#include "icecream.h"
#include "flag.h"
#include "rain.h"

#include <stdio.h>
#include <load.h>
#include <draw.h>

static GLuint guide_texture_id = 0;
static GLuint lose_texture_id = 0;
static GLuint win_texture_id = 0;

GLuint get_guide_texture_id(void)
{
    return guide_texture_id;
}

void init_scene(Scene* scene)
{
    scene->guide_id = load_texture("assets/textures/gui.jpg");
    scene->lose_id = load_texture("assets/textures/lose.jpg");
    scene->win_id = load_texture("assets/textures/win.jpg");

    if (scene->guide_id == 0) {
        scene->guide_id = load_texture("assets/textures/guj.jpg");
    }

    guide_texture_id = scene->guide_id;
    lose_texture_id = scene->lose_id;
    win_texture_id = scene->win_id;

    scene->lighting_changer = 1.4f;
    scene->fog_density = 0.005f;

    scene->material.ambient.red = 1.0f;
    scene->material.ambient.green = 1.0f;
    scene->material.ambient.blue = 1.0f;

    scene->material.diffuse.red = 1.0f;
    scene->material.diffuse.green = 1.0f;
    scene->material.diffuse.blue = 1.0f;

    scene->material.specular.red = 0.4f;
    scene->material.specular.green = 0.4f;
    scene->material.specular.blue = 0.4f;
    scene->material.shininess = 35.0f;

    init_skybox(&(scene->skybox));
    init_map(&(scene->map));

    init_icecream(&(scene->icecream1), 1.5f, -0.25f);
    init_icecream(&(scene->icecream2), 4.5f, -0.25f);
    init_icecream(&(scene->icecream3), 7.5f, -0.25f);

    init_donut(&(scene->donut));
    init_flag(&(scene->flag));
    init_rain(&(scene->rain));

    {
        GLfloat fogColor[] = {0.78f, 0.70f, 0.85f, 1.0f};

        glEnable(GL_FOG);
        glFogi(GL_FOG_MODE, GL_EXP);
        glFogf(GL_FOG_DENSITY, scene->fog_density);
        glFogfv(GL_FOG_COLOR, fogColor);
    }
}

void set_lighting(float light)
{
    float ambient_light[] = {0.55f, 0.45f, 0.55f, 1.0f};
    float diffuse_light[] = {light, light * 0.92f, light, 1.0f};
    float specular_light[] = {light, light, light, 1.0f};
    float position[] = {-4.0f, -6.0f, 7.0f, 1.0f};

    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_material(Material* material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

static void draw_donut_shadow(donut* donut)
{
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

    glColor3f(0.03f, 0.02f, 0.04f);

    glPushMatrix();

    glTranslatef(donut->position.x, donut->position.y, -0.82f);
    glScalef(0.65f, 0.32f, 1.0f);

    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(1.0f, 0.0f, 0.0f);
        glVertex3f(0.7f, 0.7f, 0.0f);
        glVertex3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-0.7f, 0.7f, 0.0f);
        glVertex3f(-1.0f, 0.0f, 0.0f);
        glVertex3f(-0.7f, -0.7f, 0.0f);
        glVertex3f(0.0f, -1.0f, 0.0f);
        glVertex3f(0.7f, -0.7f, 0.0f);
        glVertex3f(1.0f, 0.0f, 0.0f);
    glEnd();

    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
}

static void draw_screen_fog_overlay(float density)
{
    float alpha = density * 12.0f;

    if (alpha < 0.0f) {
        alpha = 0.0f;
    }

    if (alpha > 0.28f) {
        alpha = 0.28f;
    }

    if (alpha <= 0.005f) {
        return;
    }

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_FOG);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glColor4f(0.82f, 0.76f, 0.90f, alpha);

    glBegin(GL_QUADS);
        glVertex3f(-2.6f,  1.8f, -3.0f);
        glVertex3f( 2.6f,  1.8f, -3.0f);
        glVertex3f( 2.6f, -1.8f, -3.0f);
        glVertex3f(-2.6f, -1.8f, -3.0f);
    glEnd();

    glPopMatrix();

    glDisable(GL_BLEND);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_FOG);

    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}

void draw_scene(Scene* scene)
{
    set_lighting(scene->lighting_changer);
    set_material(&(scene->material));

    glEnable(GL_FOG);
    glFogf(GL_FOG_DENSITY, scene->fog_density);

    glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glColor3f(1.0f, 1.0f, 1.0f);

    draw_skybox(&(scene->skybox));

    glColor3f(1.0f, 1.0f, 1.0f);
    glEnable(GL_LIGHTING);
    glEnable(GL_FOG);

    draw_map(&(scene->map));

    draw_icecream(&(scene->icecream1));
    draw_icecream(&(scene->icecream2));
    draw_icecream(&(scene->icecream3));

    draw_flag(&(scene->flag));

    draw_donut_shadow(&(scene->donut));
    draw_donut(&(scene->donut));

    update_donut(&(scene->donut), &(scene->map), &(scene->icecream1), &(scene->flag));
    update_donut(&(scene->donut), &(scene->map), &(scene->icecream2), &(scene->flag));
    update_donut(&(scene->donut), &(scene->map), &(scene->icecream3), &(scene->flag));

    draw_screen_fog_overlay(scene->fog_density);
    draw_rain(&(scene->rain));
}

void update_scene(Scene* scene)
{
    set_lighting(scene->lighting_changer);
    update_rain(&(scene->rain));
    glFogf(GL_FOG_DENSITY, scene->fog_density);
}

void reset_scene(Scene* scene)
{
    reset_donut(&(scene->donut));

    scene->lighting_changer = 1.4f;
    scene->fog_density = 0.005f;

    set_lighting(scene->lighting_changer);
    glFogf(GL_FOG_DENSITY, scene->fog_density);
}

void reset_lights()
{
    scene.lighting_changer = 1.4f;
}

void draw_origin()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();
}

static void draw_overlay(GLuint texture_id)
{
    if (texture_id == 0) {
        return;
    }

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_FOG);

    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_TEXTURE_2D);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glBindTexture(GL_TEXTURE_2D, texture_id);
    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.9f,  1.4f, -3.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.9f,  1.4f, -3.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.9f, -1.4f, -3.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.9f, -1.4f, -3.0f);
    glEnd();

    glDisable(GL_COLOR_MATERIAL);

    glEnable(GL_FOG);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
}

void show_lose()
{
    draw_overlay(lose_texture_id);
}

void show_win()
{
    draw_overlay(win_texture_id);
}