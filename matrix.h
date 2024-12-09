#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"

typedef struct
{
    float m[2][2];
} matrix2;

typedef struct
{
    float m[3][3];
} matrix3;

typedef struct
{
    float m[4][4];
} matrix4;

matrix4 rotation_x_matrix4(float a);
matrix4 rotation_y_matrix4(float a);
matrix4 rotation_z_matrix4(float a);

matrix4 translation_x_matrix4(float x);
matrix4 translation_y_matrix4(float y);
matrix4 translation_z_matrix4(float z);

vec2 mat2_mul_vec2(matrix2 m, vec2 v);
vec3 mat3_mul_vec3(matrix3 m, vec3 v);
vec4 mat4_mul_vec4(matrix4 m, vec4 v);

matrix4 perspective_matrix();

#endif
