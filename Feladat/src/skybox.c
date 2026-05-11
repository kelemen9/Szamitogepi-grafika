#include "skybox.h"
#include "texture.h"

#include <GL/gl.h>

void init_skybox(Skybox* skybox)
{
    skybox->skybox_right  = load_texture("assets/textures/candy.png");
    skybox->skybox_left   = load_texture("assets/textures/candy.png");
    skybox->skybox_top    = load_texture("assets/textures/top.png");
    skybox->skybox_bottom = load_texture("assets/textures/top.png");
    skybox->skybox_back   = load_texture("assets/textures/back.jpg");
    skybox->skybox_front  = load_texture("assets/textures/front.png");
}

void kill_skybox()
{
}

void draw_skybox(Skybox* skybox)
{
    glDisable(GL_LIGHTING);
    glDisable(GL_FOG);
    glEnable(GL_TEXTURE_2D);
    glColor3f(1.0f, 1.0f, 1.0f);

    glBindTexture(GL_TEXTURE_2D, skybox->skybox_back);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(-50.0f,  20.0f, -10.0f);
        glTexCoord2f(1, 0); glVertex3f( 50.0f,  20.0f, -10.0f);
        glTexCoord2f(1, 1); glVertex3f( 50.0f, -30.0f, -10.0f);
        glTexCoord2f(0, 1); glVertex3f(-50.0f, -30.0f, -10.0f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, skybox->skybox_left);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(-50.0f, -30.0f, -10.0f);
        glTexCoord2f(1, 0); glVertex3f(-50.0f,  20.0f, -10.0f);
        glTexCoord2f(1, 1); glVertex3f(-50.0f,  20.0f,  30.0f);
        glTexCoord2f(0, 1); glVertex3f(-50.0f, -30.0f,  30.0f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, skybox->skybox_right);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(50.0f,  20.0f, -10.0f);
        glTexCoord2f(1, 0); glVertex3f(50.0f, -30.0f, -10.0f);
        glTexCoord2f(1, 1); glVertex3f(50.0f, -30.0f,  30.0f);
        glTexCoord2f(0, 1); glVertex3f(50.0f,  20.0f,  30.0f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, skybox->skybox_top);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(-50.0f, 20.0f, -10.0f);
        glTexCoord2f(1, 0); glVertex3f(-50.0f, 20.0f,  30.0f);
        glTexCoord2f(1, 1); glVertex3f( 50.0f, 20.0f,  30.0f);
        glTexCoord2f(0, 1); glVertex3f( 50.0f, 20.0f, -10.0f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, skybox->skybox_bottom);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(-50.0f, -30.0f, -10.0f);
        glTexCoord2f(1, 0); glVertex3f( 50.0f, -30.0f, -10.0f);
        glTexCoord2f(1, 1); glVertex3f( 50.0f, -30.0f,  30.0f);
        glTexCoord2f(0, 1); glVertex3f(-50.0f, -30.0f,  30.0f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, skybox->skybox_front);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(-50.0f, -30.0f, 30.0f);
        glTexCoord2f(1, 0); glVertex3f( 50.0f, -30.0f, 30.0f);
        glTexCoord2f(1, 1); glVertex3f( 50.0f,  20.0f, 30.0f);
        glTexCoord2f(0, 1); glVertex3f(-50.0f,  20.0f, 30.0f);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    glEnable(GL_LIGHTING);
    glEnable(GL_FOG);
}