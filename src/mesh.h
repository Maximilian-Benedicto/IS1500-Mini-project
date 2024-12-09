#ifndef MESH_H
#define MESH_H

#include "vector.h"
#include "config.h"

typedef struct
{
    int v1;
    int v2;
    int v3;

    float z; // Average depth value of the vertices

    vec4 color; // RGBA color from 0.0f to 1.0f
} triangle;

typedef struct
{
    int num_vertices;
    int num_triangles;

    vec3 vertices[MAX_VERTICES];
    triangle triangles[MAX_TRIANGLES];

} mesh3;

typedef struct
{
    int num_vertices;
    int num_triangles;

    vec4 vertices[MAX_VERTICES];
    triangle triangles[MAX_TRIANGLES];

} mesh4;

mesh3 create_mesh3(int num_vertices, int num_triangles);
mesh3 mesh4_perspective_mesh3(mesh4 mesh);


mesh4 create_mesh4(int num_vertices, int num_triangles);
mesh4 merge_mesh4(mesh4 m1, mesh4 m2);
void rotate_x_mesh4(mesh4 *mesh, float angle, vec4 center_point);
void rotate_y_mesh4(mesh4 *mesh, float angle, vec4 center_point);
void rotate_z_mesh4(mesh4 *mesh, float angle, vec4 center_point);
void translate_x_mesh4(mesh4 *mesh, float x);
void translate_y_mesh4(mesh4 *mesh, float y);
void translate_z_mesh4(mesh4 *mesh, float z);

#endif
