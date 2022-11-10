#include "box.h"

void Box::in(std::istream* source)
{
   // first input size of the box
   *source >> this->extension[0] >> this->extension[1] >> this->extension[2];
   
   int cid = 0;
   size_t num_part_comp = 0;  // number of particles of a certain component
   this->N = 0;
   
   *source >> num_part_comp;  // input number of particles of component 0
   while(num_part_comp != 0)
   {
      // create new component
      double sphere_size = 0.0;
      *source >> sphere_size;
      this->components.insert({sphere_size, cid});
      this->particles.push_back(std::vector<Sphere>());
      
      // now read all the particles
      for(size_t i = 0; i < num_part_comp; i++)
      {
         // read the coordinates
         double x[3];
         for(int d = 0; d < 3; d++)
         {
            *source >> x[d];
            
            // apply periodic boundary condition
            while(x[d] < 0.0) x[d] += this->extension[d];
            while(x[d] > this->extension[d]) x[d] -= this->extension[d];
         }
         
         // insert new particle
         this->particles[cid].push_back(Sphere(this->N++, sphere_size, x));
      }
      
      cid++;
      *source >> num_part_comp;  // input number of particles for next component
   }
}

std::istream& operator>>(std::istream& is, Box& b) {
   b.in(&is);
   return is;
}

// count the number of collisions between pairs of spheres
//
long Box::count_collisions()
{
   long num_collisions = 0;
   
   // iterate over pairs of components A and B
   for(auto A = this->components.begin(); A != this->components.end(); A++)
      for(auto B = A; B != this->components.end(); B++)
      {
         // std::cout << A->second << "(" << A->first << ") x "
         //           << B->second << "(" << B->first << ")\n";  // debug output
                   
         if(A->second == B->second) // same component
         {
            // iterate over pairs of particles i and j
            for(auto i = this->particles[A->second].begin(); std::next(i) != this->particles[A->second].end(); i++)
               for(auto j = std::next(i); j != this->particles[B->second].end(); j++)
               {
                  // std::cout << "\t" << i->get_particle_id()
                  //           << "\t" << j->get_particle_id() << "\n";  // debug output
                  
                  if(i->check_collision(&(*j), this->extension)) num_collisions++;
               }
         }
         else // different components
         {
            // iterate over pairs of particles i and j
            for(auto i = this->particles[A->second].begin(); i != this->particles[A->second].end(); i++)
               for(auto j = this->particles[B->second].begin(); j != this->particles[B->second].end(); j++)
               {
                  // std::cout << "\t" << i->get_particle_id()
                  //           << "\t" << j->get_particle_id() << "\n";  // debug output
                  
                  if(i->check_collision(&(*j), this->extension)) num_collisions++;
               }
         }
      }
   
   return num_collisions;
}
