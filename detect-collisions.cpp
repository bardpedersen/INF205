#include <iostream>
#include "collisions_low-level.h"


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
   int number_of_collisions = count_collisions(N, planets);;
   std::cout << number_of_collisions << "collisions detected";
   delete[] planets;
}
