#include "sphere.h"
#include "small_box.h"
#include "box.h"

#include <cmath>
#include <iostream>
#include <vector>
#include <cassert>


void small_Box::set_extension(int axis, double in_coord)
{
   assert((axis == 0) || (axis == 1) || (axis == 2) || (axis == 3) || (axis == 4) || (axis ==5));
   this->extension[axis] = in_coord;
}

void small_Box::set_particles(Sphere &partic){
   this->particles.push_back(&partic);
   this->N++;
}

void small_Box::remove_particles(Sphere &partic){
   ////////////////////////////////////////////////////////////////////////////////

    auto it = std::find(this->particles.begin(), this->particles.end(), &partic);;
    if (it != this->particles.end()) { this->particles.erase(it);}
   this->N--;

   // remove in a differnet way, 
   ////////////////////////////////////////////////////////////////////////////////
}

void small_Box::set_box_id(size_t box_ID){
   this->box_id = box_ID;
}

double small_Box::get_extension(int axis) const
{
   assert((axis == 0) || (axis == 1) || (axis == 2) || (axis == 3) || (axis == 4) || (axis ==5));
   return this->extension[axis];
}



