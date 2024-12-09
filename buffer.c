#include "config.h"
#include "buffer.h"
#include "vector.h"
#include <stdlib.h>

/**
 * @authors Maximilian Benedicto Arman Montazeri
 */

unsigned char pbuffer[WIDTH * HEIGHT * BUFFER_SIZE];
float zbuffer[WIDTH * HEIGHT];

/**
 * Set the pixel buffer at the given coordinates with the specified color.
 * @param v coordinates
 * @param r red component
 * @param g green component
 * @param b blue component
 * @param a alpha component
 */
void set_pbuffer(vec2 v, int r, int g, int b, int a)
{
    // Cast the floating-point coordinates to integers
    int x = (int)v.x;
    int y = (int)v.y;

    // Check if the coordinates are within the valid range
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
    {
        return; // Don't write outside the buffer
    }

    // Calculate the index (RGBA, so 4 bytes per pixel)
    int index = (y * WIDTH + x) * 4;

    // Set the pixel values (RGBA)
    pbuffer[index] = r;
    pbuffer[index + 1] = g;
    pbuffer[index + 2] = b;
    pbuffer[index + 3] = a;
}

/**
 * Set the zbuffer at the given coordinates with the specified depth.
 * @param v coordinates
 * @param z depth
 */
void set_zbuffer(vec2 v, float z)
{
    // Cast the floating-point coordinates to integers
    int x = (int)v.x;
    int y = (int)v.y;

    // Check if the coordinates are within the valid range
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
    {
        return; // Don't write outside the buffer
    }

    // Calculate the index
    int index = (y * WIDTH + x);

    // Set the pixel values
    zbuffer[index] = z;
}

/**
 * Clears the pixel buffer and sets all pixels to black (0, 0, 0, 0).
 */
void clear_pbuffer()
{
    // Fill the pixel buffer with black (0, 0, 0, 0)
    int size = WIDTH * HEIGHT * BUFFER_SIZE;
    for (int i = 0; i < size; i += BUFFER_SIZE)
    {
        pbuffer[i] = 193;
        pbuffer[i + 1] = 213;
        pbuffer[i + 2] = 251;
        pbuffer[i + 3] = 255;
    }
}

/**
 * Clears the zbuffer and sets all pixels to furthest depth -1.
 */
void clear_zbuffer()
{

    int size = WIDTH * HEIGHT;
    for (int i = 0; i < size; i++)
    {
        zbuffer[i] = -1.0f;
    }
}

void update_VGA()
{
    // VGA Buffer pointer
    volatile char *VGA = (volatile char *)0x08000000;
    for (int x = 0; x < WIDTH; x++)
    {
        for (int y = 0; y < HEIGHT; y++)
        {
            if (zbuffer_enable)
            {
                int index = y * WIDTH + x;

                // Convert the 8-bit per channel RGB to 8-bit packed RGB
                int packed_rgb = (int)((zbuffer[index] + 1) * 255.0f);

                VGA[y * WIDTH + x] = packed_rgb;
            }
            else
            {
                int index = (y * WIDTH + x) * 4; // Each pixel has 4 bytes (RGBA)

                // Extract the color from pbuffer for this pixel
                int r = pbuffer[index];     // Red component (0-255)
                int g = pbuffer[index + 1]; // Green component (0-255)
                int b = pbuffer[index + 2]; // Blue component (0-255)

                // Convert the 8-bit per channel RGB to 8-bit packed RGB
                int packed_rgb = ((r >> 5) << 5) | ((g >> 5) << 2) | (b >> 6);

                // Write the packed color to the VGA buffer
                VGA[y * WIDTH + x] = packed_rgb;
            }
        }
    }
}
