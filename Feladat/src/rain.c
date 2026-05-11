#include "rain.h"

#include <GL/gl.h>
#include <stdlib.h>
#include <time.h>

void init_rain(CandyRain* rain)
{
    int i;

    srand((unsigned int)time(NULL));

    rain->texture = 0;

    for (i = 0; i < MAX_RAIN; i++) {
        rain->drops[i].x = ((float)(rand() % 520) / 100.0f) - 2.6f;
        rain->drops[i].y = ((float)(rand() % 360) / 100.0f) - 1.8f;
        rain->drops[i].z = -3.0f;

        rain->drops[i].speed = 0.008f + ((float)(rand() % 25) / 10000.0f);
        rain->drops[i].size = 0.035f + ((float)(rand() % 22) / 1000.0f);
    }
}

void update_rain(CandyRain* rain)
{
    int i;

    for (i = 0; i < MAX_RAIN; i++) {
        rain->drops[i].y -= rain->drops[i].speed;

        if (rain->drops[i].y < -1.85f) {
            rain->drops[i].x = ((float)(rand() % 520) / 100.0f) - 2.6f;
            rain->drops[i].y = 1.85f;
            rain->drops[i].speed = 0.008f + ((float)(rand() % 25) / 10000.0f);
        }
    }
}

void draw_rain(CandyRain* rain)
{
    int i;
    float s;

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_FOG);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glLineWidth(3.0f);

    for (i = 0; i < MAX_RAIN; i++) {
        s = rain->drops[i].size;

        if (i % 5 == 0) {
            glColor4f(1.0f, 0.25f, 0.75f, 0.90f);
        }
        else if (i % 5 == 1) {
            glColor4f(1.0f, 0.85f, 0.20f, 0.90f);
        }
        else if (i % 5 == 2) {
            glColor4f(0.25f, 0.85f, 1.0f, 0.90f);
        }
        else if (i % 5 == 3) {
            glColor4f(0.55f, 1.0f, 0.35f, 0.90f);
        }
        else {
            glColor4f(1.0f, 1.0f, 1.0f, 0.80f);
        }

        glPushMatrix();

        glTranslatef(rain->drops[i].x, rain->drops[i].y, -3.0f);
        glRotatef((float)(i * 37), 0.0f, 0.0f, 1.0f);

        glBegin(GL_LINES);
            glVertex3f(-s, 0.0f, 0.0f);
            glVertex3f( s, 0.0f, 0.0f);
        glEnd();

        glPopMatrix();
    }

    glLineWidth(1.0f);

    glPopMatrix();

    glDisable(GL_BLEND);

    glEnable(GL_FOG);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);

    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}