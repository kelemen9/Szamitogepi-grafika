#include "flag.h"

#include <GL/gl.h>

#define GROUND_Z -0.82f

void init_flag(flag* flag)
{
    flag->position.x = 0.0f;
    flag->position.y = -10.8f;
    flag->position.z = GROUND_Z;
}

void draw_flag(flag* flag)
{
    glPushMatrix();

    glTranslatef(
        flag->position.x,
        flag->position.y,
        flag->position.z
    );

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);

    glColor3f(1.0f, 0.35f, 0.8f);

    glBegin(GL_QUADS);
        glVertex3f(-0.16f, -0.16f, 0.0f);
        glVertex3f( 0.16f, -0.16f, 0.0f);
        glVertex3f( 0.16f,  0.16f, 0.0f);
        glVertex3f(-0.16f,  0.16f, 0.0f);
    glEnd();

    glColor3f(1.0f, 0.9f, 0.25f);

    glBegin(GL_QUADS);
        glVertex3f(-0.035f, 0.0f, 0.0f);
        glVertex3f( 0.035f, 0.0f, 0.0f);
        glVertex3f( 0.035f, 0.0f, 1.1f);
        glVertex3f(-0.035f, 0.0f, 1.1f);
    glEnd();

    glColor3f(1.0f, 0.15f, 0.65f);

    glBegin(GL_TRIANGLES);
        glVertex3f(0.03f, 0.0f, 1.05f);
        glVertex3f(0.03f, 0.0f, 0.65f);
        glVertex3f(0.52f, 0.0f, 0.85f);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);

    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);

    glPopMatrix();
}