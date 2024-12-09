/**
 * Matrix math in 2D, 3D and 4D
 */

#include "math.h"
#include "matrix.h"
#include "vector.h"
#include "config.h"

matrix2 rotation_matrix2(float a)
{
    matrix2 result;

    result.m[0][0] = cos(a);
    result.m[0][1] = -sin(a);
    result.m[1][0] = sin(a);
    result.m[1][1] = cos(a);

    return result;
}

matrix3 rotation_matrix3(float a)
{
    matrix3 result;

    result.m[0][0] = cos(a);
    result.m[0][1] = -sin(a);
    result.m[0][2] = 0;
    result.m[1][0] = sin(a);
    result.m[1][1] = cos(a);
    result.m[1][2] = 0;
    result.m[2][0] = 0;
    result.m[2][1] = 0;
    result.m[2][2] = 1;

    return result;
}

matrix4 rotation_x_matrix4(float a)
{
    matrix4 result;
    result.m[0][0] = 1;
    result.m[0][1] = 0;
    result.m[0][2] = 0;
    result.m[0][3] = 0;
    result.m[1][0] = 0;
    result.m[1][1] = cos(a);
    result.m[1][2] = -sin(a);
    result.m[1][3] = 0;
    result.m[2][0] = 0;
    result.m[2][1] = sin(a);
    result.m[2][2] = cos(a);
    result.m[2][3] = 0;
    result.m[3][0] = 0;
    result.m[3][1] = 0;
    result.m[3][2] = 0;
    result.m[3][3] = 1;

    return result;
}

matrix4 rotation_y_matrix4(float a)
{
    matrix4 result;
    result.m[0][0] = cos(a);
    result.m[0][1] = 0;
    result.m[0][2] = sin(a);
    result.m[0][3] = 0;
    result.m[1][0] = 0;
    result.m[1][1] = 1;
    result.m[1][2] = 0;
    result.m[1][3] = 0;
    result.m[2][0] = -sin(a);
    result.m[2][1] = 0;
    result.m[2][2] = cos(a);
    result.m[2][3] = 0;
    result.m[3][0] = 0;
    result.m[3][1] = 0;
    result.m[3][2] = 0;
    result.m[3][3] = 1;

    return result;
}

matrix4 rotation_z_matrix4(float a)
{
    matrix4 result;

    result.m[0][0] = cos(a);
    result.m[0][1] = -sin(a);
    result.m[0][2] = 0;
    result.m[0][3] = 0;
    result.m[1][0] = sin(a);
    result.m[1][1] = cos(a);
    result.m[1][2] = 0;
    result.m[1][3] = 0;
    result.m[2][0] = 0;
    result.m[2][1] = 0;
    result.m[2][2] = 1;
    result.m[2][3] = 0;
    result.m[3][0] = 0;
    result.m[3][1] = 0;
    result.m[3][2] = 0;
    result.m[3][3] = 1;

    return result;
}

matrix4 translation_x_matrix4(float x)
{
    matrix4 result;
    result.m[0][0] = 1;
    result.m[0][1] = 0;
    result.m[0][2] = 0;
    result.m[0][3] = x;

    result.m[1][0] = 0;
    result.m[1][1] = 1;
    result.m[1][2] = 0;
    result.m[1][3] = 0;

    result.m[2][0] = 0;
    result.m[2][1] = 0;
    result.m[2][2] = 1;
    result.m[2][3] = 0;

    result.m[3][0] = 0;
    result.m[3][1] = 0;
    result.m[3][2] = 0;
    result.m[3][3] = 1;

    return result;
}

matrix4 translation_y_matrix4(float y)
{
    matrix4 result;
    result.m[0][0] = 1;
    result.m[0][1] = 0;
    result.m[0][2] = 0;
    result.m[0][3] = 0;

    result.m[1][0] = 0;
    result.m[1][1] = 1;
    result.m[1][2] = 0;
    result.m[1][3] = y;

    result.m[2][0] = 0;
    result.m[2][1] = 0;
    result.m[2][2] = 1;
    result.m[2][3] = 0;

    result.m[3][0] = 0;
    result.m[3][1] = 0;
    result.m[3][2] = 0;
    result.m[3][3] = 1;

    return result;
}

matrix4 translation_z_matrix4(float z)
{
    matrix4 result;
    result.m[0][0] = 1;
    result.m[0][1] = 0;
    result.m[0][2] = 0;
    result.m[0][3] = 0;

    result.m[1][0] = 0;
    result.m[1][1] = 1;
    result.m[1][2] = 0;
    result.m[1][3] = 0;

    result.m[2][0] = 0;
    result.m[2][1] = 0;
    result.m[2][2] = 1;
    result.m[2][3] = z;

    result.m[3][0] = 0;
    result.m[3][1] = 0;
    result.m[3][2] = 0;
    result.m[3][3] = 1;

    return result;
}

vec2 mat2_mul_vec2(matrix2 m, vec2 v)
{
    vec2 result = {
        m.m[0][0] * v.x + m.m[0][1] * v.y,
        m.m[1][0] * v.x + m.m[1][1] * v.y};
    return result;
}

vec3 mat3_mul_vec3(matrix3 m, vec3 v)
{
    vec3 result = {
        m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z,
        m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z,
        m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z};
    return result;
}

vec4 mat4_mul_vec4(matrix4 m, vec4 v)
{
    vec4 result;

    result.x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z + m.m[0][3] * v.w;
    result.y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z + m.m[1][3] * v.w;
    result.z = m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z + m.m[2][3] * v.w;
    result.w = m.m[3][0] * v.x + m.m[3][1] * v.y + m.m[3][2] * v.z + m.m[3][3] * v.w;

    return result;
}

matrix4 perspective_matrix()
{
    matrix4 result = {0};

    // Field of view angle is provided in degrees, so convert it to radians
    float tanHalfFov = tan(fov / 2.0f * (PI / 180.0f)); // M_PI is the value of Pi

    // Set up the perspective matrix
    result.m[0][0] = 1.0f / (aspect_ratio * tanHalfFov);
    result.m[1][1] = 1.0f / tanHalfFov;
    result.m[2][2] = -(z_far + z_near) / (z_far - z_near);
    result.m[2][3] = -(2.0f * z_far * z_near) / (z_far - z_near);
    result.m[3][2] = 1.0f;
    result.m[3][3] = 0.0f;

    return result;
}
