#include <iostream>
#include "collisions_low-level.h"

double time_measurement(int N, sphere planets[])
{
   int num_tests = 10000;
   auto t0 = std::chrono::high_resolution_clock::now();
   for(int i = 0; i < num_tests; i++)
   {
      count_collisions(N, planets);;
   }
   auto t1 = std::chrono::high_resolution_clock::now();
   return std::chrono::duration_cast<std::chrono::nanoseconds>(t1-t0).count() / (double)num_tests;
}

int main()
{
   int N = 0; // N will be the number of spheres
   std::cin >> N;  // input number of spheres 
   sphere *planets = new sphere[N];

   /*
    * read all the data from standard input
    */
   for(int i = 0; i < N; i++)
   {
      std::cin >> planets[i].size >> planets[i].coordx >> planets[i].coordy >> planets[i].coordz;
   }
   
   /*
    * how many collisions are there between the spheres?
    * 
    * note: collision here means "overlap" between spheres
    */
   int time = time_measurement(N, planets);
   std::cout << time << "nanoseconds to run";
   delete[] planets;
}
