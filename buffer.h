#ifndef BUFFER_H
#define BUFFER_H

#include "vector.h"
#include "config.h"

extern unsigned char pbuffer[WIDTH * HEIGHT * BUFFER_SIZE];
extern float zbuffer[WIDTH * HEIGHT];

void init_buffer();
void set_pbuffer(vec2 v, int r, int g, int b, int a);
void set_zbuffer(vec2 v, float z);
void clear_pbuffer();
void clear_zbuffer();
void update_VGA();

#endif