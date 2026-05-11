/* app.c */

#include "camera.h"
#include "scene.h"
#include "app.h"
#include "donut.h"

#include <stdlib.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>

Camera camera;
Scene scene;
struct MousePosition mouse_position;

void init_app(App* app, int width, int height)
{
    int error_code;
    int inited_loaders;

    app->is_running = false;

    error_code = SDL_Init(SDL_INIT_EVERYTHING);

    if (error_code != 0) {
        printf("[ERROR] SDL initialization error: %s\n", SDL_GetError());
        return;
    }

    app->window = SDL_CreateWindow(
        "donut game",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_OPENGL
    );

    if (app->window == NULL) {
        printf("[ERROR] Unable to create window!\n");
        return;
    }

    inited_loaders = IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    if ((inited_loaders & (IMG_INIT_PNG | IMG_INIT_JPG)) == 0) {
        printf("[ERROR] IMG init error: %s\n", IMG_GetError());
        return;
    }

    app->gl_context = SDL_GL_CreateContext(app->window);

    if (app->gl_context == NULL) {
        printf("[ERROR] OpenGL context error!\n");
        return;
    }

    init_opengl();
    reshape(width, height);

    init_camera(&(app->camera));
    init_scene(&(app->scene));

    app->uptime = (double)SDL_GetTicks() / 1000.0;

    camera = app->camera;
    scene = app->scene;

    app->is_running = true;
}

void init_opengl()
{
    glShadeModel(GL_SMOOTH);

    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0);

    glEnable(GL_TEXTURE_2D);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void reshape(GLsizei width, GLsizei height)
{
    int x, y, w, h;
    double ratio;

    ratio = (double)width / height;

    if (ratio > VIEWPORT_RATIO) {
        w = (int)((double)height * VIEWPORT_RATIO);
        h = height;
        x = (width - w) / 2;
        y = 0;
    }
    else {
        w = width;
        h = (int)((double)width / VIEWPORT_RATIO);
        x = 0;
        y = (height - h) / 2;
    }

    glViewport(x, y, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glFrustum(
        -.08,
        .08,
        -.06,
        .06,
        .1,
        1000
    );
}

void handle_app_events(App* app)
{
    SDL_Event event;

    static bool is_mouse_down = false;
    static int mouse_x = 0;
    static int mouse_y = 0;

    int x;
    int y;

    while (SDL_PollEvent(&event)) {

        switch (event.type) {

        case SDL_KEYDOWN:

            switch (event.key.keysym.scancode) {

            case SDL_SCANCODE_ESCAPE:
                app->is_running = false;
                break;

            case SDL_SCANCODE_R:
                reset_camera(&(app->camera));
                reset_scene(&(app->scene));
                break;

            /* Kamera */

            case SDL_SCANCODE_W:
                set_camera_speed(&(app->camera), 1.0);
                break;

            case SDL_SCANCODE_S:
                set_camera_speed(&(app->camera), -1.0);
                break;

            case SDL_SCANCODE_A:
                set_camera_side_speed(&(app->camera), 1.0);
                break;

            case SDL_SCANCODE_D:
                set_camera_side_speed(&(app->camera), -1.0);
                break;

            case SDL_SCANCODE_Q:
                set_camera_vertical_speed(&(app->camera), 1.0);
                break;

            case SDL_SCANCODE_E:
                set_camera_vertical_speed(&(app->camera), -1.0);
                break;

            /* Fánk */

            case SDL_SCANCODE_J:
                setting_donut_moving_speed(&(app->scene.donut), 3.0f);
                setting_donut_rotation(&(app->scene.donut), -240.0f);
                break;

            case SDL_SCANCODE_L:
                setting_donut_moving_speed(&(app->scene.donut), -3.0f);
                setting_donut_rotation(&(app->scene.donut), 240.0f);
                break;

            /* Kis ugrás */

            case SDL_SCANCODE_I:

                if (!app->scene.donut.in_the_air) {
                    app->scene.donut.upward_speed = 9.0f;
                    app->scene.donut.in_the_air = TRUE;
                }

                break;

            /* Kamera + fánk */

            case SDL_SCANCODE_LEFT:

                set_camera_speed(&(app->camera), -0.412);
                set_camera_side_speed(&(app->camera), 1.95);

                setting_donut_moving_speed(&(app->scene.donut), 3.0f);
                setting_donut_rotation(&(app->scene.donut), -240.0f);

                break;

            case SDL_SCANCODE_RIGHT:

                set_camera_speed(&(app->camera), 0.412);
                set_camera_side_speed(&(app->camera), -1.95);

                setting_donut_moving_speed(&(app->scene.donut), -3.0f);
                setting_donut_rotation(&(app->scene.donut), 240.0f);

                break;

            case SDL_SCANCODE_UP:

                if (!app->scene.donut.in_the_air) {
                    app->scene.donut.upward_speed = 9.0f;
                    app->scene.donut.in_the_air = TRUE;
                }

                break;

            /* Köd */

            case SDL_SCANCODE_T:

                app->scene.fog_density -= 0.01f;

                if (app->scene.fog_density < 0.0f) {
                    app->scene.fog_density = 0.0f;
                }

                glFogf(GL_FOG_DENSITY, app->scene.fog_density);

                break;

            case SDL_SCANCODE_Z:
            case SDL_SCANCODE_Y:

                app->scene.fog_density += 0.01f;

                glFogf(GL_FOG_DENSITY, app->scene.fog_density);

                break;

            /* Fényerő */

            case SDL_SCANCODE_KP_PLUS:
            case SDL_SCANCODE_EQUALS:

                app->scene.lighting_changer += 0.3f;

                set_lighting(app->scene.lighting_changer);

                break;

            case SDL_SCANCODE_KP_MINUS:
            case SDL_SCANCODE_MINUS:

                app->scene.lighting_changer -= 0.3f;

                if (app->scene.lighting_changer < 0.1f) {
                    app->scene.lighting_changer = 0.1f;
                }

                set_lighting(app->scene.lighting_changer);

                break;

            case SDL_SCANCODE_F1:

                app->camera.is_guide_visible =
                    !app->camera.is_guide_visible;

                break;

            default:
                break;
            }

            break;

        case SDL_KEYUP:

            switch (event.key.keysym.scancode) {

            case SDL_SCANCODE_W:
            case SDL_SCANCODE_S:

                set_camera_speed(&(app->camera), 0.0);

                break;

            case SDL_SCANCODE_A:
            case SDL_SCANCODE_D:

                set_camera_side_speed(&(app->camera), 0.0);

                break;

            case SDL_SCANCODE_Q:
            case SDL_SCANCODE_E:

                set_camera_vertical_speed(&(app->camera), 0.0);

                break;

            case SDL_SCANCODE_J:
            case SDL_SCANCODE_L:

                setting_donut_moving_speed(
                    &(app->scene.donut),
                    0.0f
                );

                setting_donut_rotation(
                    &(app->scene.donut),
                    0.0f
                );

                break;

            case SDL_SCANCODE_LEFT:
            case SDL_SCANCODE_RIGHT:

                set_camera_speed(&(app->camera), 0.0);
                set_camera_side_speed(&(app->camera), 0.0);

                setting_donut_moving_speed(
                    &(app->scene.donut),
                    0.0f
                );

                setting_donut_rotation(
                    &(app->scene.donut),
                    0.0f
                );

                break;

            default:
                break;
            }

            break;

        case SDL_MOUSEBUTTONDOWN:

            is_mouse_down = true;

            break;

        case SDL_MOUSEMOTION:

            SDL_GetMouseState(&x, &y);

            if (is_mouse_down) {
                rotate_camera(
                    &(app->camera),
                    mouse_x - x,
                    mouse_y - y
                );
            }

            mouse_x = x;
            mouse_y = y;

            break;

        case SDL_MOUSEBUTTONUP:

            is_mouse_down = false;

            break;

        case SDL_QUIT:

            app->is_running = false;

            break;

        default:
            break;
        }
    }
}

void update_app(App* app)
{
    double current_time;
    double elapsed_time;

    current_time = (double)SDL_GetTicks() / 1000.0;

    elapsed_time = current_time - app->uptime;

    app->uptime = current_time;

    update_camera(&(app->camera), elapsed_time);

    update_scene(&(app->scene));

    camera = app->camera;
    scene = app->scene;
}

void render_app(App* app)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();

    set_view(&(app->camera));

    draw_scene(&(app->scene));

    glPopMatrix();

    if (app->camera.is_preview_visible == 1) {
        show_texture_preview();
    }

    if (app->camera.is_guide_visible == 1) {
        show_guide();
    }

    if (app->scene.donut.is_lose_visible == 1) {
        show_lose();
    }

    if (app->scene.donut.is_win_visible == 1) {
        show_win();
    }

    SDL_GL_SwapWindow(app->window);
}

void destroy_app(App* app)
{
    if (app->gl_context != NULL) {
        SDL_GL_DeleteContext(app->gl_context);
    }

    if (app->window != NULL) {
        SDL_DestroyWindow(app->window);
    }

    IMG_Quit();
    SDL_Quit();
}