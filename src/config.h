/**
 * Config
 */
#ifndef CONFIG_H
#define CONFIG_H

#define HEIGHT 240
#define WIDTH 320
#define CAMERA_HEIGHT 120
#define CAMERA_WIDTH 160
#define COLOR_SPACE 24 // change to 8 for card
#define ALPHA 8        // remove for card or set to zero
#define BUFFER_SIZE 4
#define MAX_TRIANGLES 100 // maximum amount of triangles in a mesh4
#define MAX_VERTICES 100 // maximum amount of vertices in a mesh4
#define MAX_OBJECTS 100 // maximum amount of objects in a scene



extern float fov;
extern float aspect_ratio;
extern float z_near;
extern float z_far;
extern int wireframe_enable;
extern int rasterize_enable;
extern int zbuffer_enable;

#endif