#include "vector.h"
#include "draw.h"
#include "config.h"
#include "buffer.h"
#include "mesh.h"
#include "matrix.h"
#include "geometry.h"
#include "dtekv-lib.h"
#include "math.h"
#include "io.h"

// Main loop flag
int running = 1;

char sw0 = 0;
char sw1 = 0;
char sw2 = 0;
char sw3 = 0;
char sw4 = 0;
char sw5 = 0;
char sw6 = 0;
char sw7 = 0;
char sw8 = 0;
char sw9 = 0;

void update_scene(scene *scene, vec4 center_point) {
    if (sw0) translate_scene(scene, 0.0f, 1.0f, 0.0f);
    if (sw1) translate_scene(scene, 0.0f, -1.0f, 0.0f);
    if (sw2) rotate_scene(scene, 0.0f, -0.1f, 0.0f, center_point);
    if (sw3) rotate_scene(scene, 0.0f, 0.1f, 0.0f, center_point);
    if (sw4) rotate_scene(scene, -0.1f, 0.0f, 0.0f, center_point);
    if (sw5) rotate_scene(scene, 0.1f, 0.0f, 0.0f, center_point);
    if (sw6) translate_scene(scene, 0.0f, 0.0f, -1.0f);
    if (sw7) translate_scene(scene, 0.0f, 0.0f, 1.0f);
}

void update_config() {
    if(sw8) {
        wireframe_enable = 1;
        rasterize_enable = 0;
        zbuffer_enable = 0;
    } else {
      wireframe_enable = 0;
      rasterize_enable = 1;
      if (sw9) {
        zbuffer_enable = 1;
      } else {
        zbuffer_enable = 0;
      }
    }
}
    
int main()
{
    print("Starting!!!");

    init_io();
    clear_pbuffer();
    clear_zbuffer();

    int frames = 0;

    vec4 center_point = {0.0f, 0.0f, 0.0f, 1.0f};

    center_point = (vec4){15.0f, 30.0f, -115.0f, 1.0f};
    mesh4 big_dirt1 = create_grass_block(center_point, 15.0f);

    center_point = (vec4){15.0f, 30.0f, -85.0f, 1.0f};
    mesh4 big_dirt2 = create_grass_block(center_point, 15.0f);

    center_point = (vec4){-15.0f, 30.0f, -85.0f, 1.0f};
    mesh4 big_dirt3 = create_grass_block(center_point, 15.0f);

    center_point = (vec4){25.0f, 10.0f, -125.0f, 1.0f};
    mesh4 tree1 = create_wood_block(center_point, 5.0f);

    center_point = (vec4){25.0f, 0.0f, -125.0f, 1.0f};
    mesh4 tree2 = create_wood_block(center_point, 5.0f);

    center_point = (vec4){25.0f, -10.0f, -125.0f, 1.0f};
    mesh4 tree3 = create_wood_block(center_point, 5.0f);

    center_point = (vec4){25.0f, -30.0f, -125.0f, 1.0f};
    mesh4 big_leaf1 = create_leaf_block(center_point, 15.0f);

    center_point = (vec4){0.0f, 0.0f, -100.0f, 1.0f};

    scene render_scene = create_scene();

    add_to_scene(big_dirt1, &render_scene);
    add_to_scene(big_dirt2, &render_scene);
    add_to_scene(big_dirt3, &render_scene);
    add_to_scene(tree1, &render_scene);
    add_to_scene(tree2, &render_scene);
    add_to_scene(tree3, &render_scene);
    add_to_scene(big_leaf1, &render_scene);

    while (running)
    {

        update_scene(&render_scene, center_point);
        update_config();

        mesh4 render_mesh4 = scene_to_mesh4(&render_scene);

        mesh3 render_mesh3 = mesh4_perspective_mesh3(render_mesh4);

        draw_mesh3(render_mesh3);

        update_VGA();

        clear_pbuffer();
        clear_zbuffer();

        frames++;
    }

    return 0; // Program finished successfully
}

void handle_interrupt(unsigned cause)
{
    print("Interrupt detected! ");
    switch (cause)
    {
    case 16: // Timeout
        print("cause: 16\n");
        break;
    case 17: // Switches

        reset_io();
        print("cause: 17\n");
        int sw_mask = get_sw();
        set_leds(sw_mask);

        sw0 = sw_mask & 0b1;
        sw1 = (sw_mask >> 1) & 0b1;
        sw2 = (sw_mask >> 2) & 0b1;
        sw3 = (sw_mask >> 3) & 0b1;
        sw4 = (sw_mask >> 4) & 0b1;
        sw5 = (sw_mask >> 5) & 0b1;
        sw6 = (sw_mask >> 6) & 0b1;
        sw7 = (sw_mask >> 7) & 0b1;
        sw8 = (sw_mask >> 8) & 0b1;
        sw9 = (sw_mask >> 9) & 0b1;
        

        break;
    case 18: // Button 0
        print("cause: 18\n");
        reset_io();
        running = 0; // Exit program
        break;
    default:
        print("Unknown interrupt, cause: ");
        print_dec(cause);
        print("\n");
        break;
    }

    return;
}