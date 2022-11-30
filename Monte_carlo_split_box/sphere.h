#ifndef COLLISIONS_STRUCT_H
#define COLLISIONS_STRUCT_H

#include <cstddef>
#include <vector>

class Sphere
{
public:
   //Initelize sphere class with particle id, size and coords
   Sphere(int ipid, double is, const double ix[3]) {
      this->set_particle_id(ipid);
      this->set_size(is);
      for(int d = 0; d < 3; d++) this->set_coordinate(d, ix[d]);
   }
   
   int get_particle_id() const { return this->particle_id; }
   double get_size() const { return this->size; }
   double get_coordinate(int axis) const;  // axis = 0 for x, 1 for y, 2 for z 
   std::vector<int> &get_box_ID() { return this->box_ID; }

   
   void set_particle_id(int i_pid) { this->particle_id = i_pid; }
   void set_size(double in_size);
   void set_coordinate(int axis, double in_coord);  
   void set_box_ID(int box_id);
   void erase_box_ID();

   void erase_particle_collided_with();

   void set_particle_collided_with(int particid);
   
   std::vector<int> &get_particle_collided_with() { return this->particle_collided_with; }
   
   /*
    * is there a collision between this sphere and another?
    * this method determines it
    */
   int check_collision(Sphere* other, const double box_size[3]);

private:

   int particle_id = 0;
   double size = 0.0;
   double coords[3] = {0.0, 0.0, 0.0};
   std::vector<int> box_ID;
   std::vector<int> particle_collided_with;
};

#endif
