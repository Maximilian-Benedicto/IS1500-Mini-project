#include "vector.h"
#include "mesh.h"
#include "matrix.h"
#include "geometry.h"
#include <stddef.h>
#include <stdlib.h>

scene create_scene() {
    scene result;

    result.num_objects = 0;

    return result;
}

void rotate_scene(scene *scene, float x, float y, float z, vec4 center_point) {
    for (int i = 0; i < scene->num_objects; i++) {
        rotate_x_mesh4(&scene->objects[i], x, center_point);
        rotate_y_mesh4(&scene->objects[i], y, center_point);
        rotate_z_mesh4(&scene->objects[i], z, center_point);
    }
}

void translate_scene(scene *scene, float x, float y, float z) {
    for (int i = 0; i < scene->num_objects; i++) {
        translate_x_mesh4(&scene->objects[i], x);
        translate_y_mesh4(&scene->objects[i], y);
        translate_z_mesh4(&scene->objects[i], z);
    }
}

// TODO: add handling of too many objects
void add_to_scene(mesh4 mesh, scene *scene) {
    scene->num_objects++;
    scene->objects[scene->num_objects - 1] = mesh;
}

mesh4 scene_to_mesh4(scene *render_scene) {
    // Initialize result as an empty mesh
    mesh4 result = create_mesh4(0, 0);

    for (int i = 0; i < render_scene->num_objects; i++) {
        // Merge current object with the result
        mesh4 temp = result; // Save current result
        result = merge_mesh4(temp, render_scene->objects[i]);
    }

    return result;
}


mesh4 create_grass_block(vec4 center_point, float radius)
{
    mesh4 result = create_mesh4(8, 12);

    float r = radius;
    float x = center_point.x;
    float y = center_point.y;
    float z = center_point.z;

    // Define 8 unique vertices for the cube
    result.vertices[0] = (vec4){x - r, y - r, z - r, 1}; // Bottom-left-back
    result.vertices[1] = (vec4){x + r, y - r, z - r, 1}; // Bottom-right-back
    result.vertices[2] = (vec4){x + r, y + r, z - r, 1}; // Top-right-back
    result.vertices[3] = (vec4){x - r, y + r, z - r, 1}; // Top-left-back

    result.vertices[4] = (vec4){x - r, y - r, z + r, 1}; // Bottom-left-front
    result.vertices[5] = (vec4){x + r, y - r, z + r, 1}; // Bottom-right-front
    result.vertices[6] = (vec4){x + r, y + r, z + r, 1}; // Top-right-front
    result.vertices[7] = (vec4){x - r, y + r, z + r, 1}; // Top-left-front

    // Define the 12 triangles for the cube (2 triangles per face)
    result.triangles[0] = (triangle){0, 1, 2, 0, {0.55f, 0.27f, 0.07f, 1.0f}};  // Back face - Brown
    result.triangles[1] = (triangle){0, 2, 3, 0, {0.45f, 0.25f, 0.06f, 1.0f}};  // Back face - Lighter Brown
    result.triangles[2] = (triangle){4, 5, 6, 0, {0.60f, 0.30f, 0.10f, 1.0f}};  // Front face - Medium Brown
    result.triangles[3] = (triangle){4, 6, 7, 0, {0.50f, 0.20f, 0.05f, 1.0f}};  // Front face - Darker Brown
    result.triangles[4] = (triangle){0, 4, 7, 0, {0.58f, 0.29f, 0.08f, 1.0f}};  // Left face - Medium Brown
    result.triangles[5] = (triangle){0, 7, 3, 0, {0.48f, 0.22f, 0.06f, 1.0f}};  // Left face - Lighter Brown
    result.triangles[6] = (triangle){1, 5, 6, 0, {0.52f, 0.26f, 0.07f, 1.0f}};  // Right face - Medium Brown
    result.triangles[7] = (triangle){1, 6, 2, 0, {0.50f, 0.24f, 0.06f, 1.0f}};  // Right face - Darker Brown
    result.triangles[8] = (triangle){3, 2, 6, 0, {0.47f, 0.23f, 0.07f, 1.0f}};  // Top face - Grass (Bright Green)
    result.triangles[9] = (triangle){3, 6, 7, 0, {0.53f, 0.26f, 0.08f, 1.0f}};  // Top face - Grass (Darker Green)
    result.triangles[10] = (triangle){0, 1, 5, 0, {0.13f, 0.55f, 0.13f, 1.0f}}; // Bottom face - Dirt (Brown)
    result.triangles[11] = (triangle){0, 5, 4, 0, {0.10f, 0.45f, 0.10f, 1.0f}}; // Bottom face - Darker Dirt

    return result;
}

mesh4 create_dirt_block(vec4 center_point, float radius)
{
    mesh4 result = create_mesh4(8, 12);

    float r = radius;
    float x = center_point.x;
    float y = center_point.y;
    float z = center_point.z;

    // Define 8 unique vertices for the cube
    result.vertices[0] = (vec4){x - r, y - r, z - r, 1}; // Bottom-left-back
    result.vertices[1] = (vec4){x + r, y - r, z - r, 1}; // Bottom-right-back
    result.vertices[2] = (vec4){x + r, y + r, z - r, 1}; // Top-right-back
    result.vertices[3] = (vec4){x - r, y + r, z - r, 1}; // Top-left-back

    result.vertices[4] = (vec4){x - r, y - r, z + r, 1}; // Bottom-left-front
    result.vertices[5] = (vec4){x + r, y - r, z + r, 1}; // Bottom-right-front
    result.vertices[6] = (vec4){x + r, y + r, z + r, 1}; // Top-right-front
    result.vertices[7] = (vec4){x - r, y + r, z + r, 1}; // Top-left-front

    // Define the 12 triangles for the cube (2 triangles per face)
    result.triangles[0] = (triangle){0, 1, 2, 0, {0.55f, 0.27f, 0.07f, 1.0f}};  // Back face - Brown
    result.triangles[1] = (triangle){0, 2, 3, 0, {0.45f, 0.25f, 0.06f, 1.0f}};  // Back face - Lighter Brown
    result.triangles[2] = (triangle){4, 5, 6, 0, {0.60f, 0.30f, 0.10f, 1.0f}};  // Front face - Medium Brown
    result.triangles[3] = (triangle){4, 6, 7, 0, {0.50f, 0.20f, 0.05f, 1.0f}};  // Front face - Darker Brown
    result.triangles[4] = (triangle){0, 4, 7, 0, {0.58f, 0.29f, 0.08f, 1.0f}};  // Left face - Medium Brown
    result.triangles[5] = (triangle){0, 7, 3, 0, {0.48f, 0.22f, 0.06f, 1.0f}};  // Left face - Lighter Brown
    result.triangles[6] = (triangle){1, 5, 6, 0, {0.52f, 0.26f, 0.07f, 1.0f}};  // Right face - Medium Brown
    result.triangles[7] = (triangle){1, 6, 2, 0, {0.50f, 0.24f, 0.06f, 1.0f}};  // Right face - Darker Brown
    result.triangles[8] = (triangle){3, 2, 6, 0, {0.53f, 0.26f, 0.08f, 1.0f}};  // Top face - Dirt (Brown)
    result.triangles[9] = (triangle){3, 6, 7, 0, {0.47f, 0.23f, 0.07f, 1.0f}};  // Top face - Darker Dirt
    result.triangles[10] = (triangle){0, 1, 5, 0, {0.53f, 0.26f, 0.08f, 1.0f}}; // Bottom face - Dirt (Brown)
    result.triangles[11] = (triangle){0, 5, 4, 0, {0.47f, 0.23f, 0.07f, 1.0f}}; // Bottom face - Darker Dirt

    return result;
}

mesh4 create_wood_block(vec4 center_point, float radius)
{
    mesh4 result = create_mesh4(8, 12);

    float r = radius;
    float x = center_point.x;
    float y = center_point.y;
    float z = center_point.z;

    // Define 8 unique vertices for the cube
    result.vertices[0] = (vec4){x - r, y - r, z - r, 1}; // Bottom-left-back
    result.vertices[1] = (vec4){x + r, y - r, z - r, 1}; // Bottom-right-back
    result.vertices[2] = (vec4){x + r, y + r, z - r, 1}; // Top-right-back
    result.vertices[3] = (vec4){x - r, y + r, z - r, 1}; // Top-left-back

    result.vertices[4] = (vec4){x - r, y - r, z + r, 1}; // Bottom-left-front
    result.vertices[5] = (vec4){x + r, y - r, z + r, 1}; // Bottom-right-front
    result.vertices[6] = (vec4){x + r, y + r, z + r, 1}; // Top-right-front
    result.vertices[7] = (vec4){x - r, y + r, z + r, 1}; // Top-left-front

    // Define the 12 triangles for the cube (2 triangles per face)
    result.triangles[0] = (triangle){0, 1, 2, 0, {0.76f, 0.51f, 0.25f, 1.0f}};  // Back face - Bright Brown
    result.triangles[1] = (triangle){0, 2, 3, 0, {0.72f, 0.49f, 0.23f, 1.0f}};  // Back face - Slightly Darker Brown
    result.triangles[2] = (triangle){4, 5, 6, 0, {0.78f, 0.52f, 0.27f, 1.0f}};  // Front face - Medium Bright Brown
    result.triangles[3] = (triangle){4, 6, 7, 0, {0.80f, 0.53f, 0.28f, 1.0f}};  // Front face - Slightly Warmer Brown
    result.triangles[4] = (triangle){0, 4, 7, 0, {0.74f, 0.50f, 0.24f, 1.0f}};  // Left face - Bright Brown
    result.triangles[5] = (triangle){0, 7, 3, 0, {0.70f, 0.48f, 0.22f, 1.0f}};  // Left face - Slightly Darker
    result.triangles[6] = (triangle){1, 5, 6, 0, {0.77f, 0.51f, 0.26f, 1.0f}};  // Right face - Medium Bright Brown
    result.triangles[7] = (triangle){1, 6, 2, 0, {0.79f, 0.54f, 0.29f, 1.0f}};  // Right face - Warmer Bright Brown
    result.triangles[8] = (triangle){3, 2, 6, 0, {0.73f, 0.49f, 0.23f, 1.0f}};  // Top face - Bright Brown
    result.triangles[9] = (triangle){3, 6, 7, 0, {0.75f, 0.50f, 0.24f, 1.0f}};  // Top face - Slightly Lighter Brown
    result.triangles[10] = (triangle){0, 1, 5, 0, {0.76f, 0.51f, 0.25f, 1.0f}}; // Bottom face - Bright Brown
    result.triangles[11] = (triangle){0, 5, 4, 0, {0.78f, 0.53f, 0.27f, 1.0f}}; // Bottom face - Medium Bright Brown

    return result;
}

mesh4 create_leaf_block(vec4 center_point, float radius)
{
    mesh4 result = create_mesh4(8, 12);

    float r = radius;
    float x = center_point.x;
    float y = center_point.y;
    float z = center_point.z;

    // Define 8 unique vertices for the cube
    result.vertices[0] = (vec4){x - r, y - r, z - r, 1}; // Bottom-left-back
    result.vertices[1] = (vec4){x + r, y - r, z - r, 1}; // Bottom-right-back
    result.vertices[2] = (vec4){x + r, y + r, z - r, 1}; // Top-right-back
    result.vertices[3] = (vec4){x - r, y + r, z - r, 1}; // Top-left-back

    result.vertices[4] = (vec4){x - r, y - r, z + r, 1}; // Bottom-left-front
    result.vertices[5] = (vec4){x + r, y - r, z + r, 1}; // Bottom-right-front
    result.vertices[6] = (vec4){x + r, y + r, z + r, 1}; // Top-right-front
    result.vertices[7] = (vec4){x - r, y + r, z + r, 1}; // Top-left-front

    // Define the 12 triangles for the cube (2 triangles per face)
    result.triangles[0] = (triangle){0, 1, 2, 0, {0.25f, 0.75f, 0.25f, 0.8f}};   // Back face - Bright Green with Medium Opacity
    result.triangles[1] = (triangle){0, 2, 3, 0, {0.22f, 0.70f, 0.22f, 0.7f}};   // Back face - Slightly Darker Green, More Transparent
    result.triangles[2] = (triangle){4, 5, 6, 0, {0.30f, 0.80f, 0.30f, 0.9f}};   // Front face - Bright Green with Less Opacity
    result.triangles[3] = (triangle){4, 6, 7, 0, {0.28f, 0.78f, 0.28f, 0.8f}};   // Front face - Slightly Darker Bright Green
    result.triangles[4] = (triangle){0, 4, 7, 0, {0.26f, 0.76f, 0.26f, 0.85f}};  // Left face - Medium Bright Green
    result.triangles[5] = (triangle){0, 7, 3, 0, {0.24f, 0.72f, 0.24f, 0.75f}};  // Left face - Slightly Transparent Green
    result.triangles[6] = (triangle){1, 5, 6, 0, {0.29f, 0.79f, 0.29f, 0.88f}};  // Right face - Medium Bright Green
    result.triangles[7] = (triangle){1, 6, 2, 0, {0.27f, 0.77f, 0.27f, 0.8f}};   // Right face - Slightly Darker Bright Green
    result.triangles[8] = (triangle){3, 2, 6, 0, {0.31f, 0.82f, 0.31f, 0.9f}};   // Top face - Brightest Green with Low Transparency
    result.triangles[9] = (triangle){3, 6, 7, 0, {0.29f, 0.79f, 0.29f, 0.85f}};  // Top face - Slightly Darker Green
    result.triangles[10] = (triangle){0, 1, 5, 0, {0.23f, 0.73f, 0.23f, 0.7f}};  // Bottom face - Transparent Dark Green
    result.triangles[11] = (triangle){0, 5, 4, 0, {0.20f, 0.70f, 0.20f, 0.65f}}; // Bottom face - Darkest Green, Most Transparent

    return result;
}
