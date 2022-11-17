#include <cassert>
#include <fstream>
#include <iostream>

#include "box.h"
#include "sphere.h"

int main(int argc, char** argv)
{
   assert(argc > 1);
   
   Box b;
   std::ifstream file_in{argv[1]};
   file_in >> b;
   file_in.close();
   
   for(int i = 0; i < 100; i++){
      
      if(b.count_collisions()==0){
         break;
      }

      //if collsion == 0, break and stop. 

      /*
      //save the coords when the collision is lowest
      std::vector<double> least_collison_coord[b.get_N()]; //list in list with each sphere with its coords
      double coord[3];

      for(auto comp = b.get_components().begin(); comp != b.get_components().end(); comp++){
         for(auto partic = b.get_particles().[comp->second].begin(); partic != b.get_particles().[comp->second].end(); partic++){
            for(int c = 0; c < 3; c++){
               coord[c] = partic->get_coordinate(c);
            }
            least_collison_coord.push_back(coord[3]);
            std::cout << least_collison_coord;
         }
      }
      */
      b.move_sphere();

   }



   long num_collisions = b.count_collisions();
   std::cout << "\n===\nCollisions: " << num_collisions << "\n";
}
