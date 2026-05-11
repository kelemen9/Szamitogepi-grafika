#include "texture.h"

#include <stdio.h>

GLuint load_texture(char* filename)
{
    SDL_Surface* loaded_surface;
    SDL_Surface* formatted_surface;
    GLuint texture_name;

    loaded_surface = IMG_Load(filename);

    if (loaded_surface == NULL) {
        printf("[ERROR] Cannot load texture: %s\n", filename);
        printf("[ERROR] IMG_Load: %s\n", IMG_GetError());
        return 0;
    }

    formatted_surface = SDL_ConvertSurfaceFormat(loaded_surface, SDL_PIXELFORMAT_RGBA32, 0);
    SDL_FreeSurface(loaded_surface);

    if (formatted_surface == NULL) {
        printf("[ERROR] Cannot convert texture: %s\n", filename);
        printf("[ERROR] SDL_ConvertSurfaceFormat: %s\n", SDL_GetError());
        return 0;
    }

    glGenTextures(1, &texture_name);
    glBindTexture(GL_TEXTURE_2D, texture_name);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA,
        formatted_surface->w,
        formatted_surface->h,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        formatted_surface->pixels
    );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    SDL_FreeSurface(formatted_surface);

    return texture_name;
}
