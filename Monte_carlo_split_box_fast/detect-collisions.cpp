#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>

#include "box.h"
#include "small_box.h"
#include "sphere.h"


int main(int argc, char** argv)
{
   assert(argc > 1);
   Box b;
   std::ifstream file_in{argv[1]};
   file_in >> b;
   file_in.close();
   b.split_boxes(3);  //number of boxes in qube and initelize smaller boxes
   std::multimap<double, int, std::greater<int>> &compon = b.get_components();
   std::vector<std::vector<Sphere>> &particle = b.get_particles(); 

   int collions_to_print_Start = b.count_collisions_all_spheres();
   int collosions_start = b.count_collisions();
   int lowest_number_of_collisions = collosions_start;
   int collisions_to_funct = collosions_start;

   int size = b.get_N();
   double coord[size][3];
   int itteration = 0;

   for(int i = 0; i < 10; i++){ //number of spheres to move
      itteration++;
      int number_of_collisions = b.move_sphere(collisions_to_funct);

      if(number_of_collisions < lowest_number_of_collisions){ //check if the collosions have lower and if, we save the coordinates.

         lowest_number_of_collisions = number_of_collisions;
         for(auto comp = compon.begin(); comp != compon.end(); comp++){
            for(auto partic = particle[comp->second].begin(); partic != particle[comp->second].end(); partic++){
               int particle_number = partic->get_particle_id();
            
               for(int c = 0; c < 3; c++){
                  coord[particle_number][c] = partic->get_coordinate(c);
               }
            }
         }
      }

      if(number_of_collisions==0){ //if collsion == 0, break and stop. 
         break;
      }
      collisions_to_funct = number_of_collisions;
   }

   //assign the coords with the lowest collisions back to the spheres
   for(auto comp = compon.begin(); comp != compon.end(); comp++){
      for(auto partic = particle[comp->second].begin(); partic != particle[comp->second].end(); partic++){
         int particle_number = partic->get_particle_id();
               
         for(int c = 0; c < 3; c++){
            partic->set_coordinate(c, coord[particle_number][c]);
            //std::cout <<coord[particle_number][c] << "";
         }
         //std::cout <<" "<< partic->get_size();
         //std::cout << "\n";
      }
   }

   int collions_to_print_end = b.count_collisions_all_spheres();
   
   std::cout << "\n===\nCollisions before: " << collions_to_print_Start << "\n";
   std::cout << "\n===\nCollisions after: " << collions_to_print_end << "\n";
   std::cout << "===\nNumber of itterations: " << itteration << "\n";
}
