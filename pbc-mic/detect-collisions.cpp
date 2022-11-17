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
      
      b.move_sphere();

   }



   long num_collisions = b.count_collisions();
   std::cout << "\n===\nCollisions: " << num_collisions << "\n";
}
