#include "sphere.h"
#include <cmath>
#include <iostream>

#include "small_box.h"

void small_Box::set_extension(int axis, double in_coord)
{
   assert((axis == 0) || (axis == 1) || (axis == 2) || (axis == 3) || (axis == 4) || (axis ==5));
   this->extension[axis] = in_coord;
}

void small_Box::set_particles(Sphere partic){
    this->particles.push_back(partic);
    this->N++;
}

double small_Box::get_extension(int axis) const
{
   assert((axis == 0) || (axis == 1) || (axis == 2) || (axis == 3) || (axis == 4) || (axis ==5));
   return this->extension[axis];
}



