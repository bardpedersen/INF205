#include "collisions_low-level.h"
#include <iostream>
#include <list>

// is there a collision between sphere i and sphere j?
//
// by a collision here we mean a genuine overlap between spheres:
// if two spheres barely touch each other (square_distance == sum_of_radii*sum_of_radii) it does not count as a collision;
//
// it is only counted if, below, the square distance is properly smaller than the square of the sum of radii
//


bool check_collision(
   float size_i, float size_j,    /* note: "size" is here the sphere diameter, for i and j, respectively */
   float *coordx_i,float *coordx_j,
   float *coordy_i, float *coordy_j,
   float *coordz_i, float *coordz_j
) {
   // float *coordx_i_value;
   // coordx_i_value=coordx_i;
   // float *coordx_j_value;
   // coordx_j_value=coordx_j;

   // float *coordy_i_value;
   // coordy_i_value=coordy_i;
   // float *coordy_j_value;
   // coordy_j_value=coordy_j;

   // float *coordz_i_value;
   // coordz_i_value=coordz_i;
   // float *coordz_j_value;
   // coordz_j_value=coordz_j;

   // std::cout<< "("<<size_i<<","<<size_j<<")\n";

   // std::cout<< "("<<*coordx_i_value<<","<<*coordx_j_value<<")\n";
   // std::cout<< "("<<*coordy_i_value<<","<<*coordy_j_value<<")\n";
   // std::cout<< "("<<*coordz_i_value<<","<<*coordz_j_value<<")\n";

   // std::cout<< "("<<size_i<<","<<size_j<<")\n";

   // std::cout<< "("<<*coordx_i<<","<<*coordx_j<<")\n";
   // std::cout<< "("<<*coordy_i<<","<<*coordy_j<<")\n";
   // std::cout<< "("<<*coordz_i<<","<<*coordz_j<<")\n";



   /*
    * vector pointing from the centre of i to the centre of j
    */
   float distancex = coordx_j - coordx_i;
   float distancey = coordy_j - coordy_i;
   float distancez = coordz_j - coordz_i;
   
   /*
    * square of that vector
    */
   float square_distance = distancex*distancex + distancey*distancey + distancez*distancez;
   
   /*
    * is the square distance smaller than the square of the sum of radii?
    */
   float sum_of_radii = 0.5*(size_i+size_j);

   std::cout<<(square_distance < sum_of_radii*sum_of_radii)<<"\n";
   return square_distance < sum_of_radii*sum_of_radii;
}

// count the number of collisions between pairs of spheres
//
int count_collisions(int N,float *size[],  float *coordx[],  float *coordy[],  float *coordz[])
{
   float *size_value = new float[N]();
   size_value=*size;
   
   float *coordx_value = new float[N]();
   coordx_value=*coordx;
   
   float *coordy_value = new float[N]();
   coordy_value=*coordy;

   float *coordz_value = new float[N]();
   coordz_value=*coordz;

   int num_collisions = 0;
   
   /*
    * loop going from i = 0, j = 1 up to i = N-2, j = N-1, traversing all pairs
    */ 

   for(int i = 0; i < N-1; i++)
      for(int j = i+1; j < N; j++)
      {
         // std::cout<<"("<<i<<" , "<<j<<") \n";
         // std::cout<<size_value[i]<<" " <<size_value[j]<<" " << coordx_value[i]<<" " << coordx_value[j]<<" " << coordy_value[i]<<" " << coordy_value[j]<<" " << coordz_value[i]<<" " << coordz_value[j]<<"\n";

         if(check_collision(size_value[i], size_value[j], &coordx_value[i], &coordx_value[j], &coordy_value[i], &coordy_value[j], &coordz_value[i], &coordz_value[j]))
            num_collisions++;
      }

   
   return num_collisions;
}
