/* include/flag.h */

#ifndef FLAG_H
#define FLAG_H

#include "utils.h"

typedef struct flag
{
    vec3 position;
} flag;

void init_flag(flag* flag);
void draw_flag(flag* flag);

#endif