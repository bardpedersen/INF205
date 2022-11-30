#include <cassert>
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <vector>

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

void Sphere::set_box_ID(int box_id)
{
   this->box_ID.push_back(box_id);
}

void Sphere::erase_box_ID()
{  
   this->box_ID.clear();
}

void Sphere::set_particle_collided_with(int particid)
{
   this->particle_collided_with.push_back(particid);
}

void Sphere::erase_particle_collided_with()
{  
   this->particle_collided_with.clear();
}

// is there a collision between this sphere and another?
//
// by a collision here we mean a genuine overlap between spheres:
// if two spheres barely touch each other (square_distance == sum_of_radii*sum_of_radii) it does not count as a collision;
//
// it is only counted if, below, the square distance is properly smaller than the square of the sum of radii
//
int Sphere::check_collision(Sphere* other, const double box_size[3])
{
   int overlap = 0;
   std::cout << this->particle_id << " " << this->particle_collided_with.size() << "what "<< other->particle_id <<"\n";
   if(this->particle_collided_with.size() > 0){
      for(int elemnt = *this->particle_collided_with.begin(); elemnt != *this->particle_collided_with.end(); elemnt++){
         if(elemnt == other->particle_id){
            std::cout<<" likt \n";
            return overlap;
         }
      }
   }

   double square_distance = 0.0;
   for(int d = 0; d < 3; d++)
   {
      double dist_d = other->coords[d] - this->coords[d];
      
      // apply minimum image convention ????
      ////////////////////////fjerne?
      //if(dist_d > 0.5*box_size[d]) dist_d -= box_size[d];
      //else if(dist_d < -0.5*box_size[d]) dist_d += box_size[d]; 
      
      square_distance += dist_d*dist_d;
   }
   
   double sum_of_radii = 0.5 * (this->size + other->size);
   if(square_distance < 0.25*sum_of_radii*sum_of_radii) overlap = 8;  // soft shielding
   else if(square_distance < sum_of_radii*sum_of_radii) overlap = 1;  // normal overlap

   /// only return this when collison
   this->particle_collided_with.push_back(other->particle_id);
   other->particle_collided_with.push_back(this->particle_id);

   /*
   Save collisons in vector
   if they have collided before return 0
   */
   return overlap;
}
