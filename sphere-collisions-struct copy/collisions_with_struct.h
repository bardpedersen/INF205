#ifndef COLLISIONS_WITH_STRUCT_H
#define COLLISIONS_WITH_STRUCT_H

struct sphere{
    float size;
    float coordx;
    float coordy;
    float coordz;
};

/*
 * computes and returns the number of collisions among pairs of N spheres in three dimensions
 * size[0], ..., size[N-1] are the diameters of the spheres
 * 
 * coordx[0], ..., coordx[N-1] are the x coordinates of the centres of all the spheres
 * the y and z coordinates are handled in the same way
 */
int count_collisions(int N, struct sphere[]);

/*
 * is there a collision between spheres i and j?
 * this helper function, which may also be called directly from outside, determines it
 * 
 * as above, size values are diameters, and the other values are spatial coordinates
 */
bool check_collision(struct sphere, struct sphere);

#endif
