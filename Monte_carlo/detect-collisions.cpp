#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>

#include "box.h"
#include "sphere.h"


   /* used to calculate time in each function to se where we can improve.
   auto t1 = std::chrono::high_resolution_clock::now();
   long overlaps = b.count_overlaps();
   auto t2 = std::chrono::high_resolution_clock::now();
   auto delta_t12 = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
   std::cout << "To compute overlaps:\t" << 1.0e-06*delta_t12 << " s\n";
   */

int main(int argc, char** argv)
{
   assert(argc > 1);
   
   Box b;
   std::ifstream file_in{argv[1]};
   file_in >> b;
   file_in.close();

   std::multimap<double, int, std::greater<int>> &compon = b.get_components();
   std::vector<std::vector<Sphere>> &particle = b.get_particles(); 

   int collosions_start = b.count_collisions();
   const int size = b.get_N();
   b.start_phase();
   int collisons_stacked = b.count_collisions();
   int lowest_number_of_collisions = collisons_stacked;
   int collisions_to_funct = collisons_stacked;

   double coord[size][3];
   int iteration = 0;
   for(int i = 0; i < 10; i++){
      iteration++;
      int number_of_collisions = b.move_sphere(collisions_to_funct); // Need to fix

      if(number_of_collisions < lowest_number_of_collisions){

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

   std::cout << "\n===\nCollisions before: " << collosions_start << "\n";
   std::cout << "\n===\nCollisions after: " << lowest_number_of_collisions << "\n";
   std::cout << "===\nNumber of itterations: " << iteration << "\n";
}