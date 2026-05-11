#include "camera.h"
#include "scene.h"

#include <GL/gl.h>
#include <math.h>
#include <load.h>

static GLuint guide_texture_id = 0;

void init_camera(Camera* camera)
{
    camera->position.x = -6.0f;
    camera->position.y = 1.0f;
    camera->position.z = 1.5f;

    camera->rotation.x = -5.0f;
    camera->rotation.y = 0.0f;
    camera->rotation.z = -10.0f;

    camera->speed.x = 0.0f;
    camera->speed.y = 0.0f;
    camera->speed.z = 0.0f;

    camera->is_preview_visible = 0;
    camera->is_guide_visible = 1;
}

void update_camera(Camera* camera, double time)
{
    double angle = degree_to_radian(camera->rotation.z);
    double side_angle = degree_to_radian(camera->rotation.z + 90.0);

    camera->position.x += cos(angle) * camera->speed.y * time;
    camera->position.y += sin(angle) * camera->speed.y * time;

    camera->position.x += cos(side_angle) * camera->speed.x * time;
    camera->position.y += sin(side_angle) * camera->speed.x * time;

    camera->position.z += camera->speed.z * time;
}

void reset_camera(Camera* camera)
{
    init_camera(camera);
}

void set_view(Camera* camera)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(-(camera->rotation.x + 90.0f), 1.0f, 0.0f, 0.0f);
    glRotatef(-(camera->rotation.z - 90.0f), 0.0f, 0.0f, 1.0f);

    glTranslatef(
        -camera->position.x,
        -camera->position.y,
        -camera->position.z
    );
}

void rotate_camera(Camera* camera, double horizontal, double vertical)
{
    camera->rotation.z += horizontal;
    camera->rotation.x += vertical;

    if (camera->rotation.z < 0.0) {
        camera->rotation.z += 360.0;
    }

    if (camera->rotation.z > 360.0) {
        camera->rotation.z -= 360.0;
    }

    if (camera->rotation.x < -45.0) {
        camera->rotation.x = -45.0;
    }

    if (camera->rotation.x > 45.0) {
        camera->rotation.x = 45.0;
    }
}

void set_camera_speed(Camera* camera, double speed)
{
    camera->speed.y = speed;
}

void set_camera_side_speed(Camera* camera, double speed)
{
    camera->speed.x = speed;
}

void set_camera_vertical_speed(Camera* camera, double speed)
{
    camera->speed.z = speed;
}

void show_texture_preview()
{
}

void show_guide()
{
    if (guide_texture_id == 0) {
        guide_texture_id = load_texture("assets/textures/gui.jpg");

        if (guide_texture_id == 0) {
            guide_texture_id = load_texture("assets/textures/guj.jpg");
        }
    }

    if (guide_texture_id == 0) {
        return;
    }

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_FOG);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_COLOR_MATERIAL);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glBindTexture(GL_TEXTURE_2D, guide_texture_id);
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