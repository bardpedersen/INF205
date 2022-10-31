#include "collisions_low-level.h"


// is there a collision between sphere i and sphere j?
//
// by a collision here we mean a genuine overlap between spheres:
// if two spheres barely touch each other (square_distance == sum_of_radii*sum_of_radii) it does not count as a collision;
//
// it is only counted if, below, the square distance is properly smaller than the square of the sum of radii
//
bool check_collision(sphere planets1, sphere planets2) 
{
   /*
    * vector pointing from the centre of i to the centre of j
    */
   float distancex = planets2.coordx - planets1.coordx;
   float distancey = planets2.coordy - planets1.coordy;
   float distancez = planets2.coordz - planets1.coordz;
   
   /*
    * square of that vector
    */
   float square_distance = distancex*distancex + distancey*distancey + distancez*distancez;
   
   /*
    * is the square distance smaller than the square of the sum of radii?
    */
   float sum_of_radii = 0.5*(planets1.size + planets2.size);
   return square_distance < sum_of_radii*sum_of_radii;
}

// count the number of collisions between pairs of spheres
//
int count_collisions(int N, sphere planets[])
{
   int num_collisions = 0;
   
   /*
    * loop going from i = 0, j = 1 up to i = N-2, j = N-1, traversing all pairs
    */
   for(int i = 0; i < N-1; i++)
   {
      for(int j = i+1; j < N; j++)
      {
         if(check_collision(planets[i], planets[j]))
         {
            num_collisions++;
         }
      }
   }
   
   return num_collisions;
}
