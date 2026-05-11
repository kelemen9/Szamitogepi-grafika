#include "icecream.h"
#include "texture.h"

#include <GL/gl.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define GROUND_Z -0.82f

static void draw_textured_cone(float radius, float height)
{
    int i;
    int segments = 40;

    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0.5f, 1.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);

        for (i = 0; i <= segments; i++) {
            float a = (float)i / segments * 2.0f * M_PI;
            float u = (float)i / segments;

            glTexCoord2f(u, 0.0f);
            glVertex3f(cos(a) * radius, sin(a) * radius, height);
        }
    glEnd();
}

static void draw_textured_scoop(float radius)
{
    int i, j;
    int stacks = 18;
    int slices = 40;

    for (i = 0; i < stacks; i++) {
        float v1 = (float)i / stacks;
        float v2 = (float)(i + 1) / stacks;

        float phi1 = v1 * M_PI;
        float phi2 = v2 * M_PI;

        glBegin(GL_QUAD_STRIP);

        for (j = 0; j <= slices; j++) {
            float u = (float)j / slices;
            float theta = u * 2.0f * M_PI;

            glTexCoord2f(u, v1);
            glVertex3f(
                radius * cos(theta) * sin(phi1),
                radius * sin(theta) * sin(phi1),
                radius * cos(phi1)
            );

            glTexCoord2f(u, v2);
            glVertex3f(
                radius * cos(theta) * sin(phi2),
                radius * sin(theta) * sin(phi2),
                radius * cos(phi2)
            );
        }

        glEnd();
    }
}

void init_icecream(icecream* icecream, float y, float z)
{
    icecream->cone_texture = load_texture("assets/textures/icecream_texture (2).jpg");
    icecream->scoop_texture = load_texture("assets/textures/icecream_texture.jpg");

    icecream->position.x = 0.0f;
    icecream->position.y = -y;
    icecream->position.z = GROUND_Z;
}

void draw_icecream(icecream* icecream)
{
    glPushMatrix();

    glTranslatef(
        icecream->position.x,
        icecream->position.y,
        icecream->position.z
    );

    glEnable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);

    glBindTexture(GL_TEXTURE_2D, icecream->cone_texture);
    glColor3f(1.0f, 1.0f, 1.0f);
    draw_textured_cone(0.24f, 0.70f);

    glPushMatrix();
        glTranslatef(0.0f, 0.0f, 0.82f);

        glBindTexture(GL_TEXTURE_2D, icecream->scoop_texture);
        glColor3f(1.0f, 0.95f, 1.0f);
        draw_textured_scoop(0.36f);
    glPopMatrix();

    glColor3f(1.0f, 1.0f, 1.0f);

    glEnable(GL_LIGHTING);

    glPopMatrix();
}