#ifndef BOX_H
#define BOX_H

#include <iostream>
#include <map>
#include <vector>

#include "sphere.h"
#include "small_box.h"

class Box
{
public:
   void in(std::istream* source);  // read from *source
   
   long count_collisions();  //count number of collisions

   std::vector<std::vector<Sphere>> new_vector(); // make new vector that sorts based on x coord

   int move_sphere(int number_of_coll); // move spheres
   
   int get_N() const{return this->N;};

   double get_extension(int axis) const;

   void split_boxes(int number_of_boxes); //Split the box into smaller ones for faster computation

   long count_collisions_all_spheres();
   

   std::multimap<double, int, std::greater<int> > &get_components() {return this->components;};
   std::vector<std::vector<Sphere> > &get_particles() {return this->particles;};
   

private:
   double extension[3];  // size of the box
   std::multimap<double, int, std::greater<int> > components;  //  IDs (value) ordered by size (key)
   std::vector<std::vector<Sphere> > particles;  // maps each component ID to the spheres associated with that component
   std::vector<std::vector<Sphere> > x_particles; // maps each component, and sorted by x coord
   std::vector<small_Box> boxes; 
   size_t N;  // total number of particles
};

std::istream& operator>>(std::istream& is, Box& b);

#endif
