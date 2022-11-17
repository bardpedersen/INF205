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

// is there a collision between this sphere and another?
//
// by a collision here we mean a genuine overlap between spheres:
// if two spheres barely touch each other (square_distance == sum_of_radii*sum_of_radii) it does not count as a collision;
//
// it is only counted if, below, the square distance is properly smaller than the square of the sum of radii
//
bool Sphere::check_collision(const Sphere* other, const double box_size[3]) const
{
   // square distance between the centre of i and the centre of j
   double square_distance = 0.0;
   for(int d = 0; d < 3; d++)
   {
      double dist_d = other->coords[d] - this->coords[d];
      
      // apply minimum image convention
      if(dist_d > 0.5*box_size[d]) dist_d -= box_size[d]; //3 og 0, 3, 3> 0.5*4 3 -4 =  -1
      else if(dist_d < -0.5*box_size[d]) dist_d += box_size[d]; 
      
      square_distance += dist_d*dist_d;
   }
   
   /*
    * is the square distance smaller than the square of the sum of radii?
    */
   double sum_of_radii = 0.5 * (this->size + other->size); //why multiply by 0.5
   bool collision = (square_distance < sum_of_radii*sum_of_radii);
   
   if(collision) // debug_output
   {  
      /*
      std::cout << "\t\tcollision between " << this->particle_id << " (" << this->coords[0] << "/"
                << this->coords[1] << "/" << this->coords[2] << "),\tsize " << this->size
                << ",\t\tand " << other->particle_id << " (" << other->coords[0] << "/"
                << other->coords[1] << "/" << other->coords[2] << "),\tsize " << other->size << "\n";
      */
   }
   return collision;
}
