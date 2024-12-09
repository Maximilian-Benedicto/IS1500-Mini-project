#ifndef VECTOR_H
#define VECTOR_H

typedef struct
{
    float x, y;
} vec2;

typedef struct
{
    float x, y, z;
} vec3;

typedef struct
{
    float x, y, z, w;
} vec4;

float vec3_length(vec3 v);
vec3 vec3_add(vec3 a, vec3 b);
vec3 vec3_sub(vec3 a, vec3 b);
vec3 vec3_mul(vec3 v, float factor);
vec3 vec3_div(vec3 v, float factor);
void vec3_normalize(vec3 *v);
vec3 vec3_dot(vec3 a, vec3 b);

vec3 vec4_to_vec3(vec4 v);

float vec4_length(vec4 v);
vec4 vec4_add(vec4 a, vec4 b);
vec4 vec4_sub(vec4 a, vec4 b);
vec4 vec4_mul(vec4 v, float factor);
vec4 vec4_div(vec4 v, float factor);
void vec4_normalize(vec4 *v);

// Vector 2D functions
float vec2_length(vec2 v);
vec2 vec2_add(vec2 a, vec2 b);
vec2 vec2_sub(vec2 a, vec2 b);
vec2 vec2_mul(vec2 v, float factor);
vec2 vec2_div(vec2 v, float factor);
void vec2_normalize(vec2 *v);

#endif