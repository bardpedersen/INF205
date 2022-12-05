#include <cassert>
#include <iostream>
#include <stdlib.h>
#include <cmath>

#include "sphere.h"


double Sphere::get_coordinate(int axis) const
{
   assert((axis == 0) || (axis == 1) || (axis == 2));
   return this->coords[axis];
}

void Sphere::set_size(double in_size)
{
   assert(in_size > 0.0);
   this->size = in_size;
}

void Sphere::set_coordinate(int axis, double in_coord)
{
   assert((axis == 0) || (axis == 1) || (axis == 2));
   this->coords[axis] = in_coord;
}

// Is there a collision between this sphere and another?
//
// by a collision here we mean a genuine overlap between spheres:
// if two spheres barely touch each other (square_distance == sum_of_radii*sum_of_radii) it does not count as a collision;
//
// it is only counted if, below, the square distance is properly smaller than the square of the sum of radii
//
int Sphere::check_collision(const Sphere* other, const double box_size[3]) const
{
   // square distance between the centre of i and the centre of j
   double square_distance = 0.0;
   for(int d = 0; d < 3; d++)
   {
      double dist_d = other->coords[d] - this->coords[d];
      
      // apply minimum image convention ????
      if(dist_d > 0.5*box_size[d]) dist_d -= box_size[d];
      else if(dist_d < -0.5*box_size[d]) dist_d += box_size[d]; 
      
      square_distance += dist_d*dist_d;
   }
   
   double sum_of_radii = 0.5 * (this->size + other->size);
   int overlap = 0;
   if(square_distance < 0.25*sum_of_radii*sum_of_radii) overlap = 8;  // soft shielding
   else if(square_distance < sum_of_radii*sum_of_radii) overlap = 1;  // normal overlap
   
   return overlap;
}
