#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/gl.h>

#define GL_CLAMP_TO_EDGE 0x812F

typedef GLubyte Pixel[3];

/**
 * Load texture from file and returns with the texture name.
 */
GLuint load_texture(char* filename);

//GLuint load_cube_map(char*filename);


#endif /* TEXTURE_H */
