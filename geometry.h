#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "vector.h"
#include "mesh.h"
#include "config.h"

typedef struct
{
    int num_objects;

    mesh4 objects[MAX_OBJECTS];
} scene;

void add_to_scene(mesh4 mesh, scene *scene);
scene create_scene();
void rotate_scene(scene *scene, float x, float y, float z, vec4 center_point);
void translate_scene(scene *scene, float x, float y, float z);
mesh4 scene_to_mesh4(scene *render_scene);
mesh4 create_grass_block(vec4 center_point, float radius);
mesh4 create_dirt_block(vec4 center_point, float radius);
mesh4 create_wood_block(vec4 center_point, float radius);
mesh4 create_leaf_block(vec4 center_point, float radius);

#endif
