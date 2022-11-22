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

   auto t0 = std::chrono::high_resolution_clock::now();
   std::multimap<double, int, std::greater<int>> &compon = b.get_components();
   auto t1 = std::chrono::high_resolution_clock::now();
   std::vector<std::vector<Sphere>> &particle = b.get_particles(); 
   auto t2 = std::chrono::high_resolution_clock::now();

   auto delta_t01 = std::chrono::duration_cast<std::chrono::microseconds>(t1-t0).count();
   auto delta_t12 = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
   std::cout << "b.get_components():\t" << 1.0e-06*delta_t01 << " s\n";
   std::cout << "b.get_particles():\t" << 1.0e-06*delta_t12 << " s\n";


   
   int lowest_number_of_collisions = b.count_collisions();
   auto t3 = std::chrono::high_resolution_clock::now();
   auto delta_t23 = std::chrono::duration_cast<std::chrono::microseconds>(t3-t2).count();
   std::cout << "b.count_collisions():\t" << 1.0e-06*delta_t23 << " s\n";

   int collisions_to_funct = lowest_number_of_collisions;
   int size = b.get_N();
   auto t4 = std::chrono::high_resolution_clock::now();
   auto delta_t34 = std::chrono::duration_cast<std::chrono::microseconds>(t4-t3).count();
   std::cout << "b.get_N():\t" << 1.0e-06*delta_t34 << " s\n";

   double coord[size][3];
   int itteration = 0;
   std::cout << "\n===\nCollisions: " << lowest_number_of_collisions << "\n===\n";

   for(int i = 0; i < 1; i++){
      std::cout << "\n===\nCollisions: " << lowest_number_of_collisions <<" "<< itteration << "\n===\n";
      itteration++;
      int number_of_collisions = b.move_sphere(collisions_to_funct); // Need to fix
      auto t5 = std::chrono::high_resolution_clock::now();
      auto delta_t45 = std::chrono::duration_cast<std::chrono::microseconds>(t5-t4).count();
      std::cout << "b.move_sphere:\t" << 1.0e-06*delta_t45 << " s\n";

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

   std::cout << "\n===\nCollisions: " << lowest_number_of_collisions << "\n";
   std::cout << "===\nNumber of itterations: " << itteration << "\n";
}