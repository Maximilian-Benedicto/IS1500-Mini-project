#include "vector.h"
#include "math.h"
#include "buffer.h"
#include "config.h"
#include "mesh.h"
#include <stdlib.h>
#include "draw.h"
#include "dtekv-lib.h"

int draw_r = 255;
int draw_g = 255;
int draw_b = 255;
int draw_a = 255;

/**
 * Draw a line on the pixel buffer.
 * @param v1 The first point of the line.
 * @param v2 The second point
 */
void draw_line(vec2 v1, vec2 v2)
{
    // Calculate the distance between the two points
    vec2 distance = vec2_sub(v2, v1);

    // Calculate the number of steps needed to draw the line
    int steps = fabsf(distance.x) > fabsf(distance.y) ? fabsf(distance.x) : fabsf(distance.y);

    // Calculate the step size
    vec2 step_size = vec2_div(distance, steps);

    // Start at the first point
    vec2 current_point = v1;

    // Iterate over the steps and draw each pixel
    for (int i = 0; i <= steps; i++)
    {
        set_pbuffer(current_point, draw_r, draw_g, draw_b, draw_a); // red
        current_point = vec2_add(current_point, step_size);
    }
}

// Function to compute the area of a triangle in 2d screen space given its 3D vertices (used for barycentric coordinates)
float computeArea(vec3 v1, vec3 v2, vec3 v3)
{
    return fabsf((v1.x * (v2.y - v3.y) + v2.x * (v3.y - v1.y) + v3.x * (v1.y - v2.y)) / 2.0f);
}

/**
 * Rasterize a triangle on the pixel buffer with the set color.
 * Triangles are set to be ina counter-clockwise direction and then filled.
 * @param v1 The first vertex of the triangle.
 * @param v2 The second
 * @param v3 The third
 */
void rasterize_triangle(vec3 v1, vec3 v2, vec3 v3)
{

    // Calculate the signed area of the triangle
    float area = (v2.x - v1.x) * (v3.y - v1.y) - (v2.y - v1.y) * (v3.x - v1.x);
    // If the area is negative then the triangle is oriented in a CW direction
    if (area < 0)
    {
        // Swap v2 and v3 to make the triangle CCW
        vec3 temp = v2;
        v2 = v3;
        v3 = temp;
    }

    // Calculate raw bounding box coordinates
    float rawMinX = fmin(v1.x, fmin(v2.x, v3.x));
    float rawMaxX = fmax(v1.x, fmax(v2.x, v3.x));
    float rawMinY = fmin(v1.y, fmin(v2.y, v3.y));
    float rawMaxY = fmax(v1.y, fmax(v2.y, v3.y));

    // Apply floor and ceil to ensure pixel bounds
    int minX = floor(rawMinX);
    int maxX = ceil(rawMaxX);
    int minY = floor(rawMinY);
    int maxY = ceil(rawMaxY);

    // Clamp to screen bounds (0,0 is top-left)
    minX = fmax(0, minX);
    maxX = fmin(WIDTH - 1, maxX);
    minY = fmax(0, minY);
    maxY = fmin(HEIGHT - 1, maxY);

    for (int x = minX; x <= maxX; x++)
    {
        for (int y = minY; y <= maxY; y++)
        {
            vec3 pixel = {x, y, 0};
            float areaTotal = computeArea(v1, v2, v3); // Total area of the triangle
            float area1 = computeArea(pixel, v2, v3);  // Sub-triangle area with pixel
            float area2 = computeArea(v1, pixel, v3);  // Sub-triangle area with pixel
            float area3 = computeArea(v1, v2, pixel);  // Sub-triangle area with pixel

            // Barycentric coordinates
            float lambda1 = area1 / areaTotal;
            float lambda2 = area2 / areaTotal;
            float lambda3 = area3 / areaTotal;

            // Check if pixel is within the triangle, account for floating-point imprecision
            const float epsilon = 1e-5;
            if (lambda1 >= 0 && lambda2 >= 0 && lambda3 >= 0 && fabsf(lambda1 + lambda2 + lambda3 - 1) < epsilon)
            {

                // Interpolate z-value using barycentric coordinates
                float z = lambda1 * v1.z + lambda2 * v2.z + lambda3 * v3.z;

                // Perform depth test and update buffers if the pixel is closer
                if (z > zbuffer[x + y * WIDTH])
                {
                    set_zbuffer((vec2){pixel.x, pixel.y}, z);
                    set_pbuffer((vec2){pixel.x, pixel.y}, draw_r, draw_g, draw_b, draw_a);
                }
            }
        }
    }
}

int compare_triangle_z(const void *a, const void *b)
{
    triangle ta = *(const triangle *)a;
    triangle tb = *(const triangle *)b;

    float fa = ta.z;
    float fb = tb.z;

    if (fa < fb)
        return 1;
    if (fa > fb)
        return -1;
    return 0;
}


int check_triangle_zbuffer(vec3 v1, vec3 v2, vec3 v3)
{
    return (
               v1.z < zbuffer[(int)(v1.x + v1.y * WIDTH)] &&
               v2.z < zbuffer[(int)(v2.x + v2.y * WIDTH)] &&
               v3.z < zbuffer[(int)(v3.x + v3.y * WIDTH)])
               ? 0
               : 1;
}

/**
 * Draw a mesh of triangles on the pixel buffer.
 * Mesh is drawn in ascending order based on the average depth-value of each triangle.
 * @param mesh The mesh of triangles to draw.
 */
void draw_mesh3(mesh3 mesh)
{

    // Calculate the average z-coordinate of each triangle
    for (int i = 0; i < mesh.num_triangles; i++)
    {
        triangle t = mesh.triangles[i];
        float v1 = mesh.vertices[t.v1].z;
        float v2 = mesh.vertices[t.v2].z;
        float v3 = mesh.vertices[t.v3].z;
        float average_z = (v1 + v2 + v3) / 3.0f;
        mesh.triangles[i].z = average_z;
    }

    // Sort the triangles by their z-coordinate in descending order
    qsort(mesh.triangles, mesh.num_triangles, sizeof(triangle), compare_triangle_z);

    // Iterate over each triangle in the mesh
    for (int i = 0; i < mesh.num_triangles; i++)
    {
        triangle t = mesh.triangles[i];

        vec3 v1 = {mesh.vertices[t.v1].x, mesh.vertices[t.v1].y, mesh.vertices[t.v1].z};
        vec3 v2 = {mesh.vertices[t.v2].x, mesh.vertices[t.v2].y, mesh.vertices[t.v2].z};
        vec3 v3 = {mesh.vertices[t.v3].x, mesh.vertices[t.v3].y, mesh.vertices[t.v3].z};
       
            if (rasterize_enable)
            {
                draw_r = (int)(mesh.triangles[i].color.x * 255);
                draw_g = (int)(mesh.triangles[i].color.y * 255);
                draw_b = (int)(mesh.triangles[i].color.z * 255);
                draw_a = (int)(mesh.triangles[i].color.w * 255);

              
                    if (check_triangle_zbuffer(v1, v2, v3)) rasterize_triangle(v1, v2, v3);
                    //update_VGA();
              
            }

            if (wireframe_enable)
            {
                draw_r = 255;
                draw_g = 0;
                draw_b = 0;
                draw_a = 255;

                draw_line((vec2){v1.x, v1.y}, (vec2){v2.x, v2.y});
                draw_line((vec2){v2.x, v2.y}, (vec2){v3.x, v3.y});
                draw_line((vec2){v3.x, v3.y}, (vec2){v1.x, v1.y});
            }
        
    }
}
