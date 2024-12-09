/**
 * Vector math in 2D, 3D and 4D
 * @authors Maximilian Benedict, Arman Montazeri
 */

#include "vector.h"
#include "math.h"
#include "config.h"

float vec2_length(vec2 v)
{
    return sqrtf(v.x * v.x + v.y * v.y);
}
vec2 vec2_add(vec2 a, vec2 b)
{
    vec2 result = {a.x + b.x, a.y + b.y};
    return result;
}
vec2 vec2_sub(vec2 a, vec2 b)
{
    vec2 result = {a.x - b.x, a.y - b.y};
    return result;
}
vec2 vec2_mul(vec2 v, float factor)
{
    vec2 result = {v.x * factor, v.y * factor};
    return result;
}

vec2 vec2_div(vec2 v, float factor)
{
    vec2 result = {v.x / factor, v.y / factor};
    return result;
}
void vec2_normalize(vec2 *v)
{
    float length = vec2_length(*v);
    if (length != 0)
    {
        *v = vec2_div(*v, length);
    }
}

float vec3_length(vec3 v)
{
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}
vec3 vec3_add(vec3 a, vec3 b)
{
    vec3 result = {a.x + b.x, a.y + b.y, a.z + b.z};
    return result;
}

vec3 vec3_sub(vec3 a, vec3 b)
{
    vec3 result = {a.x - b.x, a.y - b.y, a.z - b.z};
    return result;
}

vec3 vec3_mul(vec3 v, float factor)
{
    vec3 result = {v.x * factor, v.y * factor, v.z * factor};
    return result;
}

vec3 vec3_div(vec3 v, float factor)
{
    vec3 result = {v.x / factor, v.y / factor, v.z / factor};
    return result;
}

void vec3_normalize(vec3 *v)
{
    float length = vec3_length(*v);
    if (length != 0)
    {
        *v = vec3_div(*v, length);
    }
}
vec3 vec3_dot(vec3 a, vec3 b)
{
    vec3 result = {(a.y * b.z) - (a.z * b.y), (a.z * b.x) - (a.x * b.z), (a.x * b.y) - (a.y * b.x)};
    return result;
}

vec3 vec4_to_vec3(vec4 v)
{
    vec3 result;

    // Perform the perspective divide for X and Y (x/w, y/w)
    float ndc_x = v.x / v.w;
    float ndc_y = v.y / v.w;

    // Do not perform the perspective divide for Z, since it's already transformed
    float ndc_z = v.z / v.w; // Keep Z as it is for depth precision

    // Map NDC (-1, 1) to screen space (0, WIDTH) and (0, HEIGHT)
    result.x = ((ndc_x + 1) / 2.0f) * (WIDTH);     // X maps from [-1,1] to [0, WIDTH]
    result.y = ((1.0f - ndc_y) / 2.0f) * (HEIGHT); // Y maps from [-1,1] to [0, HEIGHT] (flip Y)

    // Optionally, map Z to [0, 1] (if you want a depth buffer range)
    result.z = (ndc_z + 1) / 2; // Mapping NDC z from [-1, 1] to [0, 1] for depth

    return result;
}

float vec4_length(vec4 v)
{
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
}
vec4 vec4_add(vec4 a, vec4 b)
{
    vec4 result = {a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
    return result;
}
vec4 vec4_sub(vec4 a, vec4 b)
{
    vec4 result = {a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
    return result;
}
vec4 vec4_mul(vec4 v, float factor)
{
    vec4 result = {v.x * factor, v.y * factor, v.z * factor, v.w * factor};
    return result;
}
vec4 vec4_div(vec4 v, float factor)
{
    vec4 result = {v.x / factor, v.y / factor, v.z / factor, v.w / factor};
    return result;
}
void vec4_normalize(vec4 *v)
{
    float length = vec4_length(*v);
    if (length != 0)
    {
        *v = vec4_div(*v, length);
    }
}
