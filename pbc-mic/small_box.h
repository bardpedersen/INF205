#ifndef SMALL_BOX_H
#define SMALL_BOX_H

#include <iostream>
#include <map>
#include <vector>

#include "sphere.h"

class small_Box
{
public:
   void set_extension(int axis, double in_coord);
   void set_particles(Sphere *partic);
   void set_box_id(size_t box_ID);

   double get_extension(int axis) const;
   int get_N() const { return this->N;}
   int get_box_id() const { return this->box_id;}
   std::vector<Sphere> &get_particles() {return this->particles;}


private:
   double extension[6];  // size of the box (x_start, x_stop, y_start, y_stop, z_start, z_stop)
   std::vector<Sphere> particles;  // maps each component ID to the spheres associated with that component
   size_t N = 0;  // total number of particles
   size_t box_id = 0; 
};

#endif
