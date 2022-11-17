#ifndef BOX_H
#define BOX_H

#include <iostream>
#include <map>
#include <vector>

#include "sphere.h"

class Box
{
public:
   void in(std::istream* source);  // read from *source
   
   long count_collisions();  // count number of collisions

   void move_sphere(); // move spheres
   
   int get_N() const{ return this->N;};

   std::multimap<double, int, std::greater<int>> get_components() const{ return this->components;};
   std::vector<std::vector<Sphere>> get_particles() const{ return this->particles;};

   

private:
   double extension[3];  // size of the box
   std::multimap<double, int, std::greater<int>> components;  //  IDs (value) ordered by size (key)
   std::vector<std::vector<Sphere>> particles;  // maps each component ID to the spheres associated with that component
   size_t N = 0;  // total number of particles
};

std::istream& operator>>(std::istream& is, Box& b);

#endif
