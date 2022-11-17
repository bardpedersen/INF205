#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>

#include "box.h"
#include "sphere.h"

int main(int argc, char** argv)
{
   assert(argc > 1);
   
   Box b;
   std::ifstream file_in{argv[1]};
   file_in >> b;
   file_in.close();

   std::multimap<double, int, std::greater<int>> &compon = b.get_components();
   std::vector<std::vector<Sphere>> &particle = b.get_particles(); 
   
   int lowest_number_of_collisions = b.count_collisions();
   int size = b.get_N();
   double coord[size][3];
   for(int i = 0; i < 100; i++){

      int number_of_collisions = b.count_collisions();
      std::cout << number_of_collisions << " " << lowest_number_of_collisions<<"\n";
      if(number_of_collisions==0){ //if collsion == 0, break and stop. 
         break;
      }

      //save the coords when the collision is lowest 
      if(number_of_collisions < lowest_number_of_collisions){

         lowest_number_of_collisions = number_of_collisions;
         for(auto comp = compon.begin(); comp != compon.end(); comp++){
            for(auto partic = particle[comp->second].begin(); partic != particle[comp->second].end(); partic++){
               int particle_number = partic->get_particle_id();
            
               for(int c = 0; c < 3; c++){
                  coord[particle_number][c] = partic->get_coordinate(c);
                  std::cout << coord[particle_number][c];
               }
               std::cout << "\n";
            }
         }
      }
      b.move_sphere();
   }


   for(auto comp = compon.begin(); comp != compon.end(); comp++){
      for(auto partic = particle[comp->second].begin(); partic != particle[comp->second].end(); partic++){
         int particle_number = partic->get_particle_id();
               
         for(int c = 0; c < 3; c++){
            partic->set_coordinate(c, coord[particle_number][c]);
            std::cout << coord[particle_number][c];
         }
         std::cout << "\n";
      }
   }




   int num_collisions = b.count_collisions();
   std::cout << "\n===\nCollisions: " << num_collisions << "\n";
}
