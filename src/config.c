#include "config.h"

float fov = 90.0f; // Field of View in degrees
float aspect_ratio = (float)WIDTH / (float)HEIGHT;
float z_near = 1.0f;   // Near clipping plane
float z_far = 10000.0f; // Far clipping plane
int wireframe_enable = 0;
int rasterize_enable = 1;
int zbuffer_enable = 0; // Rasterization must be on for this to work