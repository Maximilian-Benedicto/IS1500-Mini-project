#include "vector.h"
#include "mesh.h"
#include "matrix.h"
#include <stdlib.h>
#include <stddef.h>


mesh3 create_mesh3(int num_vertices, int num_triangles)
{
    mesh3 result;
    result.num_vertices = num_vertices;
    result.num_triangles = num_triangles;

    return result;
}



mesh4 create_mesh4(int num_vertices, int num_triangles)
{
    mesh4 result;
    result.num_vertices = num_vertices;
    result.num_triangles = num_triangles;

    return result;
}

mesh4 merge_mesh4(mesh4 m1, mesh4 m2) {
    mesh4 result = create_mesh4(m1.num_vertices + m2.num_vertices, m1.num_triangles + m2.num_triangles);

    for (int i = 0; i < m1.num_vertices; i++)
    {
        result.vertices[i] = m1.vertices[i];
    }

    for (int i = 0; i < m2.num_vertices; i++)
    {
        result.vertices[m1.num_vertices + i] = m2.vertices[i];
    }

    for (int i = 0; i < m1.num_triangles; i++)
    {
        result.triangles[i] = m1.triangles[i];
    }

    for (int i = 0; i < m2.num_triangles; i++) {
        triangle t = m2.triangles[i];
        // Adjust vertex indices
        t.v1 += m1.num_vertices;
        t.v2 += m1.num_vertices;
        t.v3 += m1.num_vertices;
        result.triangles[m1.num_triangles + i] = t;
    }

    return result;
}

void rotate_x_mesh4(mesh4 *mesh, float angle, vec4 center_point)
{
    matrix4 r = rotation_x_matrix4(angle);
    for (int i = 0; i < mesh->num_vertices; i++)
    {
        vec4 v = mesh->vertices[i];
        vec4 p = center_point;
        vec4 v_prim = vec4_sub(v, p);
        vec4 v_bis = mat4_mul_vec4(r, v_prim);
        vec4 v_result = vec4_add(v_bis, p);
        mesh->vertices[i] = v_result;
    }
}

void rotate_y_mesh4(mesh4 *mesh, float angle, vec4 center_point)
{
    matrix4 r = rotation_y_matrix4(angle);
    for (int i = 0; i < mesh->num_vertices; i++)
    {
        vec4 v = mesh->vertices[i];
        vec4 p = center_point;
        vec4 v_prim = vec4_sub(v, p);
        vec4 v_bis = mat4_mul_vec4(r, v_prim);
        vec4 v_result = vec4_add(v_bis, p);
        mesh->vertices[i] = v_result;
    }
}

void rotate_z_mesh4(mesh4 *mesh, float angle, vec4 center_point)
{
    matrix4 r = rotation_z_matrix4(angle);
    for (int i = 0; i < mesh->num_vertices; i++)
    {
        vec4 v = mesh->vertices[i];
        vec4 p = center_point;
        vec4 v_prim = vec4_sub(v, p);
        vec4 v_bis = mat4_mul_vec4(r, v_prim);
        vec4 v_result = vec4_add(v_bis, p);
        mesh->vertices[i] = v_result;
    }
}

void translate_x_mesh4(mesh4 *mesh, float x)
{
    matrix4 t = translation_x_matrix4(x);
    for (int i = 0; i < mesh->num_vertices; i++)
    {
        vec4 v = mesh->vertices[i];
        vec4 v_result = mat4_mul_vec4(t, v);
        mesh->vertices[i] = v_result;
    }
}

void translate_y_mesh4(mesh4 *mesh, float y)
{
    matrix4 t = translation_y_matrix4(y);
    for (int i = 0; i < mesh->num_vertices; i++)
    {
        vec4 v = mesh->vertices[i];
        vec4 v_result = mat4_mul_vec4(t, v);
        mesh->vertices[i] = v_result;
    }
}

void translate_z_mesh4(mesh4 *mesh, float z)
{
    matrix4 t = translation_z_matrix4(z);
    for (int i = 0; i < mesh->num_vertices; i++)
    {
        vec4 v = mesh->vertices[i];
        vec4 v_result = mat4_mul_vec4(t, v);
        mesh->vertices[i] = v_result;
    }
}

mesh3 mesh4_perspective_mesh3(mesh4 mesh)
{
    // Create an empty mesh3 object to hold the result
    mesh3 result = create_mesh3(mesh.num_vertices, mesh.num_triangles);

    // Generate the perspective projection matrix
    matrix4 p = perspective_matrix();

    // Loop over each vertex and apply the perspective projection
    for (int i = 0; i < mesh.num_vertices; i++)
    {
        vec4 v4 = mesh.vertices[i];          // Original 4D vertex
        vec4 v4_prim = mat4_mul_vec4(p, v4); // Apply the perspective matrix

        // Convert 4D vector to 3D by performing the perspective divide (inside vec4_to_vec3)
        vec3 v3 = vec4_to_vec3(v4_prim);

        // Store the result vertex in the 3D mesh
        result.vertices[i] = v3;
    }

    // Copy the triangle data from the original mesh
    result.num_triangles = mesh.num_triangles;
    for (int i = 0; i < result.num_triangles; i++)
    {
        result.triangles[i] = mesh.triangles[i];
    }
    
    return result;
}
